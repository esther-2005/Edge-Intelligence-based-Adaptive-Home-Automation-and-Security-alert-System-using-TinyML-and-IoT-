/************************************************************
 * EDGE INTELLIGENCE-BASED ADAPTIVE HOME AUTOMATION
 * AND SECURITY ALERT SYSTEM USING TINYML & IoT
 *
 * Controller : ESP32
 * ML         : Edge Impulse TinyML
 * IoT        : Blynk
 *
 * Features:
 * - MQ-2 gas detection using TinyML
 * - Flame detection
 * - Temperature monitoring
 * - Humidity monitoring
 * - Automatic exhaust fan control
 * - Automatic window opening using servo
 * - Buzzer alert
 * - Blynk remote monitoring
 ************************************************************/

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include <ESP32Servo.h>

// Edge Impulse generated library
#include "Gas_Detection_inferencing.h"


/* =========================================================
   BLYNK CONFIGURATION
   ========================================================= */

#define BLYNK_TEMPLATE_ID   "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "Home Security"
#define BLYNK_AUTH_TOKEN    "YOUR_BLYNK_AUTH_TOKEN"


/* =========================================================
   WI-FI CONFIGURATION
   ========================================================= */

char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";


/* =========================================================
   PIN CONFIGURATION
   ========================================================= */

#define DHTPIN       14
#define DHTTYPE      DHT11

#define GAS_PIN      34
#define FLAME_PIN    27

#define RELAY_PIN    26
#define SERVO_PIN    13

/*
 * Change these two pins if your actual prototype
 * uses different GPIO pins.
 */
#define BUZZER_PIN   25
#define LED_PIN      33


/* =========================================================
   OBJECTS
   ========================================================= */

DHT dht(DHTPIN, DHTTYPE);
Servo windowServo;


/* =========================================================
   VARIABLES
   ========================================================= */

float temperature = 0.0;
float humidity = 0.0;

int gasValue = 0;
int flameValue = 0;

bool gasDetected = false;
bool flameDetected = false;


/* =========================================================
   TINYML FEATURE BUFFER
   ========================================================= */

/*
 * Edge Impulse determines the required input size from
 * the generated model.
 */

static float features[EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE];


/* =========================================================
   FUNCTION FOR EDGE IMPULSE SENSOR DATA
   ========================================================= */

int get_signal_data(size_t offset, size_t length, float *out_ptr)
{
    for (size_t i = 0; i < length; i++)
    {
        out_ptr[i] = features[offset + i];
    }

    return 0;
}


/* =========================================================
   SETUP
   ========================================================= */

void setup()
{
    Serial.begin(115200);

    delay(1000);

    Serial.println();
    Serial.println("========================================");
    Serial.println(" Home Security & Automation System");
    Serial.println(" ESP32 + TinyML + IoT");
    Serial.println("========================================");


    /* -----------------------------
       Sensor configuration
       ----------------------------- */

    pinMode(GAS_PIN, INPUT);
    pinMode(FLAME_PIN, INPUT);

    pinMode(RELAY_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);


    /* -----------------------------
       Initial actuator states
       ----------------------------- */

    digitalWrite(RELAY_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN, LOW);


    /* -----------------------------
       DHT11 initialization
       ----------------------------- */

    dht.begin();


    /* -----------------------------
       Servo initialization
       ----------------------------- */

    windowServo.attach(SERVO_PIN);

    // Window closed position
    windowServo.write(0);


    /* -----------------------------
       Wi-Fi and Blynk
       ----------------------------- */

    Serial.println("Connecting to Wi-Fi...");

    Blynk.begin(
        BLYNK_AUTH_TOKEN,
        ssid,
        pass
    );

    Serial.println("System initialized.");
}


/* =========================================================
   READ DHT11
   ========================================================= */

void readDHTSensor()
{
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();

    if (isnan(temperature) || isnan(humidity))
    {
        Serial.println("DHT11 reading failed.");
        return;
    }

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");


    /* Send values to Blynk */

    Blynk.virtualWrite(V2, temperature);
    Blynk.virtualWrite(V3, humidity);
}


/* =========================================================
   READ FLAME SENSOR
   ========================================================= */

void readFlameSensor()
{
    flameValue = digitalRead(FLAME_PIN);

    /*
     * Most flame sensor modules give LOW when
     * flame is detected.
     */

    if (flameValue == LOW)
    {
        flameDetected = true;
    }
    else
    {
        flameDetected = false;
    }


    if (flameDetected)
    {
        Serial.println("🔥 FLAME DETECTED!");

        digitalWrite(BUZZER_PIN, HIGH);
        digitalWrite(LED_PIN, HIGH);

        Blynk.virtualWrite(V1, 1);
    }
    else
    {
        Serial.println("No flame detected.");

        digitalWrite(BUZZER_PIN, LOW);
        digitalWrite(LED_PIN, LOW);

        Blynk.virtualWrite(V1, 0);
    }
}


