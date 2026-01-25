#include <Arduino.h>
#include <WiFi.h>

/*
 * Wi-Fi Scanner for ESP32
 * Compatible with PlatformIO + Arduino framework
 * Supports 2.4 GHz / 5 GHz (if SoC allows)
 */

static void scanWiFi()
{
  Serial.println("Scan start");

  // Blocking scan
  int n = WiFi.scanNetworks();
  Serial.println("Scan done");

  if (n <= 0) {
    Serial.println("No networks found");
  } else {
    Serial.printf("%d networks found\n", n);
    Serial.println("Nr | SSID                             | RSSI | CH | Encryption");

    for (int i = 0; i < n; ++i) {
      Serial.printf("%2d | ", i + 1);
      Serial.printf("%-32.32s | ", WiFi.SSID(i).c_str());
      Serial.printf("%4d | ", WiFi.RSSI(i));
      Serial.printf("%2d | ", WiFi.channel(i));

      switch (WiFi.encryptionType(i)) {
        case WIFI_AUTH_OPEN:            Serial.print("OPEN"); break;
        case WIFI_AUTH_WEP:             Serial.print("WEP"); break;
        case WIFI_AUTH_WPA_PSK:         Serial.print("WPA"); break;
        case WIFI_AUTH_WPA2_PSK:        Serial.print("WPA2"); break;
        case WIFI_AUTH_WPA_WPA2_PSK:    Serial.print("WPA+WPA2"); break;
        case WIFI_AUTH_WPA2_ENTERPRISE: Serial.print("WPA2-EAP"); break;
        case WIFI_AUTH_WPA3_PSK:        Serial.print("WPA3"); break;
        case WIFI_AUTH_WPA2_WPA3_PSK:   Serial.print("WPA2+WPA3"); break;
        case WIFI_AUTH_WAPI_PSK:        Serial.print("WAPI"); break;
        default:                        Serial.print("UNKNOWN");
      }

      Serial.println();
      delay(5);
    }
  }

  // Free RAM
  WiFi.scanDelete();
  Serial.println("-------------------------------------");
}

void setup()
{
  Serial.begin(115200);
  delay(200);

  Serial.println();
  Serial.println("ESP32 Wi-Fi Scanner starting...");

  // Station mode only
  WiFi.mode(WIFI_STA);
  WiFi.disconnect(true);
  delay(100);

  Serial.println("Wi-Fi initialized in STA mode");
}

void loop()
{
  Serial.println();
  Serial.println("-------------------------------------");
  Serial.println("Default Wi-Fi band scan");
  Serial.println("-------------------------------------");

#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 4, 2)
  WiFi.setBandMode(WIFI_BAND_MODE_AUTO);
#endif
  scanWiFi();

#if CONFIG_SOC_WIFI_SUPPORT_5G
  delay(1000);

  Serial.println("-------------------------------------");
  Serial.println("2.4 GHz band scan");
  Serial.println("-------------------------------------");
  WiFi.setBandMode(WIFI_BAND_MODE_2G_ONLY);
  scanWiFi();

  delay(1000);

  Serial.println("-------------------------------------");
  Serial.println("5 GHz band scan");
  Serial.println("-------------------------------------");
  WiFi.setBandMode(WIFI_BAND_MODE_5G_ONLY);
  scanWiFi();
#endif

  // Repeat every 10 seconds
  delay(10000);
}
