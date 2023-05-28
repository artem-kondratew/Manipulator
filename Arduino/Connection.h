
#ifndef Connection_h
#define Connection_h


#include "Config.h"
#include "Joint.h"
#include "Servo.h"


uint8_t command[COMMAND_SIZE];
uint8_t message[MESSAGE_SIZE];


class Connection {
private:
    static uint8_t crc8(uint8_t data[], int size);
    static uint16_t calcCommandCheckSum();
    static uint16_t calcMessageCheckSum();
    static void setMsgValues(uint8_t id);
    
public:
static void sendMessage(uint8_t id);
    static void receiveCommand();
    
private:
    static void findCommand();
};


uint8_t Connection::crc8(uint8_t data[], int size) {
    uint8_t byte;
    uint8_t POLY = 0x7;
    uint8_t crc8 = 0xFF;

    for (int j = 0; j < size; j++) {

        byte = data[j];
        crc8 = crc8 ^ byte;

        for (int i = 0; i < 8; i++) {

            if (crc8 & 0x80) {
                crc8 = (crc8 << 1) ^ POLY;
            }
            else {
                crc8 = crc8 << 1;
            }
        }
    }
    return crc8;
}


uint16_t Connection::calcCommandCheckSum() {
    return crc8(command, COMMAND_SIZE);
}


uint16_t Connection::calcMessageCheckSum() {
    return crc8(message, MESSAGE_SIZE-1);
}


void Connection::setMsgValues(uint8_t id) {
    Servo* servo = Servo::findServo(id);
    
    message[MESSAGE_START_BYTE1_CELL] = START_BYTE;
    message[MESSAGE_START_BYTE2_CELL] = START_BYTE;
    
    message[MESSAGE_ID_CELL] = id;

    uint16_t angle = servo->get_angle();
    message[MESSAGE_ANGLE1_CELL] = angle / 100;
    message[MESSAGE_ANGLE2_CELL] = angle % 100;

    uint16_t speed = servo->get_speed();
    message[MESSAGE_SPEED1_CELL] = speed / 100;
    message[MESSAGE_SPEED2_CELL] = speed % 100;

    uint16_t load = servo->get_load();
    message[MESSAGE_TORQUE1_CELL] = load / 100;
    message[MESSAGE_TORQUE2_CELL] = load % 100;

    message[MESSAGE_IS_MOVING_CELL] = servo->is_moving();

    int16_t x = joint4.get_x();
    message[MESSAGE_X1_CELL] = 0;//abs(x / 100);
    message[MESSAGE_X2_CELL] = 0;//abs(x % 100);
    message[MESSAGE_X_SIGN] = (x >= 0) ? 1 : 0;

    int16_t y = joint4.get_y();
    message[MESSAGE_Y1_CELL] = 0;//abs(y / 100);
    message[MESSAGE_Y2_CELL] = 0;//abs(y % 100);
    message[MESSAGE_Y_SIGN] = (y >= 0) ? 1 : 0;

    int16_t z = joint4.get_z();
    message[MESSAGE_Z1_CELL] = 0;//abs(z / 100);
    message[MESSAGE_Z2_CELL] = 0;//abs(z % 100);
    message[MESSAGE_Z_SIGN] = (z >= 0) ? 1 : 0;

    message[MESSAGE_CHECKSUM_CELL] = calcMessageCheckSum();
}


void Connection::sendMessage(uint8_t id) {
    setMsgValues(id);

    for (int cell = MESSAGE_START_BYTE1_CELL; cell < MESSAGE_SIZE; cell++) {
        Serial.print(char(message[cell]));
    }
}


void Connection::receiveCommand() {
    if (Serial.available() >= 7) {
        command[COMMAND_START_BYTE1_CELL] = Serial.read();
        command[COMMAND_START_BYTE2_CELL] = Serial.read();
        if (command[COMMAND_START_BYTE1_CELL] == START_BYTE && command[COMMAND_START_BYTE2_CELL] == START_BYTE) {
            for (int cell = COMMAND_ID_CELL; cell < COMMAND_SIZE; cell++) {
                command[cell] = Serial.read();
            }
            if (!calcCommandCheckSum()) {
                findCommand();
                sendMessage(DXL_ID1);
                sendMessage(DXL_ID2);
                sendMessage(DXL_ID3);
                sendMessage(DXL_ID4);
            }
        }
    }
}


void Connection::findCommand() {
    uint16_t value = command[COMMAND_VALUE1_CELL] * 100 + command[COMMAND_VALUE2_CELL];
    uint8_t task = command[COMMAND_TASK_CELL];
    if (task == PING_TASK) {
        return;
    }
    if (task == SET_ANGLE_TASK) {
        return Servo::set_angle(value, command[COMMAND_ID_CELL]);
    }
    if (task == SET_SPEED_TASK) {
        return Servo::set_speed(value, command[COMMAND_ID_CELL]);
    }
    if (task == TOOL_PUSH_TASK) {
        return Servo::toolPush(true);
    }
    if (task == TOOL_POP_TASK) {
        return Servo::toolPop();
    }
    if (task == GO_HOME_TASK) {
        return Servo::setStartPosition();
    }
}


#endif
