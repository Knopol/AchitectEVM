#include <stdio.h>
#include <wchar.h>
#include <unistd.h>

#include "mySimpleComputer.h"
#include "myTerm.h"
#include "myBigChars.h"
#include "myReadkey.h"
#include <locale.h>

int numbers[10][2];
int minus[2];
int plus[2];
int instructionCounter = 0;
int status = 0;
int accumulator = 0;

void scr_print(){
	int mem_data;
    
    mt_setfgcolor(White);
    mt_setbgcolor(Black);
    mt_clrscr();
    mt_gotoXY(1, 2);
    for(int i = 0; i < 100; i++){
    	sc_memoryGet(i, &mem_data);
    	mt_gotoXY(i % 10 * 6 + 2, i / 10 + 2);
    	if(i == instructionCounter && status == 0){
    		mt_setfgcolor(Black);
    		mt_setbgcolor(White);
    	}
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
    	if(i == instructionCounter && status == 0){
    		mt_setfgcolor(White);
    		mt_setbgcolor(Black);
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
    printf(" accumulator ");
    mt_gotoXY(71, 2);
    if(status == 1){
		mt_setfgcolor(Black);
		mt_setbgcolor(White);
    }
    if(accumulator >= 0){
    	printf("+%04d", accumulator);
    }
    else{
    	printf("-%04d", -accumulator);
    }
    if(status == 1){
		mt_setfgcolor(White);
		mt_setbgcolor(Black);
    }
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
    
    if(status == 0){
    	sc_memoryGet(instructionCounter, &mem_data);
    }
    else{
    	mem_data = accumulator;
    }
    
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
    	mem_data = -mem_data;
    }
    
    for(int i = 3; i >= 0; i--){
    	bc_printbigchar(numbers[mem_data % 10], 10 + i * 8, 14, White, Black);
    	mem_data /= 10;
    }
    
}

int main(){ //142 38
	
	/*
	numbers[0][0] = 1111638588;
    numbers[0][1] = 1010975298;
    numbers[1][0] = 136845320;
    numbers[1][1] = 2114455560;
    numbers[2][0] = 71451196;
    numbers[2][1] = 2116030472;
    numbers[3][0] = 67256892;
    numbers[3][1] = 1010958852;
    numbers[4][0] = 2118271554;
    numbers[4][1] = 33686018;
    numbers[5][0] = 2084585598;
    numbers[5][1] = 1010958850;
    numbers[6][0] = 2084586044;
	numbers[6][1] = 1010975298;
	numbers[7][0] = 67371646;
	numbers[7][1] = 269486088;
	numbers[8][0] = 1010975292;
	numbers[8][1] = 1010975298;
	numbers[9][0] = 1111638588;
    numbers[9][1] = 134480446;
    
    minus[0] = 2113929216;
    minus[1] = 126;
    plus[0] = 2115508224;
    plus[1] = 1579134;
    
    bc_bigcharwrite (0, numbers[0], 10);
    bc_bigcharwrite (10, minus, 1);
    bc_bigcharwrite (11, plus, 1);
    */
    
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
    
    mt_gotoXY(1, 37);
    
    //sleep(1);
    rk_mytermregime(0, 0, 0, 0, 1);
    int last_num = 0;
    int arr[10] = {};
    enum Keys last_key = NOTHING;
    enum Keys key = NOTHING;
    
    while(1){
    	/*
    	int cnt = readkey_char(arr);
    	mt_gotoXY(1, 37);
    	for(int i = 0; i < 10; i++){
    		printf("%3d ", arr[i]);
    	}
    	*/
    	
    	rk_readkey(&key);
    	if(key!= last_key){
    		last_key = key;
    		int num;
    		switch (key){
    			case VK_UP:
    				if(instructionCounter >= 10){
    					instructionCounter -= 10;
    				}
    				break;
				case VK_DOWN:
					if(instructionCounter < 90){
    					instructionCounter += 10;
    				}
    				break;
				case VK_RIGHT:
					if(instructionCounter % 10 < 9){
    					instructionCounter++;
    				}
    				break;
    			case VK_LEFT:
    				if(instructionCounter % 10 > 0){
    					instructionCounter--;
    				}
    				break;
    			case VK_BACKSPACE:
    				if(status == 0){
    					sc_memorySet(instructionCounter, 0);	
    				}
    				else{
    					accumulator = 0;
    				}
    				break;
    			case VK_0: case VK_1: case VK_2: case VK_3: case VK_4: 
    			case VK_5: case VK_6: case VK_7: case VK_8: case VK_9: 
    				if(status == 0){
						sc_memoryGet(instructionCounter, &num);
						if(num >= 9999 || num <= -9999){
							break;
						}
						num = num * 10 + 0 + key - VK_0;
						sc_memorySet(instructionCounter, num);	
    				}
    				else{
    					if(accumulator >= 9999 || accumulator <= -9999){
							break;
						}
						accumulator = accumulator * 10 + 0 + key - VK_0;
    				}
    				break;
    			case VK_PLUS:
    				if(status == 0){
						sc_memoryGet(instructionCounter, &num);
						if(num < 0){
							num = -num;
						}
						sc_memorySet(instructionCounter, num);	
    				}
    				else{
    					if(accumulator < 0){
							accumulator = -accumulator;
						}
    				}
    				break;
    			case VK_MINUS:
    				if(status == 0){
						sc_memoryGet(instructionCounter, &num);
						if(num > 0){
							num = -num;
						}
						sc_memorySet(instructionCounter, num);	
    				}
    				else{
    					if(accumulator > 0){
							accumulator = -accumulator;
						}
    				}
    				break;
    			case VK_F5:
    				status = 1;
    				break;
    			case VK_F6:
    				status = 0;
    				break;
    		}
    		scr_print();
    	}
    	
    	mt_gotoXY(1, 38);
    	printf(" ");
    }
    
    
    //readkey_char();
}

