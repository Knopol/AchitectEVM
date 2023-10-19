#include <stdio.h>
#include <wchar.h>

#include "mySimpleComputer.h"
#include "myTerm.h"
#include "myBigChars.h"
#include <locale.h>

int numbers[10][2];
int minus[2];
int plus[2];
int instructionCounter = 15;

void scr_print(){
	int mem_data;
    mt_clrscr();
    mt_gotoXY(1, 2);
    for(int i = 0; i < 100; i++){
    	sc_memoryGet(i, &mem_data);
    	mt_gotoXY(i % 10 * 6 + 2, i / 10 + 2);
    	if(mem_data >= 0){
    		if(mem_data < 10000){
    			printf("+%04d", mem_data);
    		}
    		else{
    			printf("+9999");
    		}
    	}
    	else{
    		if(mem_data > -10000){
    			printf("-%04d", -mem_data);
    		}
    		else{
    			printf("-9999");
    		}
    	}
    	
    }
    bc_box(1, 1, 61, 12);
    bc_box(1, 13, 42, 22);
    bc_box(43, 13, 85, 22);
    
    bc_box(62, 1, 85, 3);
    bc_box(62, 4, 85, 6);
    bc_box(62, 7, 85, 9);
    bc_box(62, 10, 85, 12);
    
    mt_gotoXY(27, 1);
    printf(" Memory ");
    mt_gotoXY(67, 1);
    printf(" accunulator ");
    mt_gotoXY(64, 4);
    printf(" instructionCounter ");
    mt_gotoXY(71, 5);
    printf("+%04d", instructionCounter);
    mt_gotoXY(68, 7);
    printf(" Operation ");
    mt_gotoXY(70, 10);
    printf(" Flags ");
    mt_gotoXY(45, 13);
    printf(" Keys: ");
    mt_gotoXY(44, 14);
    printf("l - load");
    mt_gotoXY(44, 15);
    printf("s - save");
    mt_gotoXY(44, 16);
    printf("r - run");
    mt_gotoXY(44, 17);
    printf("t - step");
    mt_gotoXY(44, 18);
    printf("i - reset");
    mt_gotoXY(44, 19);
    printf("F5 - accumulator");
    mt_gotoXY(44, 20);
    printf("F6 - intructionCounter");
    
    sc_memoryGet(instructionCounter, &mem_data);
    
    if(mem_data >= 0){
    	if(mem_data > 9999){
    		mem_data = 9999;
    	}
    	bc_printbigchar(plus, 2, 14, White, Black);
    }
    else{
    	if(mem_data < -9999){
    		mem_data = -9999;
    	}
    	bc_printbigchar(minus, 2, 14, White, Black);
    }
    
    for(int i = 3; i >= 0; i--){
    	bc_printbigchar(numbers[mem_data % 10], 10 + i * 8, 14, White, Black);
    	mem_data /= 10;
    }
    
}

int main(){
    int count;
    
    bc_bigcharread (0, numbers[0], 10, &count);
    if(count != 10){
    	mt_gotoXY(1, 37);
    	printf("Read error\n");
    	return -1;
    }
    bc_bigcharread (10, minus, 1, &count);
    if(count != 1){
    	mt_gotoXY(1, 37);
    	printf("Read error\n");
    	return -1;
    }
    bc_bigcharread (11, plus, 1, &count);
    if(count != 1){
    	mt_gotoXY(1, 37);
    	printf("Read error\n");
    	return -1;
    }
    
    sc_memoryInit();
    sc_regInit();
    
    for (int i = 0; i < 100; i++) {
		sc_memorySet(i, i);
	}
    
    scr_print();
    
    mt_gotoXY(1, 38);
}
