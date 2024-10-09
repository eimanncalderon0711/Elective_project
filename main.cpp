// #include <WiFi.h>
// #include <HTTPClient.h>
// #include <SPI.h>
// #include <MFRC522.h>

// const char* wifiSSID = "Cloud Control Network";
// const char* wifiPassword = "ccv7network";
// const char* serverURL = "http://10.10.10.17/rfid/rfid.php";

// #define resetPin 0
// #define sdaPin 5

// MFRC522 rfidModule(sdaPin, resetPin);

// void setup() {
//   Serial.begin(115200);
//   SPI.begin(18, 19, 23, sdaPin);
//   rfidModule.PCD_Init();
//   Serial.println("RFID reader initialized.");

//   WiFi.begin(wifiSSID, wifiPassword);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(1000);
//     Serial.println("Connecting to WiFi...");
//   }
//   Serial.println("Connected to WiFi, IP Address: ");
//   Serial.println(WiFi.localIP());
// }

// void loop() {
//   if (!rfidModule.PICC_IsNewCardPresent()) {
//     return;
//   }

//   if (!rfidModule.PICC_ReadCardSerial()) {
//     Serial.println("Failed to read card.");
//     return;
//   }

//   String rfidTagData = "";
//   for (byte i = 0; i < rfidModule.uid.size; i++) {
//     rfidTagData += String(rfidModule.uid.uidByte[i], HEX);
//   }

//   Serial.print("RFID Tag UID: ");
//   Serial.println(rfidTagData);

//   if (WiFi.status() == WL_CONNECTED) {
//     HTTPClient http;
//     String fullURL = String(serverURL) + "?rfid=" + rfidTagData;

//     http.begin(fullURL.c_str());
//     int responseCode = http.GET();

//     if (responseCode > 0) {
//       String serverResponse = http.getString();
//       Serial.println("Response from server: " + serverResponse);
//     } else {
//       Serial.println("Error in sending request: " + String(responseCode));
//     }

//     http.end();
//   } else {
//     Serial.println("WiFi Disconnected");
//   }

//   rfidModule.PICC_HaltA();
//   delay(2000);
// }


// #include <WiFi.h>
// #include <HTTPClient.h>
// #include <SPI.h>
// #include <MFRC522.h>

// #define SS_PIN  5 
// #define RST_PIN 0 

// MFRC522 rfid(SS_PIN, RST_PIN); 
// const char* ssid = "CalderonWifi";
// const char* password = "@July07112001"; 
// const char* serverUrl = "http://192.168.1.16/rfid/rfid.php";

// void setup() {
//     Serial.begin(115200);
//     SPI.begin(); 
//     rfid.PCD_Init(); 
//     WiFi.begin(ssid, password); 

//     while (WiFi.status() != WL_CONNECTED) {
//         delay(1000);
//         Serial.println("Connecting to WiFi...");
//     }

//     Serial.println("Connected to WiFi");
// }

// void loop() {
//     if (!rfid.PICC_IsNewCardPresent()) {
//         return;
//     }
//     if (!rfid.PICC_ReadCardSerial()) {
//         return;
//     }

//     String rfidUID = "";
//     for (byte i = 0; i < rfid.uid.size; i++) {
//         rfidUID += String(rfid.uid.uidByte[i], HEX);
//     }

//     // Debugging output for RFID UID
//     Serial.print("RFID UID: ");
//     Serial.println(rfidUID);

//     WiFiClient client;
//     const char* serverIp = "192.168.1.16";  
//     if (client.connect(serverIp, 80)) {  
//         String url = "/rfid_status.php?rfid=" + rfidUID; 
//         client.print(String("GET ") + url + " HTTP/1.1\r\n" +
//                      "Host: " + serverIp + "\r\n" +
//                      "Connection: close\r\n\r\n");
//         Serial.println("Request sent to server.");
//         delay(100);
//     } else {
//         Serial.println("Connection to server failed");
//     }

