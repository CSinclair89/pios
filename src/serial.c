#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

void putc(int data) {
	int serialPort = open("/dev/ttyS0", O_WRONLY);
	if (serialPort < 0) {
		perror("Failed to open serial port!");
		return;
	}

	write(serialPort, &data, 1);
	close(serialPort);
}











