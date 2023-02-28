
#define DEVICE_NAME "3"

#define BAUDRATE 1000000
#define SERIAL_BAUDRATE 57600

#define DXL_ID1 1
#define DXL_ID2 2
#define DXL_ID3 3
#define DXL_ID4 4

#define ANALOG_PIN1 A0
#define ANALOG_PIN2 A1
#define ANALOG_PIN3 A2
#define ANALOG_PIN4 A3

#define BUTTON_PIN 9


void getStartPosition(DynamixelWorkbench servos) {
    servos.goalPosition(DXL_ID1, 500);
    servos.goalPosition(DXL_ID2, 500);
    servos.goalPosition(DXL_ID3, 500);
    servos.goalPosition(DXL_ID4, 500);
    delay (5000);
}
