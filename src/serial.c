#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

/*
 * 'open_port()' - Open serial port 1.
 *
 * Returns the file descriptor on success or -1 on error.
 */

int open_port(char *name) {
  int fd; /* File descriptor for the port */

  fd = open(name, O_RDWR | O_NOCTTY | O_NDELAY | O_SYNC);
  if (fd == -1) {
   //Could not open the port.
    printf("open_port: Error opening %s: %s\n", name, strerror(errno));
        return -1;
    //perror("open_port: Unable to open port ");
  }
  else {
    fcntl(fd, F_SETFL, 0);
    printf("Serial Port Open\n");
	}

  return (fd);
}

int close_port(int fd) {
	int retVal = close(fd);
	if(retVal==0) printf("Port closed succesfully\n");
	else printf("Error while closing port\n");
	
	return retVal;
	 
}

int set_interface_attribs(int fd, int speed) {
    struct termios tty;

    if (tcgetattr(fd, &tty) < 0) {
        printf("Error from tcgetattr: %s\n", strerror(errno));
        return -1;
    }

    cfsetospeed(&tty, (speed_t)speed);
    cfsetispeed(&tty, (speed_t)speed);

    tty.c_cflag |= (CLOCAL | CREAD);    /* ignore modem controls */
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;         /* 8-bit characters */
    tty.c_cflag &= ~PARENB;     /* no parity bit */
    tty.c_cflag &= ~CSTOPB;     /* only need 1 stop bit */
    tty.c_cflag &= ~CRTSCTS;    /* no hardware flowcontrol */

    /* setup for non-canonical mode */
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    tty.c_oflag &= ~OPOST;

    /* fetch bytes as they become available */
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 1;

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        printf("Error from tcsetattr: %s\n", strerror(errno));
        return -1;
    }
    return 0;
}

void set_mincount(int fd, int mcount)
{
    struct termios tty;

    if (tcgetattr(fd, &tty) < 0) {
        printf("Error tcgetattr: %s\n", strerror(errno));
        return;
    }

    tty.c_cc[VMIN] = mcount ? 1 : 0;
    tty.c_cc[VTIME] = 5;        /* half second timer */

    if (tcsetattr(fd, TCSANOW, &tty) < 0)
        printf("Error tcsetattr: %s\n", strerror(errno));
}

int readLine(int fd, char *buf) {
	char temp;
	char *ptemp;
	ptemp = &temp;
	 
	int counter = 0;
	//printf("in\n");
	while(temp != '\n'){
		read(fd,ptemp,1);
		//printf("read char: %s\n",ptemp);
		*buf = *ptemp;
		buf++;
		counter++;
	}
	buf = buf -2;
	*buf = '\0';
	return counter;
}
