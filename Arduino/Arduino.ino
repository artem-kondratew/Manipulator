
#include <DynamixelWorkbench.h>
#include "Calibration.h"
#include "Config.h"
#include "Connection.h"
#include "Joint.h"
#include "Servo.h"


unsigned long long int tool_timer;
unsigned long long int now;


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

    tool_timer = millis();
}


void loop() {
    Connection::receiveCommand();
    //Servo::mv(Serial.parseInt());
    now = millis();
    if (now - tool_timer > TOOL_TIMER) {
        Servo::toolPush();
        tool_timer = now;
    }
}