/* =========================================================
   TINYML GAS CLASSIFICATION
   ========================================================= */

bool runGasTinyML()
{
    /*
     * Collect MQ-2 samples for the TinyML model.
     *
     * The exact number of samples is determined by the
     * Edge Impulse generated model.
     */

    for (size_t i = 0;
         i < EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE;
         i++)
    {
        gasValue = analogRead(GAS_PIN);

        /*
         * Convert ADC value to float.
         * The scaling can be adjusted according to
         * the preprocessing used during Edge Impulse
         * model training.
         */

        features[i] = (float)gasValue;

        delay(
            1000 / EI_CLASSIFIER_FREQUENCY
        );
    }


    /* -----------------------------
       Create Edge Impulse signal
       ----------------------------- */

    signal_t signal;

    signal.total_length =
        EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE;

    signal.get_data = get_signal_data;


    /* -----------------------------
       Run inference
       ----------------------------- */

    ei_impulse_result_t result = {};

    EI_IMPULSE_ERROR res =
        run_classifier(
            &signal,
            &result,
            false
        );


    if (res != EI_IMPULSE_OK)
    {
        Serial.print("TinyML inference error: ");
        Serial.println(res);

        return false;
    }


    /* -----------------------------
       Display classification result
       ----------------------------- */

    Serial.println();
    Serial.println("----- TinyML Classification -----");


    float highestProbability = 0.0;

    String predictedClass = "Normal";


    for (size_t i = 0;
         i < EI_CLASSIFIER_LABEL_COUNT;
         i++)
    {
        String label =
            result.classification[i].label;

        float probability =
            result.classification[i].value;


        Serial.print(label);
        Serial.print(": ");
        Serial.println(probability, 4);


        if (probability > highestProbability)
        {
            highestProbability = probability;
            predictedClass = label;
        }
    }


    Serial.print("Predicted Class: ");
    Serial.println(predictedClass);

    Serial.print("Confidence: ");
    Serial.println(highestProbability, 4);


    /*
     * The Edge Impulse model used in this project
     * contains gas-related classification.
     *
     * Expected classes:
     * - Normal / No Gas
     * - Gas Detected
     */

    predictedClass.toLowerCase();


    if (
        predictedClass.indexOf("gas") >= 0 &&
        predictedClass.indexOf("no gas") < 0 &&
        predictedClass.indexOf("normal") < 0
       )
    {
        return true;
    }


    return false;
}


/* =========================================================
   GAS SAFETY RESPONSE
   ========================================================= */

void gasSafetyResponse()
{
    Serial.println();
    Serial.println("🚨 GAS DETECTED!");
    Serial.println("Activating safety mechanisms...");


    /*
     * Turn ON exhaust fan
     */

    digitalWrite(RELAY_PIN, HIGH);


    /*
     * Open window
     */

    windowServo.write(90);


    /*
     * Visual indication
     */

    digitalWrite(LED_PIN, HIGH);


    /*
     * Send gas status to Blynk
     */

    Blynk.virtualWrite(V0, gasValue);


    Serial.println("Exhaust fan: ON");
    Serial.println("Window: OPEN");
}


/* =========================================================
   NORMAL GAS CONDITION
   ========================================================= */

void normalGasResponse()
{
    Serial.println();
    Serial.println("No hazardous gas detected.");


    /*
     * Turn OFF exhaust fan
     */

    digitalWrite(RELAY_PIN, LOW);


    /*
     * Close window
     */

    windowServo.write(0);


    /*
     * Gas monitoring value
     */

    Blynk.virtualWrite(V0, gasValue);
}


/* =========================================================
   MAIN LOOP
   ========================================================= */

void loop()
{
    /*
     * Maintain Blynk connection
     */

    Blynk.run();


    /* =====================================================
       1. READ TEMPERATURE & HUMIDITY
       ===================================================== */

    readDHTSensor();


    /* =====================================================
       2. FLAME DETECTION
       ===================================================== */

    readFlameSensor();


    /* =====================================================
       3. TINYML GAS CLASSIFICATION
       ===================================================== */

    gasDetected = runGasTinyML();


    /* =====================================================
       4. GAS SAFETY DECISION
       ===================================================== */

    if (gasDetected)
    {
        gasSafetyResponse();
    }
    else
    {
        normalGasResponse();
    }


    /* =====================================================
       5. FLAME SAFETY
       ===================================================== */

    if (flameDetected)
    {
        Serial.println();
        Serial.println("🔥 FIRE/FLAME ALERT!");
        Serial.println("Buzzer activated.");

        digitalWrite(BUZZER_PIN, HIGH);
        digitalWrite(LED_PIN, HIGH);

        /*
         * Keep the exhaust fan active during
         * a detected hazardous condition.
         */

        digitalWrite(RELAY_PIN, HIGH);
    }


    /* =====================================================
       DELAY
       ===================================================== */

    delay(1000);
}
