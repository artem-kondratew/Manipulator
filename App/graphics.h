//
// Created by user on 05.03.23.
//

#ifndef MANIPULATOR_GRAPHICS_H
#define MANIPULATOR_GRAPHICS_H


#include <csignal>
#include <sys/ioctl.h>
#include "ncurses.h"
#include "Connect.h"


#define KEY_RETURN     10

#define ID_X            9
#define GOAL_X         17
#define ANGLE_X        23
#define SPEED_X        34
#define BOOST_X        41
#define TORQUE_X       52
#define IS_MOVING_X    62

#define COMMAND_Y       8
#define LAST_COMMAND_Y  9


int CURS_Y = 0;
int CURS_X = 0;


int get_columns() {
    struct winsize window{};
    ioctl(0, TIOCGWINSZ, &window);
    return window.ws_col;
}


void finish() {
    Connect::disconnectArduino();
    clear();
    refresh();
    resetty();
    endwin();
    exit(0);
}


void sighandler(int sig) {
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
        move(i + 1, ID_X + 1);
        printw("%d", i);
    }
    refresh();
}


void init_graphics() {
    initscr();
    savetty();  //  save terminal settings

    //nonl();  //  deny going to the new line

    cbreak();  //  send buffer after pressing enter
    echo();  //  visible printing
    //timeout(0);

    //leaveok(stdscr, TRUE);
    //curs_set(0);  //  hide cursor
    keypad(stdscr, TRUE);

    signal(SIGINT, sighandler);

    clear();
    print_table();
    print_id();
    move(8, 0);
    refresh();
}


void clear_command_line() {
    move(COMMAND_Y, 0);
    for (int i = 0; i < get_columns(); i++) {
        printw(" ");
    }
    move(COMMAND_Y, 0);
    refresh();
}


void print_last_command() {
    move(LAST_COMMAND_Y, 0);
    for (int i = 0; i < get_columns(); i++) {
        printw(" ");
    }
    move(LAST_COMMAND_Y, 0);
    printw("%s", Connect::key_cmd.get());
}


void print_command_line() {
    move(COMMAND_Y, 0);
    printw("%s", Connect::key_cmd.get());
}


void key_return_proc() {
    //Connect::decodeKeyInput(command);
    print_last_command();
    clear_command_line();
    Connect::key_cmd.reset();
}


void key_backspace_proc() {
    getsyx(CURS_Y, CURS_X);
    Connect::key_cmd.setCurs(CURS_X + 1);
    Connect::key_cmd.keyBackspace();
    clear_command_line();
    print_command_line();
    move(CURS_Y, CURS_X);
}


void key_delete_proc() {
    getsyx(CURS_Y, CURS_X);
    Connect::key_cmd.setCurs(CURS_X);
    Connect::key_cmd.keyDelete();
    clear_command_line();
    print_command_line();
    move(CURS_Y, CURS_X);
}


void key_left_proc() {
    getsyx(CURS_Y, CURS_X);
    move(CURS_Y, CURS_X - 1);
}


void key_right_proc() {
    getsyx(CURS_Y, CURS_X);
    if (CURS_X == Connect::key_cmd.size()) {
        return;
    }
    move(CURS_Y, CURS_X + 1);
}

void key_proc(int key) {
    char symbol = (char)key;
    if (key == KEY_RETURN) {
        return key_return_proc();
    }
    if (key == KEY_BACKSPACE) {
        return key_backspace_proc();
    }
    if (key == KEY_DC) {
        return key_delete_proc();
    }
    if (key == KEY_LEFT) {
        return key_left_proc();
    }
    if (key == KEY_RIGHT) {
        return key_right_proc();
    }
    if (key == KEY_UP) {
        return;
    }
    if (key == KEY_DOWN) {
        return;
    }

    getsyx(CURS_Y, CURS_X);
    Connect::key_cmd.push(symbol, CURS_X - 1);
    clear_command_line();
    print_command_line();
    move(CURS_Y, Connect::key_cmd.getCurs() + 1);
    refresh();
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
