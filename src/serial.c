#define MU_10 0x3F215040

// Serial port method
int putc(int data) {
        volatile  unsigned int *mu10 = (volatile  unsigned int *)MU_10;
        *mu10 = (unsigned int)(data & 0xFF);
        return data;
}
