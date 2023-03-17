//
// Created by user on 05.03.23.
//

#ifndef MANIPULATOR_GRAPHICS_H
#define MANIPULATOR_GRAPHICS_H


#include <csignal>
#include <sys/ioctl.h>
#include "ncurses.h"
#include "Connect.h"


#define KEY_RETURN 10


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

    move(0, 9);
    printw("id");

    move(0, 17);
    printw("goal");
    move(0, 23);
    printw("angle");

    move(0, 34);
    printw("speed");
    move(0, 41);
    printw("boost");

    move(0, 52);
    printw("torque");

    move(0, 62);
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


#endif //MANIPULATOR_GRAPHICS_H
