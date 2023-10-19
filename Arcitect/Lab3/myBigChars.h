#ifndef MY_BIG_CHARS_H
#define MY_BIG_CHARS_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <math.h>

#include "myTerm.h"

int bc_printA (const char* str);

int bc_box(int x1, int y1, int x2, int y2);

int bc_printbigchar(int matrix[2], int x, int y, enum Colors fg_color, enum Colors bg_color);

int bc_setbigcharpos (int* big, int x, int y, int value);

int bc_getbigcharpos(int* big, int x, int y, int *value);

int bc_bigcharwrite (int fd, int* big, int count);

int bc_bigcharread (int fd, int* big, int need_count, int* count);

#endif // !MY_BIG_CHARS_H
