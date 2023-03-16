
#include <DynamixelWorkbench.h>
#include "Config.h"
#include "Servo.h"
#include "Connection.h"


void setup() {

    Serial.begin(SERIAL_BAUDRATE);
    Serial.setTimeout(0);

    Servo::init();
    Servo::pingServos();

    servo1.setMoveMode(100, 40);
    servo2.setMoveMode(40, 40);
    servo3.setMoveMode(40, 40);
    servo4.setMoveMode(100, 40);

    Servo::getStartPosition();
    Servo::Calibration_setup();
    Servo::getStartPosition();
}


void loop() {

    // Serial.print(servo2.getLoad());
    // Serial.print(",");
    // Serial.print(servo3.getLoad());
    // Serial.println();
    // delay(20);

    //Servo::talk(Serial.parseInt());
    //Servo::anglePrint();
}
