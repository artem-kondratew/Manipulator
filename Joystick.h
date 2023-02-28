
#include <stdint.h>


class Joystick {
private:
    uint8_t PIN;
    uint16_t value;
public:
    Joystick(uint8_t _PIN);
    ~Joystick() = default;

    uint16_t getValue();
    void setValue();
    static void refresh();
    static bool checkAngles();
};


Joystick joystick1(ANALOG_PIN1);
Joystick joystick2(ANALOG_PIN2);
Joystick joystick3(ANALOG_PIN3);
Joystick joystick4(ANALOG_PIN4);


Joystick::Joystick(uint8_t _PIN) {
    PIN = _PIN;
    value = 0;
}


uint16_t Joystick::getValue() {
    return value;   
}


void Joystick::setValue() {
    if (abs(value - analogRead(PIN)) < 5) {
        return;
    }
    value = analogRead(PIN);
}


void Joystick::refresh() {
    joystick1.setValue();
    joystick2.setValue();
    joystick3.setValue();
    joystick4.setValue();
}


bool Joystick::checkAngles() {
    uint16_t alpha = joystick2.value * 120 / 1024 /180 * 3.14;
    uint16_t beta = ((joystick3.value - 270) * 70 / 754 + 145) / 180 * 3.14;
    if (sin(alpha) + sin(beta) > -0.6) {
        return 0;
    }
    return 1;
}
