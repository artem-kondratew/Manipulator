//
// Created by user on 05.03.23.
//

#ifndef MANIPULATOR_GRAPHICS_H
#define MANIPULATOR_GRAPHICS_H


#include <csignal>
#include <sys/ioctl.h>
#include "ncurses.h"
#include "Connect.h"


#define KEY_RETURN  10

#define ID_X         9
#define GOAL_X      17
#define ANGLE_X     23
#define SPEED_X     34
#define BOOST_X     41
#define TORQUE_X    52
#define IS_MOVING_X 62


int CURS_Y = 0;
int CURS_X = 0;


int get_columns() {
    struct winsize window{};
    ioctl(0, TIOCGWINSZ, &window);
    return window.ws_col;
}


void finish() {
    clear();
    refresh();
    resetty();
    endwin();
    exit(0);
}


void sigHandler(int sig) {
    if (sig == SIGINT) {
        finish();
    }
}


void print_table() {
    for (int i = 1; i < 5; i++) {
        move(i + 1, 0);
        printw("servo%d", i);
    }

    move(0, ID_X);
    printw("id");

    move(0, GOAL_X);
    printw("goal");
    move(0, ANGLE_X);
    printw("angle");

    move(0, SPEED_X);
    printw("speed");
    move(0, BOOST_X);
    printw("boost");

    move(0, TORQUE_X);
    printw("torque");

    move(0, IS_MOVING_X);
    printw("is_moving");

    move(7, 0);
    printw("Set command:");

    refresh();
}


void print_id() {
    for (int i = 1; i < 5; i++) {
        move(i + 1, 9);
        printw("%d", i);
    }
    refresh();
}


void initGraphics() {
    initscr();
    savetty();  //  save terminal settings

    //nonl();  //  deny going to the new line

    cbreak();  //  буфер передается после нажатия enter
    echo();  //  отображается печать символов
    //timeout(0); //  буфер передается без нажатия enter

    //leaveok(stdscr, TRUE);  //  сдвиг курсора - нормально
    //curs_set(0);  //  hide cursor
    keypad(stdscr, TRUE);

    signal(SIGINT, sigHandler);

    clear();
    print_table();
    print_id();
    move(8, 0);
    refresh();
}


void clear_command_line() {
    move(8, 0);
    for (int i = 0; i < get_columns(); i++) {
        printw(" ");
    }
    move(8, 0);
    refresh();
}


void print_last_command() {
    move(9, 0);
    for (int i = 0; i < get_columns(); i++) {
        printw(" ");
    }
    move(9, 0);
    printw("%s", Connect::key_cmd.get());
}


void print_command_line() {
    move(8, 0);
    printw("%s", Connect::key_cmd.get());
}


void print_goal(uint8_t servo, uint16_t goal) {
    move(1 + servo, GOAL_X);
    printw("%d", goal);
}


void print_angle(uint8_t servo, uint16_t angle) {
    move(1 + servo, ANGLE_X);
    printw("%d", angle);
}


void print_speed(uint8_t servo, uint16_t speed) {
    move(1 + servo, SPEED_X);
    printw("%d", speed);
}


void print_boost(uint8_t servo, uint16_t boost) {
    move(1 + servo, BOOST_X);
    printw("%d", boost);
}


void print_torque(uint8_t servo, uint16_t torque) {
    move(1 + servo, TORQUE_X);
    printw("%d", torque);
}

void print_is_moving(uint8_t servo, uint16_t is_moving) {
    move(1 + servo, IS_MOVING_X);
    printw("%d", is_moving);
}


#endif //MANIPULATOR_GRAPHICS_H
