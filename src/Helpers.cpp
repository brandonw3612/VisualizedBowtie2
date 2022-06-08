//
// Created by Brandon Wong on 2022/6/6.
//

#include <cstdio>
#include <termios.h>
#include <unistd.h>
#include <cstring>

#include "../include/Helpers.h"

int Helpers::getDigits(int num) {
    if (num == 0) return 1;

    int result = 0;
    while (num > 0) {
        result++;
        num /= 10;
    }
    return result;
}

int Helpers::scanKeyboard() {
    int character;
    struct termios orig_term_attr{};
    struct termios new_term_attr{};

    /* set the terminal to raw mode */
    tcgetattr(fileno(stdin), &orig_term_attr);
    memcpy(&new_term_attr, &orig_term_attr, sizeof(struct termios));
    new_term_attr.c_lflag &= ~(ECHO|ICANON);
    new_term_attr.c_cc[VTIME] = 0;
    new_term_attr.c_cc[VMIN] = 1;
    tcsetattr(fileno(stdin), TCSANOW, &new_term_attr);

    /* read a character from the stdin stream without blocking */
    /*   returns EOF (-1) if no character is available */
    character = fgetc(stdin);

    /* restore the original terminal attributes */
    tcsetattr(fileno(stdin), TCSANOW, &orig_term_attr);

    return character;
}