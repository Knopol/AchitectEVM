#include <stdio.h>

#include "mySimpleComputer.h"


int main(){
	int res;
	sc_memoryInit();
	sc_regInit();
	for (int i = 0; i < 100; i++) {
		sc_memorySet(i, i);
	}
	for(int i = 0; i < 100; i++){
		
		sc_memoryGet(i, &res);
		printf("%d\n", res);
	}
	sc_memorySave("file");
	sc_memoryLoad("file");
}
