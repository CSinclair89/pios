#include "timer.h"

#define COUNT_REG 0x3f003004

// System timer count registration
unsigned long getTimerCount() {
        unsigned long *timerCountReg = (unsigned long *)COUNT_REG;
        return *timerCountReg;
}

// Method to wait for a few seconds
void waitFor1ms() {
        unsigned long tic = getTimerCount();
        unsigned long toc = tic + 1000000;

        while (getTimerCount() < toc) {}
}
