//
// Created by user on 05.03.23.
//

#include "Connect.h"


bool Connect::openArduino() {
    if (Arduino == -1) {
        std::cout << "Unable to open /dev/ttyACM0" << std::endl;
        return false;
    }
    return true;
}


void Connect::clearCommand() {
    command[0] = START_BYTE;
    command[1] = START_BYTE;
    command[2] = CONNECT_DXL_ID;
    command[3] = CONNECT_TASK;
    command[4] = CONNECT_MID;
    command[5] = CONNECT_MID;
    calcCommandCheckSum();
}


bool Connect::setConnection() {
    if (!openArduino()) {
        return false;
    }
    clearCommand();
    bool flag = false;
    std::cout << "connecting..." << std::endl;
    while (!flag) {
        sendCommand();
        sleep(1);
        receiveMessage();
        if (message[0] == 64 && message[1] == 64 && message[MESSAGE_SIZE - 1] == calcMessageCheckSum()) {
            sleep(1);
            std::cout << "connected" << std::endl;
            flag = true;
        }
    }
}


void Connect::calcCommandCheckSum() {
    command[6] = char((command[2] + command[3] + command[4] + command[5]) / 8);
}


char Connect::calcMessageCheckSum() {
    return char((message[2] + message[3] + message[4] + message[5]) / 8);
}


void Connect::sendCommand() {
    calcCommandCheckSum();
    write(Arduino, Connect::command, COMMAND_SIZE);
}


void Connect::receiveMessage() {
    read(Arduino, Connect::message, MESSAGE_SIZE);
    std::cout << Connect::message << std::endl;
    for (char i: Connect::message) {
        std::cout << int(i) << std::endl;
    }
    std::cout << "check: " << (int)calcMessageCheckSum() << std::endl;
    if (checkMessage()) {
        std::cout << "pocket: ok" << std::endl;
    }
    else {
        std::cout << "pocket: fail" << std::endl;
    }
}


bool Connect::checkMessage() {
    return message[MESSAGE_SIZE-1] == calcMessageCheckSum();
}
