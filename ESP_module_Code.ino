#include <Arduino.h>
#include <WiFi.h>
#include <FirebaseESP32.h>

// WiFi Credentials
#define WIFI_SSID "Dasun464"
#define WIFI_PASSWORD "Dasun1998"

// Firebase Credentials
#define API_KEY "AIzaSyA-qsvs3ndugT0FdItJH1_HGQlTdPia2tY"
#define DATABASE_URL "https://river-guage-project-default-rtdb.firebaseio.com/"

// Serial communication pins
#define RXp2 16
#define TXp2 17

// Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
bool signupOK = false;

// Variables to store received values
String ambientTemp, waterTemp, distance;
float formattedWattage = 0.0;
float formattedAmpsRMS = 0.0;

// Fix: Correct the callback function to use proper token info fields
void tokenStatusCallback(TokenInfo info) {
    Serial.print("Token status: ");
    Serial.println(info.status == token_status_ready ? "ready" : "error");
}

void setup() {
    Serial.begin(115200);
    Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);

    // Connect to WiFi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(300);
    }
    Serial.println("\nConnected with IP: " + WiFi.localIP().toString());

    // Firebase Configuration
    config.api_key = API_KEY;
    config.database_url = DATABASE_URL;
    config.token_status_callback = tokenStatusCallback;

    // Sign up to Firebase
    if (Firebase.signUp(&config, &auth, "", "")) {
        Serial.println("Firebase authentication successful.");
        signupOK = true;
    } else {
        Serial.printf("Firebase signup failed: %s\n", config.signer.signupError.message.c_str());
    }

    // Initialize Firebase
    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);
}

void loop() {
    if (Serial2.available()) {
        String receivedData = Serial2.readString();
        receivedData.trim();  // Remove any trailing whitespace
        Serial.println("Received: " + receivedData);

        // Fixed parsing for Ambient Temperature
        if (receivedData.indexOf("Ambient Temperature") != -1) {
            int startPos = receivedData.indexOf("=") + 2;
            int endPos = receivedData.indexOf(" Degree");
            if (endPos == -1) {
                endPos = receivedData.length();
            }
            ambientTemp = receivedData.substring(startPos, endPos);
            ambientTemp.trim();
            Serial.println("Parsed Ambient Temp: " + ambientTemp);
            sendToFirebase("System/AmbientTemperature", ambientTemp.toFloat());
        }
        
        // Fixed parsing for Water Temperature
        if (receivedData.indexOf("Water Temperature") != -1) {
            int startPos = receivedData.indexOf(";") + 2;
            int endPos = receivedData.indexOf("°C");
            if (endPos == -1) {
                endPos = receivedData.length();
            }
            waterTemp = receivedData.substring(startPos, endPos);
            waterTemp.trim();
            Serial.println("Parsed Water Temp: " + waterTemp);
            sendToFirebase("System/WaterTemperature", waterTemp.toFloat());
        }
        
        // Fixed parsing for Distance
        if (receivedData.indexOf("Distance") != -1) {
            int startPos = receivedData.indexOf(":") + 2;
            distance = receivedData.substring(startPos);
            distance.trim();
            Serial.println("Parsed Distance: " + distance);
            sendToFirebase("System/Distance", distance.toFloat());
        }
    }

    if (Firebase.ready() && signupOK && formattedWattage > 0.2 &&
        (millis() - sendDataPrevMillis > 2000 || sendDataPrevMillis == 0)) {
        sendDataPrevMillis = millis();

        sendToFirebase("System/AmpsRMS", formattedAmpsRMS);
        sendToFirebase("System/Wattage", formattedWattage);
    }

    delay(5000);
}

void sendToFirebase(const char* path, float value) {
    if (Firebase.setFloat(fbdo, path, value)) {
        Serial.printf("%s sent successfully.\n", path);
    } else {
        Serial.printf("Failed to send %s: %s\n", path, fbdo.errorReason().c_str());
    }
}
