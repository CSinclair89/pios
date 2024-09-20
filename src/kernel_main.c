
char glbl[128];

void kernel_main() {
    
  	extern char __bss_start, __bss_end;
	char *bssstart, *bssend;  
	
	bssstart = &__bss_start;
	bssend = &__bss_end;
	char *i = bssstart;

	for (; i < bssend; i++) { 
		*i = 1; 
	}

	while(1){
    }
}
