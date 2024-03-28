#include <HardwareSerial.h>

#define RX_PIN 16 // Sensörün TX pininin bağlı olduğu ESP32 pin numarası 
#define TX_PIN 17 // Sensörün RX pininin bağlı olduğu ESP32 pin numarası 

HardwareSerial sensorSerial(1); 

void setup() {
  Serial.begin(115200); 
  sensorSerial.begin(115200, SERIAL_8N1, RX_PIN, TX_PIN); 
}

void loop() {
  if (sensorSerial.available() >= 4) { 
    uint8_t data[4];
    for (int i = 0; i < 4; i++) {
      data[i] = sensorSerial.read();
    }

    uint8_t frame = data[0];
    uint8_t data_h = data[1];
    uint8_t data_l = data[2];
    uint8_t sum = data[3];

    Serial.print("Frame: "); Serial.println(frame);
    Serial.print("Data_H: "); Serial.println(data_h);
    Serial.print("Data_L: "); Serial.println(data_l);
    Serial.print("Sum: "); Serial.println(sum);
  }
  
  delay(100); 
}
