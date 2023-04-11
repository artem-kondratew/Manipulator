
#ifndef Connection_h
#define Connection_h


#include "Config.h"
//#include "FSM.h"
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
    
    message[MESSAGE_GOAL1_CELL] = servo->getGoal() / 100;
    message[MESSAGE_GOAL1_CELL] = servo->getGoal() % 100;
    
    message[MESSAGE_ANGLE1_CELL] = servo->getAngle() / 100;
    message[MESSAGE_ANGLE2_CELL] = servo->getAngle() % 100;
    
    message[MESSAGE_SPEED1_CELL] = servo->getSpeed() / 100;
    message[MESSAGE_SPEED2_CELL] = servo->getSpeed() % 100;
    
    message[MESSAGE_TORQUE1_CELL] = servo->getLoad() / 100;
    message[MESSAGE_TORQUE2_CELL] = servo->getLoad() % 100;

    message[MESSAGE_IS_MOVING_CELL] = servo->isMoving();

    message[MESSAGE_X1_CELL] = 12;
    message[MESSAGE_X2_CELL] = 13;
    message[MESSAGE_Y1_CELL] = 14;
    message[MESSAGE_Y2_CELL] = 15;
    message[MESSAGE_Z1_CELL] = 16;
    message[MESSAGE_Z2_CELL] = 17;

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
    if (command[COMMAND_TASK_CELL] == PING_TASK) {
        return;
    }
    if (command[COMMAND_TASK_CELL] == SET_ANGLE_TASK) {
        return Servo::setAngle(value, command[COMMAND_ID_CELL]);
    }
    if (command[COMMAND_TASK_CELL] == SET_SPEED_TASK) {
        return Servo::setSpeed(value, command[COMMAND_ID_CELL]);
    }
    if (command[COMMAND_TASK_CELL] == TOOL_PUSH_TASK) {
        return Servo::toolPush();
    }
    if (command[COMMAND_TASK_CELL] == TOOL_POP_TASK) {
        return Servo::toolPop();
    }
    if (command[COMMAND_TASK_CELL] == CALIBRATION_TASK) {
        return;
    }
    if (command[COMMAND_TASK_CELL] == REBOOT_TASK) {
        return;
    }
    if (command[COMMAND_TASK_CELL] == GET_ERROR_TASK) {
        return;
    }
    if (command[COMMAND_TASK_CELL] == SET_X_TASK) {
        return Joint::setX(value);
    }
    if (command[COMMAND_TASK_CELL] == SET_Y_TASK) {
        return Joint::setY(value);
    }
    if (command[COMMAND_TASK_CELL] == SET_Z_TASK) {
        return Joint::setZ(value);
    }
    if (command[COMMAND_TASK_CELL] == GO_HOME_TASK) {
        return Servo::getStartPosition();
    }
}


#endif
