#include "rprintf.h"

#define MU_10 0x3F215040

char glbl[128];

unsigned long getTimerCount() {
	unsigned long *timerCountReg = (unsigned long *)0x3f003004;
	return *timerCountReg;
}

void waitFor1ms() {
	unsigned long tic = getTimerCount();
	unsigned long toc = tic + 1000000;

	while (getTimerCount() < toc) {}
}

void putc(int data) {
	volatile  unsigned int *mu10 = (volatile  unsigned int *)MU_10;
	*mu10 = (unsigned int)(data & 0xFF);
}

void kernel_main() {
    
  	extern char __bss_start, __bss_end;
	char *bssStart, *bssEnd;  
	
	bssStart = &__bss_start;
	bssEnd = &__bss_end;
	char *i = bssStart;
	
	waitFor1ms();

	for (; i < bssEnd; i++) {
	       	*i = 0;
	}
	
	esp_printf(putc, "Hello! Number: %d\n", 42);

	while(1){
    }
}
