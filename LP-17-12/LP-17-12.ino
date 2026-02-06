#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

#define SERVICE_UUID        "12345678-1234-1234-1234-1234567890ab"
#define CHARACTERISTIC_UUID "abcd1234-1234-1234-1234-abcdef123456"

class RGBCallback : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    String value = pCharacteristic->getValue();

    if (value.length() == 3) {
      uint8_t r = value[0];
      uint8_t g = value[1];
      uint8_t b = value[2];

      Serial.print("RGB recibido: ");
      Serial.print(r); Serial.print(", ");
      Serial.print(g); Serial.print(", ");
      Serial.println(b);

      // 🔥 Acá después:
      // strip.setPixelColor(0, r, g, b);
      // strip.show();
    }
  }
};

void setup() {
  Serial.begin(115200);

  BLEDevice::init("ESP32-C3-RGB");

  BLEServer *server = BLEDevice::createServer();
  BLEService *service = server->createService(SERVICE_UUID);

  BLECharacteristic *characteristic =
    service->createCharacteristic(
      CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_WRITE
    );

  characteristic->setCallbacks(new RGBCallback());

  service->start();

  BLEAdvertising *advertising = BLEDevice::getAdvertising();
  advertising->addServiceUUID(SERVICE_UUID);
  advertising->start();

  Serial.println("Esperando conexión BLE...");
}

void loop() {}
