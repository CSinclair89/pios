#define MU_10_VIRTUAL 0xC0000040
#define MU_10_PHYSICAL 0x3F215040

// Serial port method
int putc(int data) {
        volatile  unsigned int *mu10 = (volatile  unsigned int *)MU_10_PHYSICAL;
        *mu10 = (unsigned int)(data & 0xFF);
        return data;
}

int putc_phys(int data) {
	volatile unsigned int *mu10 = (volatile unsigned int *)MU_10_PHYSICAL;
	*mu10 = (unsigned int)(data & 0xFF);
	return data;
}


