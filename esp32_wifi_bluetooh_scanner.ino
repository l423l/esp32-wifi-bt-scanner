#include <WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <BLEDevice.h>
#include <BLEScan.h>

// =====================
// PIN TANIMLARI / PIN DEFINITIONS
// =====================
#define SDA_PIN 19
#define SCL_PIN 18
int redPin   = 23;
int greenPin = 22;
int bluePin  = 21;

LiquidCrystal_I2C lcd(0x27, 16, 2);
BLEScan* pBLEScan;

// =====================
// LED KONTROL / LED CONTROL
// =====================
void setColor(bool r, bool g, bool b) {
  digitalWrite(redPin,   r ? LOW : HIGH);
  digitalWrite(greenPin, g ? LOW : HIGH);
  digitalWrite(bluePin,  b ? LOW : HIGH);
}

// =====================
// KURULUM / SETUP
// =====================
void setup() {
  Serial.begin(115200);

  pinMode(redPin,   OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin,  OUTPUT);

  Wire.begin(SDA_PIN, SCL_PIN);
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("WiFi & BT");
  lcd.setCursor(0, 1);
  lcd.print("Scanner");
  delay(2000);

  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan();
  pBLEScan->setActiveScan(true);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
}

void loop() {

  // =====================
  // WIFI TARAMA / WIFI SCAN
  // =====================
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi Scanning...");
  setColor(false, false, true); // Mavi / Blue

  int networkCount = WiFi.scanNetworks();

  Serial.println("======================");
  Serial.print(networkCount);
  Serial.println(" WiFi networks found:");
  Serial.println("======================");

  for (int i = 0; i < networkCount; i++) {
    String ssid = WiFi.SSID(i);
    int rssi    = WiFi.RSSI(i);

    Serial.print(i + 1);
    Serial.print(". ");
    Serial.print(ssid);
    Serial.print("  Signal: ");
    Serial.print(rssi);
    Serial.println(" dBm");

    lcd.clear();
    lcd.setCursor(0, 0);
    if (ssid.length() > 16) {
      lcd.print(ssid.substring(0, 16));
    } else {
      lcd.print(ssid);
    }
    lcd.setCursor(0, 1);
    lcd.print("Signal:");
    lcd.print(rssi);
    lcd.print("dBm");

    if (rssi >= -50) {
      setColor(false, true, false); // Yeşil / Green — Güçlü / Strong
    } else if (rssi >= -70) {
      setColor(false, true, true);  // Camgöbeği / Cyan — Orta / Medium
    } else {
      setColor(true, false, false); // Kırmızı / Red — Zayıf / Weak
    }

    delay(2000);
  }

  // =====================
  // BLUETOOTH TARAMA / BLUETOOTH SCAN
  // =====================
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("BT Scanning...");
  setColor(true, false, true); // Mor / Purple

  Serial.println("======================");
  Serial.println("Scanning Bluetooth...");
  Serial.println("======================");

  BLEScanResults* foundDevices = pBLEScan->start(5, false);
  int btCount = foundDevices->getCount();

  Serial.print(btCount);
  Serial.println(" BT devices found:");

  for (int i = 0; i < btCount; i++) {
    BLEAdvertisedDevice device = foundDevices->getDevice(i);
    String btName = device.getName().c_str();
    int btRssi    = device.getRSSI();

    if (btName == "") btName = "Unknown";

    Serial.print(i + 1);
    Serial.print(". ");
    Serial.print(btName);
    Serial.print("  Signal: ");
    Serial.print(btRssi);
    Serial.println(" dBm");

    lcd.clear();
    lcd.setCursor(0, 0);
    if (btName.length() > 16) {
      lcd.print(btName.substring(0, 16));
    } else {
      lcd.print(btName);
    }
    lcd.setCursor(0, 1);
    lcd.print("BT:");
    lcd.print(btRssi);
    lcd.print("dBm");

    setColor(true, false, true); // Mor / Purple
    delay(2000);
  }

  pBLEScan->clearResults();

  // =====================
  // SONUÇ / SUMMARY
  // =====================
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi:");
  lcd.print(networkCount);
  lcd.print(" BT:");
  lcd.print(btCount);
  lcd.setCursor(0, 1);
  lcd.print("Refreshing...");
  setColor(true, true, false); // Sarı / Yellow

  delay(5000);
}