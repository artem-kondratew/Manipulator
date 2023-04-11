
#include <DynamixelWorkbench.h>
#include "Calibration.h"
#include "Connection.h"
#include "Config.h"
#include "Joint.h"
#include "Servo.h"


void setup() {

    Serial.begin(SERIAL_BAUDRATE);
    Serial.setTimeout(0);

    Servo::init();
    Servo::pingServos();

    servo1.setSpeed(DEFAULT_SPEED);
    servo2.setSpeed(DEFAULT_SPEED);
    servo3.setSpeed(DEFAULT_SPEED);
    servo4.setSpeed(DEFAULT_SPEED);

    Servo::getStartPosition();
    //Servo::Calibration_setup();
    //Servo::getStartPosition();
}


void loop() {
    Connection::receiveCommand();
    //Servo::talk(Serial.parseInt());
    //Servo::anglePrint();
}
