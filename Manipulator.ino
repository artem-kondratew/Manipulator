
#include <DynamixelWorkbench.h>
#include "Config.h"
#include "Servo.h"
#include "Connection.h"


void setup() {

    pinMode(ANALOG_PIN1, INPUT);
    pinMode(ANALOG_PIN2, INPUT);
    pinMode(ANALOG_PIN3, INPUT);
    pinMode(ANALOG_PIN4, INPUT);

    Serial.begin(SERIAL_BAUDRATE);
    Serial.setTimeout(0);

    servos.init(DEVICE_NAME, SERVO_BAUDRATE);
    Servo::pingServos();

    servo1.setMoveMode(40, 40);
    servo2.setMoveMode(40, 40);
    servo3.setMoveMode(40, 40);
    servo4.setMoveMode(100, 40);

    

    Servo::getStartPosition();
}


void loop() {
    Connection::getData();
    //Servo::talk(Serial.parseInt());
    //Servo::anglePrint();
}
