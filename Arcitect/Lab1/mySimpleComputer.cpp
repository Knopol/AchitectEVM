#include "mySimpleComputer.h"

const int size = 100;
int data[size];

int flag;

int sc_memoryInit() {
    for (int i = 0; i < size; i++) {
        data[i] = 0;
    }
    return 1;
}

int sc_memorySet(int address, int value) {
    if (address >= size || address < 0) { 
        flag |= OUT_OF_RANGE;
        return 0;
    }
    data[address] = value;
    return 1;
}

int sc_memoryGet(int address, int* value) {
    if (address >= size || address < 0) {
        flag |= OUT_OF_RANGE;
        return 0;
    }
    *value = data[address];
    return 1;
}

int sc_memorySave(const char* filename) {
    FILE* f;
    f = fopen(filename, "wb");
    
    if (f == NULL) {
        flag |= FILE_NOT_AVAELABLE;
        return 0;
    }
    int count = fwrite(data, sizeof(int), size, f);
    fclose(f);
    if (count != size) {
        flag |= FILE_WRITE_ERROR;
        return 0;
    }
    return 1;
}

int sc_memoryLoad(const char* filename) {
    FILE* f;
    f = fopen(filename, "rb");

    if (f == NULL) {
        flag |= FILE_NOT_AVAELABLE;
        return 0;
    }
    int count = fread(data, sizeof(int), size + 1, f);
    fclose(f);
    if (count != size) {
        flag |= FILE_READ_ERROR;
        return 0;
    }
    return 1;
}

int sc_regInit(void) {
    flag = 0;
    return 1;
}

int sc_regSet(int reg, int value) {
    if (value != 0 || value != 1) {
        flag |= WRONG_VALUE;
        return 0;
    }
    switch (reg){
    case OUT_OF_RANGE:
        if (value) {
            flag |= OUT_OF_RANGE;
        }
        else {
            flag &= ~OUT_OF_RANGE;
        }
        break;
    case WRONG_COMAND:
        if (value) {
            flag |= WRONG_COMAND;
        }
        else {
            flag &= ~WRONG_COMAND;
        }
        break;
    case FILE_NOT_AVAELABLE:
        if (value) {
            flag |= FILE_NOT_AVAELABLE;
        }
        else {
            flag &= ~FILE_NOT_AVAELABLE;
        }
        break;
    case FILE_WRITE_ERROR:
        if (value) {
            flag |= FILE_WRITE_ERROR;
        }
        else {
            flag &= ~FILE_WRITE_ERROR;
        }
        break;
    case FILE_READ_ERROR:
        if (value) {
            flag |= FILE_READ_ERROR;
        }
        else {
            flag &= ~FILE_READ_ERROR;
        }
        break;
    case WRONG_VALUE:
        if (value) {
            flag |= WRONG_VALUE;
        }
        else {
            flag &= ~WRONG_VALUE;
        }
        break;
	case IGNORE_TIMER:
        if (value) {
            flag |= IGNORE_TIMER;
        }
        else {
            flag &= ~IGNORE_TIMER;
        }
        break;
    default:
        flag |= WRONG_REGISTER;
        return 0;
        break;
    }
    return 1;
}

int sc_regGet(int reg, int* value) {
    if (reg != OUT_OF_RANGE && reg != WRONG_COMAND && reg != FILE_NOT_AVAELABLE && reg != FILE_WRITE_ERROR &&
        reg != FILE_READ_ERROR && reg != WRONG_REGISTER && reg != WRONG_VALUE && reg != IGNORE_TIMER) {
        return -1;
    }
    *value = (flag & reg) > 0;
    return 0;
}

int sc_commandEncode(int command, int operand, int* value) {
    *value = (operand & 0x7F) + (command & 0x7F << 7);
    return 1;
}

