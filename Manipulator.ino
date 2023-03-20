
#include <DynamixelWorkbench.h>
#include "Config.h"
#include "Servo.h"
#include "Node.h"


void setup() {

    pinMode(ANALOG_PIN1, INPUT);
    pinMode(ANALOG_PIN2, INPUT);
    pinMode(ANALOG_PIN3, INPUT);
    pinMode(ANALOG_PIN4, INPUT);

    Serial.begin(SERIAL_BAUDRATE);

    servos.init(DEVICE_NAME, BAUDRATE);

    servo1.pingServo();
    servo2.pingServo();
    servo3.pingServo();
    servo4.pingServo();
    
    servos.jointMode(DXL_ID1, 100, 40);
    servos.jointMode(DXL_ID2, 100, 40);
    servos.jointMode(DXL_ID3, 100, 40);
    servos.jointMode(DXL_ID4, 100, 40);
    
    Servo::getStartPosition();
}


void loop() {
  
    //Joystick::refresh();
/*
    servo1.setAngle(joystick1.getValue());
    servo2.setAngle(joystick2.getValue());
    servo3.setAngle(joystick3.getValue());
    servo4.setAngle(joystick4.getValue());
*/
    Servo::talk(Serial.parseInt());
    Servo::anglePrint();

    Joint::getAngles();
    
}