//     rfid.PICC_HaltA(); 
//     delay(2000); 
// }


// #include <WiFi.h>
// #include <HTTPClient.h>
// #include <SPI.h>
// #include <MFRC522.h>

// #define SS_PIN  5 
// #define RST_PIN 0 

// MFRC522 rfid(SS_PIN, RST_PIN); 
// const char* ssid = "CalderonWifi";
// const char* password = "@July07112001"; 
// const char* serverUrl = "192.168.1.16"; // Server IP address

// void setup() {
//     Serial.begin(115200);
//     SPI.begin(); 
//     rfid.PCD_Init(); 
//     WiFi.begin(ssid, password); 

//     while (WiFi.status() != WL_CONNECTED) {
//         delay(1000);
//         Serial.println("Connecting to WiFi...");
//     }

//     Serial.println("Connected to WiFi");
// }

// void loop() {
//     // Check for a new RFID card
//     if (!rfid.PICC_IsNewCardPresent()) {
//         return;
//     }
//     if (!rfid.PICC_ReadCardSerial()) {
//         return;
//     }

//     // Collect RFID UID
//     String rfidUID = "";
//     for (byte i = 0; i < rfid.uid.size; i++) {
//         rfidUID += String(rfid.uid.uidByte[i], HEX);
//     }

//     // Print the RFID UID for debugging
//     Serial.println("RFID UID: " + rfidUID);

//     // If connected to WiFi, make HTTP request
//     if (WiFi.status() == WL_CONNECTED) {
//         HTTPClient http;
//         String url = String("http://") + serverUrl + "/rfid/rfid.php?rfid=" + rfidUID;

//         http.begin(url); 
//         int httpResponseCode = http.GET(); // Send the GET request

//         // End the connection
//         http.end(); 
//     } else {
//         Serial.println("WiFi not connected");
//     }

//     rfid.PICC_HaltA(); 
//     delay(2000); 
// }


#include <WiFi.h>
#include <HTTPClient.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN  5 
#define RST_PIN 0 

MFRC522 rfid(SS_PIN, RST_PIN); 
const char* ssid = "CalderonWifi";
const char* password = "@July07112001"; 
const char* serverUrl = "http://192.168.1.16/rfid/rfid.php";  // Change to your local server IP

void setup() {
    Serial.begin(115200);
    SPI.begin(); 
    rfid.PCD_Init(); 
    WiFi.begin(ssid, password); 

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }

    Serial.println("Connected to WiFi");
}

void loop() {
    // Check for new card
    if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
        return;
    }

    // Construct the RFID UID string
    String rfidUID = "";
    for (byte i = 0; i < rfid.uid.size; i++) {
        rfidUID += String(rfid.uid.uidByte[i], HEX);
    }
    rfidUID.toUpperCase(); // Make the RFID uppercase for consistency

    Serial.println("RFID UID: " + rfidUID);

    // Send the UID to the backend (PHP)
    HTTPClient http;
    String serverPath = String(serverUrl) + "?rfid=" + rfidUID;  // Send RFID as query parameter

    http.begin(serverPath.c_str());
    int httpResponseCode = http.GET();

    // Check for successful response
    if (httpResponseCode > 0) {
        String response = http.getString();
        
        // Extract the relevant part of the response for the terminal output
        if (response.indexOf("RFID Not Found") != -1) {
            Serial.println("RFID Not Found");
        } else if (response.indexOf("RFID Found") != -1) {
            // Find the status updated part in the response
            int statusIndex = response.indexOf("Status updated to: ");
            if (statusIndex != -1) {
                String status = response.substring(statusIndex + 19, statusIndex + 20);  // Get status value (0 or 1)
                Serial.println("RFID Found - Status updated to: " + status);
            }
        }
    } else {
        Serial.println("Error on sending request: " + String(httpResponseCode));
    }

    http.end();
    rfid.PICC_HaltA();  // Halt RFID
    delay(2000);        // Add delay to prevent rapid repeat scanning
}


