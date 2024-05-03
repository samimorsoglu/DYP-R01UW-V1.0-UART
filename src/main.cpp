#include <Arduino.h>

#define RX_PIN 18 // Sensörün TX pininin bağlı olduğu ESP32 pin numarası 
#define TX_PIN 17 // Sensörün RX pininin bağlı olduğu ESP32 pin numarası 

int distance =0;
volatile bool newData = false;
void handleInterrupt() {
  newData = true;
}

void setup() {
  Serial.begin(115200); 
  Serial1.begin(115200, SERIAL_8N1, RX_PIN, TX_PIN); 

  attachInterrupt(digitalPinToInterrupt(RX_PIN), handleInterrupt, FALLING);
}

void sensorcheck() {
  while (Serial1.available() >= 4) { 
    uint8_t data[4];
    for (int i = 0; i < 4; i++) {
      data[i] = Serial1.read();
    }

    uint8_t frame = data[0];
    uint8_t data_h = data[1];
    uint8_t data_l = data[2];
    uint8_t sum = data[3];

    distance = (data_h * 256) + data_l;

  }

}
void loop() {
  if (newData) { 
    sensorcheck();
    newData = false; 
  }
  Serial.println(distance);
  delay(2000);
  
}

