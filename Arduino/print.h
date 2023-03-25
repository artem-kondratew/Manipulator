//
// Created by user on 3/24/23.
//


#ifndef print_h
#define print_h


#include "Config.h"


template<typename T>
void print(T text) {
    if (!PRINT_FLAG) {
        return;
    }
    Serial.print(text);
}


template<typename T>
void println(T text) {
    if (!PRINT_FLAG) {
        return;
    }
    Serial.println(text);
}


#endif
