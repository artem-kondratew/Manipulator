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

/*
class Exception: std::exception {
private:
    std::string message;
public:
    explicit Exception(std::string _message) {message = std::move(_message);};

    std::string getMessage() const {return message;};
};*/


class Connect {
private:
    inline static int Arduino = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NONBLOCK);
public:
    inline static char command[COMMAND_SIZE];
    inline static char message[MESSAGE_SIZE];
    inline static str key_cmd;

    static void clearCommand();

    static bool openArduino();

    static void setConnection();

    static void disconnectArduino();

    static void calcCommandCheckSum();

    static char calcMessageCheckSum(const char buffer[]);

    static void sendCommand();

    static void setId(char id);

    static void setTask(char task);

    static void setValue(uint16_t value);

    static void encodeCommand(uint64_t cmd);

    static bool receiveMessage();

    static void decodeMessage();

    static void decodeKeyInput();
};


inline struct termios SerialPortSettings;


#endif //MANIPULATOR_CONNECT_H
