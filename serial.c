#include "serial.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <termios.h>

int serial_open(char *port, int baud)
{
	int speed;
	int fd;
	struct termios tty;
	if((fd = open(port, O_RDWR | O_NOCTTY | O_SYNC)) < 0)
	{
		return -1;
	}

	switch(baud)
	{
		case 50:
			speed = B50;

		case 75:
			speed = B75;
			break;

		case 110:
			speed = B110;
			break;

		case 134:
			speed = B134;
			break;

		case 150:
			speed = B150;
			break;

		case 200:
			speed = B200;
			break;

		case 300:
			speed = B300;
			break;

		case 600:
			speed = B600;
			break;

		case 1200:
			speed = B1200;
			break;

		case 1800:
			speed = B1800;
			break;

		case 2400:
			speed = B2400;
			break;

		case 4800:
			speed = B4800;
			break;

		case 9600:
			speed = B9600;
			break;

		case 19200:
			speed = B19200;
			break;

		case 38400:
			speed = B38400;
			break;

		case 57600:
			speed = B57600;
			break;

		case 115200:
			speed = B115200;
			break;

		case 230400:
			speed = B230400;
			break;

		default:
			return -1;
	}

	if(tcgetattr(fd, &tty) < 0)
	{
		return -1;
	}

	cfsetospeed(&tty, (speed_t)speed);
	cfsetispeed(&tty, (speed_t)speed);
	tty.c_cflag |= (CLOCAL | CREAD);
	tty.c_cflag &= ~CSIZE;
	tty.c_cflag |= CS8;
	tty.c_cflag &= ~PARENB;
	tty.c_cflag |= CSTOPB;
	tty.c_cflag &= ~CRTSCTS;
	tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
	tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	tty.c_oflag &= ~OPOST;
	tty.c_cc[VMIN] = 1;
	tty.c_cc[VTIME] = 1;
	if(tcsetattr(fd, TCSANOW, &tty))
	{
		return -1;
	}

	return fd;
}
