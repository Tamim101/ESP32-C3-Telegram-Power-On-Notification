
#include <WiFi.h>
#include <HTTPClient.h>
#include "soc/soc.h"          // For brownout detector
#include "soc/rtc_cntl_reg.h" // For brownout detector

// ====== Wi-Fi Credentials ======
const char* ssid = "Tamim-wifi";
const char* password = "Tamims9047@";

// ====== Telegram Bot Info ======
const char* botToken = "8243146761:AAHdU1pmAI2oxFfFHDNmsFi-SG9x1aWHO4U";
const char* chatIDs[] = { "6259013308", "2017577128", "7289612958", "6198271608", "5569079543" };
const int phoneCount = 5;

// ====== Buzzer ======
const int buzzerPin = 18; // Adjust if different for your ESP32-C3 setup
bool buzzerActive = false;
unsigned long buzzerStartTime = 0;

// ====== RTC Data to Persist Across Resets ======
RTC_DATA_ATTR bool messageSent = false;

// ====== Function to send Telegram message ======
void sendTelegramMessage(String message);

void setup() {
  // Disable brownout detector to prevent resets
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);

  Serial.begin(115200);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  Serial.println("🔄 Connecting to Wi-Fi...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // Wait for Wi-Fi connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n✅ Wi-Fi Connected!");

  // Send message to all chat IDs once connected, if not already sent
  if (!messageSent) {
    Serial.println("⚡ Power ON: Sending Telegram + Buzzer ON");
    sendTelegramMessage("⚡ ESP32-C3 Power ON & Turn off Generator ✅");
    digitalWrite(buzzerPin, HIGH);
    buzzerActive = true;
    buzzerStartTime = millis();
    messageSent = true; // Persists across resets due to RTC_DATA_ATTR
  }
}

void loop() {
  // Turn off buzzer after 5 seconds
  if (buzzerActive && (millis() - buzzerStartTime >= 5000)) {
    digitalWrite(buzzerPin, LOW);
    buzzerActive = false;
    Serial.println("🔕 Buzzer OFF");
  }
  delay(1000); // Keep loop lightweight
}

// ====== Function Implementation ======
void sendTelegramMessage(String message) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    for (int i = 0; i < phoneCount; i++) {
      String url = "https://api.telegram.org/bot" + String(botToken) + "/sendMessage?chat_id=" + String(chatIDs[i]) + "&text=" + message;
      Serial.print("📤 Sending message to chat ID: ");
      Serial.println(chatIDs[i]);
      http.begin(url);
      int httpCode = http.GET();
      if (httpCode == 200) {
        Serial.print("✅ Message sent successfully to chat ID: ");
        Serial.println(chatIDs[i]);
      } else {
        Serial.print("❌ Failed to send message to chat ID: ");
        Serial.print(chatIDs[i]);
        Serial.print(", HTTP Code: ");
        Serial.println(httpCode);
      }
      http.end();
      delay(500); // Avoid overwhelming the Telegram API
    }
  } else {
    Serial.println("⚠️ Wi-Fi not connected. Cannot send messages.");
  }
}