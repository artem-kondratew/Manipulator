//
// Created by user on 05.03.23.
//

#ifndef MANIPULATOR_CONNECT_H
#define MANIPULATOR_CONNECT_H


#include <chrono>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>
#include "../Arduino/Config.h"
#include "Exception.h"
#include "Gservo.h"
#include "str.h"


class Connect {
private:
    inline static int Arduino = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NONBLOCK);
    inline static uint8_t command[COMMAND_SIZE];
    inline static uint8_t message[MESSAGE_SIZE];

public:
    inline static str key_cmd;

private:
    static void resetCommand();

    static bool openArduino();

public:
    static bool setConnection();
    static void disconnectArduino();

private:
    static uint8_t crc8(const uint8_t pocket[], uint64_t size);
    static void calcCommandCheckSum();
    static uint8_t calcMessageCheckSum(uint8_t buffer[]);

public:
    static void sendCommand();

private:
    static void setId(uint8_t id);
    static void setTask(uint8_t task);
    static void setValue(uint16_t value);
    static void encodeCommand(uint64_t cmd);

    static void decodeMessage();
    static Gservo* findGservo(uint8_t id);

public:
    static bool receiveMessage();

private:
    static uint64_t checkNumberCommand();

public:
    static void toolPush();
    static void toolPop();
    static void goHome();

    static void decodeKeyInput();
};


inline struct termios SerialPortSettings;


#endif //MANIPULATOR_CONNECT_H
