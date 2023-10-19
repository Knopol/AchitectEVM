#include "myBigChars.h"

int bc_printA (const char* str){
    //printf("\033[11m");
    //printf("%s", str);
    //printf("\033[10m");
    printf("%s", str);
    return 0;
}

int bc_box(int x1, int y1, int x2, int y2){
    int length = abs(x1 - x2) + 1;
    int height = abs(y1 - y2) + 1;
    for(int i = 1; i < length - 1; i++){
        mt_gotoXY(i + x1, y1);
        bc_printA("\u2500");
        mt_gotoXY((i + x1), y2);
        bc_printA("\u2500");
    }
    
    for(int i = 1; i < height - 1; i++){
        mt_gotoXY(x2, (i + y1));
        bc_printA("\u2502");
        mt_gotoXY((x1), (i + y1));
        bc_printA("\u2502");
    }
	
	mt_gotoXY(x1, y1);
    bc_printA("\u250C");
	mt_gotoXY(x1, y2);
    bc_printA("\u2514");
	mt_gotoXY(x2, y1);
    bc_printA("\u2510");
	mt_gotoXY(x2, y2);
    bc_printA("\u2518");
	
    return 0;
}

int bc_printbigchar (int matrix[2], int x, int y, enum Colors fg_color, enum Colors bg_color){
    mt_setfgcolor(fg_color);
    mt_setbgcolor(bg_color);
    unsigned char* cur = reinterpret_cast<unsigned char*>(matrix);
    for(int i = 0; i < 8; i++){
        mt_gotoXY(x, y + i);
        for(unsigned char pos = 0x80; pos != 0; pos = pos >> 1){
            if(*cur & pos){
                bc_printA("\u2593");
            }
            else{
                printf(" ");
            }
        }
        cur++;
    }


    return 0;
}

int bc_setbigcharpos (int* big, int x, int y, int value){
	if(x < 0 || x > 7 || y < 0 || y > 7 || value < 0 || value > 1 || big == NULL){return -1;}
	unsigned char* cur = reinterpret_cast<unsigned char*>(big) + y;
	if(value){
		*cur |= 0x80 >> x;
	}
	else{
		*cur &= ~(0x80 >> x);
	}
	return 0;
}

int bc_getbigcharpos(int * big, int x, int y, int *value){
	if(x < 0 || x > 7 || y < 0 || y > 7 || big == NULL){return -1;}
	unsigned char* cur = reinterpret_cast<unsigned char*>(big) + y;
	if((*cur & (0x80 >> x)) != 0){
		*value = 1;
	}
	else{
		*value = 0;
	}
	return 0;
}

int bc_bigcharwrite (int fd, int* big, int count){
	if(fd < 0 || count <= 0 || big == NULL){return -1;}
	FILE *f;
	f = fopen("bigChar.dat", "r+b");
	if(f == NULL){ f = fopen("bigChar.dat", "w+b");}
	if(f == NULL){ return -1;}
	fseek(f, 0, SEEK_END);
	int max = ftell(f);
	max /= 8;
	if(fd <= max){
		fseek(f, fd * 8, SEEK_SET);
	}
	else{
		int val[2] = {0, 0};
		fseek(f, max * 8, SEEK_SET);
		for(int i = max; i < fd; i++){
			fwrite(val, sizeof(int) * 2, 1, f);
		}
	}
	fwrite(big, sizeof(int) * 2, count, f);	
	fclose(f); 
	return 0;
}

int bc_bigcharread (int fd, int* big, int need_count, int* count){
	if(fd < 0 || need_count <= 0 || big == NULL){return -1;}
	FILE *f;
	f = fopen("bigChar.dat", "rb");
	if(f == NULL){ return -1; }
	fseek(f, 0, SEEK_END);
	if(ftell(f) < fd * 8){ return -1;}
	fseek(f, fd * 8, SEEK_SET);
	*count = fread(big, sizeof(int) * 2, need_count, f);
	fclose(f); 
	return 0;
}
