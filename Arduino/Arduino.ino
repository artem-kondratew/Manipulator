
#include <DynamixelWorkbench.h>
#include "Calibration.h"
#include "Config.h"
#include "Connection.h"
#include "Joint.h"
#include "Servo.h"


void setup() {
    Serial.begin(SERIAL_BAUDRATE);
    Serial.setTimeout(0);

    Servo::init();
    Servo::pingServos();

    servo1.set_speed(DEFAULT_SPEED);
    servo2.set_speed(DEFAULT_SPEED);
    servo3.set_speed(DEFAULT_SPEED);
    servo4.set_speed(DEFAULT_SPEED);

    Servo::setStartPosition();
    Servo::toolPop();
}


void loop() {
    Connection::receiveCommand();
    //Servo::mv(Serial.parseInt());
}
