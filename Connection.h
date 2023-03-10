
#ifndef Connection_h
#define Connection_h


#include "Config.h"
#include "Servo.h"


uint8_t id = 0;
uint8_t command = 0;
uint16_t value1 = 0;
uint16_t value2 = 0;
uint16_t value = 0;
uint16_t checksum = 0;


class Connection {
public:
    static uint16_t calc();
    static void setData();
    static void getData();
    static void findCommand();
};


uint16_t Connection::calc() {
    return (char(id) + char(command) + char(value1) + char(value2)) / 8;
}


void Connection::setData() {
    Serial.print(char(64));
    Serial.print(char(64));
    Serial.print(char(id));
    Serial.print(char(command));
    Serial.print(char(value1));
    Serial.print(char(value2));
    Serial.print(char(calc()));
}


void Connection::getData() {
  if (Serial.available() >= 7) {
      byte start1 = Serial.read();
      byte start2 = Serial.read();
      if (start1 + start2 == 128) {
          id = Serial.read();
          command = Serial.read();
          value1 = Serial.read();
          value2 = Serial.read();
          checksum = Serial.read();
      if (calc() == checksum) {
          findCommand();
          setData();
      }
    }
  }
}


void Connection::findCommand() {
    value = value1 * 100 + value2;
    if (command == 0) {
        
    }
    if (command == 1) {
        Servo::setAngle(value, id);
    }
}


#endif
