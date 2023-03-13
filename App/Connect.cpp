//
// Created by user on 05.03.23.
//

#include "Connect.h"


bool Connect::openArduino() {
    if (Arduino == -1) {
        Arduino = open("/dev/ttyACM1", O_RDWR | O_NOCTTY | O_NONBLOCK);
        if (Arduino == -1) {
            return false;
        }
        return true;
    }
    return true;
}


void Connect::clearCommand() {
    command[0] = START_BYTE;
    command[1] = START_BYTE;
    command[2] = CONNECT_DXL_ID;
    command[3] = CONNECT_TASK;
    command[4] = CONNECT_VALUE;
    command[5] = CONNECT_VALUE;
    calcCommandCheckSum();
}


void Connect::setConnection() {
    if (!openArduino()) {
        std::cout << "Unable to connect" << std::endl;
        return;
    }
    clearCommand();
    message_flag = false;
    std::cout << "connecting..." << std::endl;
    auto start_timer = std::chrono::system_clock::now();
    while (!message_flag) {
        auto end_timer = std::chrono::system_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(end_timer - start_timer).count() > int(TIMER)) {
            sendCommand();
            receiveMessage();
            start_timer = std::chrono::system_clock::now();
        }
    }
    sleep(2);
    std::cout << "connected" << std::endl;
}


void Connect::calcCommandCheckSum() {
    command[CHECKSUM_CELL] = char((command[2] + command[3] + command[4] + command[5]) / 8);
}


char Connect::calcMessageCheckSum(const char buffer[]) {
    return char((buffer[2] + buffer[3] + buffer[4] + buffer[5]) / 8);
}


void Connect::sendCommand() {
    if (!openArduino()) {
        return;
    }
    calcCommandCheckSum();
    write(Arduino, command, COMMAND_SIZE);
}


void Connect::receiveMessage() {
    message_flag = false;
    if (!openArduino()) {
        return;
    }

    char buffer[MESSAGE_SIZE];
    read(Arduino, buffer, MESSAGE_SIZE);

    if (buffer[0] == 64 && buffer[1] == 64 && buffer[MESSAGE_SIZE - 1] == calcMessageCheckSum(buffer)) {
        std::memcpy(message, buffer, sizeof(char) * MESSAGE_SIZE);
        message_flag = true;
        std::cout << "pocket: ok " << message << std::endl;
        return;
    }
    std::cout << "pocket: fail " << (int) buffer[MESSAGE_SIZE - 1] << " ";
    std::cout << (int) calcMessageCheckSum(buffer) << std::endl;
}


void Connect::setId(char id) {
    command[ID_CELL] = id;
}


void Connect::setTask(char task) {
    command[TASK_CELL] = task;
}


void Connect::setValue(uint16_t value) {
    command[VALUE1_CELL] = char(value / 100);
    command[VALUE2_CELL] = char(value % 100);
}


void Connect::encodeCommand(uint64_t com) {
    char id = char(com / 100000);
    setId(id);

    char task = char((com % 100000) / 10000);
    setTask(task);

    uint16_t value = com % 10000;
    setValue(value);
}
