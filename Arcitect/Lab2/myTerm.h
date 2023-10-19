#ifndef MY_TERM_H
#define MY_TERM_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>

enum Colors{
    Black,
    Dark_Gray,
    Blue,
    Light_Blue,
    Green,
    Light_Green,
    Cyan,
    Light_Cyan,
    Red,
    Light_Red,
    Purple,
    Light_Purple,
    Brown,
    Yellow,
    Light_Gray,
    White,
    Underscore,
    Blink,
    Inverse,
    Concealed
};

int mt_clrscr (void);

int mt_gotoXY(int x, int y);

int mt_getscreensize (int * rows, int * cols);

int mt_setfgcolor (enum Colors);

int mt_setbgcolor (enum Colors);

#endif // !MY_TERM_H
