#ifndef MY_READ_KEY_H
#define MY_READ_KEY_H

#define _CRT_SECURE_NO_WARNINGS

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

enum Keys{
	VK_UP,
	VK_DOWN,
	VK_RIGHT,
    VK_LEFT,
    VK_L,
    VK_S,
    VK_0,
    VK_1,
    VK_2,
    VK_3,
    VK_4,
    VK_5,
    VK_6,
    VK_7,
    VK_8,
    VK_9,
    VK_PLUS,
    VK_MINUS,
    VK_F5,
    VK_F6,
    VK_BACKSPACE,
    NOTHING
};

int rk_readkey (enum Keys* key);


int readkey_char(int* data);


int rk_mytermsave (void);

int rk_mytermrestore (void);

int rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint);

#endif // !MY_READ_KEY_H
