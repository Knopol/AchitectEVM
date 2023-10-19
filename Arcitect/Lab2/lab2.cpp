#include <stdio.h>

#include "mySimpleComputer.h"
#include "myTerm.h"

int main(){
	int mem_data;
    sc_memoryInit();
    sc_regInit();
    for (int i = 0; i < 100; i++) {
		sc_memorySet(i, i);
	}
    mt_clrscr();
    mt_gotoXY(27, 1);
    printf(" Memory ");
    mt_gotoXY(1, 2);
    for(int i = 0; i < 100; i++){
    	sc_memoryGet(i, &mem_data);
    	mt_gotoXY(i % 10 * 6 + 2, i / 10 + 2);
    	if(mem_data > 0){
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
    mt_gotoXY(67, 1);
    printf(" accunulator ");
    mt_gotoXY(64, 4);
    printf(" instructionCounter ");
    mt_gotoXY(71, 5);
    printf("+0000");
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
    mt_gotoXY(1, 38);
}
