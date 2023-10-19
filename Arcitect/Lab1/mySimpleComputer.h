#ifndef MY_SIMPLE_COMPUTER_H
#define MY_SIMPLE_COMPUTER_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define OUT_OF_RANGE 0x0001
#define WRONG_COMAND 0x0002
#define FILE_NOT_AVAELABLE 0x0004
#define FILE_WRITE_ERROR 0x0008
#define FILE_READ_ERROR 0x0010
#define WRONG_REGISTER 0x0020
#define WRONG_VALUE 0x0040
#define IGNORE_TIMER 0x0080

int sc_memoryInit();

int sc_memorySet(int address, int value);

int sc_memoryGet(int address, int* value);

int sc_memorySave(const char* filename);

int sc_memoryLoad(const char* filename);

int sc_regInit(void);

int sc_regSet(int register, int value);

int sc_regGet(int register, int* value);

int sc_commandEncode(int command, int operand, int* value);

int sc_commandDecode(int value, int* command, int* operand);

#endif // !MY_SIMPLE_COMPUTER_H

