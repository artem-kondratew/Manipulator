
#include <stdint.h>
#include <string>
#include <DynamixelWorkbench.h>


#define pi 512


DynamixelWorkbench servos;


class Servo {
private:
    uint8_t DXL_ID;
    uint16_t min_angle;
    uint16_t max_angle;
    uint16_t angle;
public:
    Servo(uint8_t _DXL_ID, uint16_t _min_angle, uint16_t _max_angle);
    ~Servo() = default;
    void pingServo();
    void setAngle(uint16_t _angle);
    uint16_t getAngle();
    static void talk(uint16_t _angle);
};


Servo servo1(DXL_ID1, 150, 853);
Servo servo2(DXL_ID2, 0, 550);
Servo servo3(DXL_ID3, 250, 800);
Servo servo4(DXL_ID4, 0, 1023);


Servo::Servo(uint8_t _DXL_ID, uint16_t _min_angle, uint16_t _max_angle) {
    DXL_ID = _DXL_ID;
    min_angle = _min_angle;
    max_angle = _max_angle;
    angle = 0;
}


void Servo::pingServo() {
    servos.ping(DXL_ID, 0, 0);
}


void Servo::setAngle(uint16_t _angle) {
    if (DXL_ID == 2) {
        
    }
    if (_angle < min_angle) {
        angle = min_angle;
        servos.goalPosition(DXL_ID, angle);
        return;
    }
    if (_angle > max_angle) {
      angle = max_angle;
        servos.goalPosition(DXL_ID, angle);
        return;
    }
    angle = _angle;
    servos.goalPosition(DXL_ID, angle);
}


uint16_t Servo::getAngle() {
    return angle;
}


void Servo::talk(uint16_t msg) {
    uint8_t id = msg / 10000;
    uint16_t _angle = msg % 10000;
    if (id == 1) {
      servo1.setAngle(_angle);
    }
    if (id == 2) {
      servo2.setAngle(_angle);
    }
    if (id == 3) {
      servo3.setAngle(_angle);
    }
    if (id == 4) {
      servo4.setAngle(_angle);
    }
}

void anglePrint() {
    Serial.print("\nangle1: ");
    Serial.println(servo1.getAngle());
    Serial.print("angle2: ");
    Serial.println(servo2.getAngle());
    Serial.print("angle3: ");
    Serial.println(servo3.getAngle());
    Serial.print("angle4: ");
    Serial.println(servo4.getAngle());
}
