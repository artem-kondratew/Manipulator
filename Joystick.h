#include <iostream.h>
#include <stdint.h>


class Joystick {
private:
    uint8_t analog_port;
    uint16_t analog_value;
public:
    Joystick(unit8_t port, unit16_t value);
    ~Joystick() = default;

    unit16_t getValue();
    unit16_t getDegrees();
  
}


Joystick::Joystick(unit8_t port, unit16_t value) {
    analog_port = port;
    value = analogRead(analog_port);
    
}


unit16_t Joystick::getValue() {
    return value;   
}
