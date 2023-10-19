#include "myReadkey.h"

termios tsaved;

int rk_readkey (enum Keys* key){
    char arr[80];
    int cnt = read(0, arr, 80);
    *key = NOTHING;
    if(arr[0] == 27){
    	if(arr[1] != 91){
    		return 0;
    	}
    	switch(arr[2]){
    		case 49:
    			if(arr[3] == 53){
    				*key = VK_F5;
    			}
    			else if(arr[3] == 55){
    				*key = VK_F6;
    			}
    			break;
    		case 65:
    			*key = VK_UP;
    			break;
    		case 66:
    			*key = VK_DOWN;
    			break;
    		case 67:
    			*key = VK_RIGHT;
    			break;
    		case 68:
    			*key = VK_LEFT;
    			break;
    	}
    }
    else{
    	switch (arr[0]){
    		case 108:
    			*key = VK_L;
    			break;
    		case 115: 
    			*key = VK_S;
    			break;
    		case 43: 
    			*key = VK_PLUS;
    			break;
    		case 45: 
    			*key = VK_MINUS;
    			break;
    		case 48: 
    			*key = VK_0;
    			break;
    		case 49: 
    			*key = VK_1;
    			break;
    		case 50: 
    			*key = VK_2;
    			break;
    		case 51: 
    			*key = VK_3;
    			break;
    		case 52: 
    			*key = VK_4;
    			break;
    		case 53: 
    			*key = VK_5;
    			break;
    		case 54: 
    			*key = VK_6;
    			break;
    		case 55: 
    			*key = VK_7;
    			break;
    		case 56: 
    			*key = VK_8;
    			break;
    		case 57: 
    			*key = VK_9;
    			break;
    		case 127: 
    			*key = VK_BACKSPACE;
    			break;
    	}
    }
    return 0;
}

int readkey_char(int* data){
	char x[10];
	int cnt = read(0, &x, 10);
	for(int i = 0; i < cnt; i++){
		data[i] = x[i];
	}
	if(cnt > 0){
		for(int i = cnt; i < 10; i++){
			data[i] = 0;
		}
		
	}
	return cnt;
}

int rk_mytermsave (void){
	if(tcgetattr(0, &tsaved) == 0){
		return 1;
	}
	printf ("Terminal open error\n");
	return 0;
}

int rk_mytermrestore (void){
	tcsetattr (0, 1, &tsaved);
	return 1;
}

int rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint){
	if(vtime < 0 || vmin < 0){
		return -1;
	}
	termios term;
	tcgetattr (0, &term);
	
	term.c_cc[VTIME] = vtime;
	term.c_cc[VMIN] = vmin;
	
	if(regime){
		term.c_lflag |= ICANON;
	}
	else{
		term.c_lflag &= ~ICANON;
	}
	
	if(echo){
		term.c_lflag |= ECHO;
	}
	else{
		term.c_lflag &= ~ECHO;
	}
	
	if(sigint){
		term.c_lflag |= ISIG;
	}
	else{
		term.c_lflag &= ~ISIG;
	}
	tcsetattr (0, TCSAFLUSH, &term);
	return 1;
}
