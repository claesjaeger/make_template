#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <stdlib.h>
#include <sys/time.h>
//#include <readline/readline.h>
//#include <readline/history.h>

#include <weathercollect.h>
#include <logWriter.h>
#include <serial.h>
/*
 * Exit status
 * -1:could not open serial port
 * 
 *
 */
 
 
//https://stackoverflow.com/questions/6947413/how-to-open-read-and-write-from-serial-port-in-c

int main()
{
    int fd;
    int wlen;
    int rdlen;
    char buf[300];
    struct timeval now, logCreated;
    int timediff;
    
    FILE * logFile;
    
    //Create logfile
    //printf("before\n");
   logFile = createLogFile();
   gettimeofday(&logCreated, NULL);
 
    fd = open_port(PORTNAME);
    if (fd < 0) {
        printf("Error opening %s: %s.\nProgram will now close.\n", PORTNAME, strerror(errno));
        exit(-1);
    }
    /*baudrate 19200, 8 bits, no parity, 1 stop bit */
    set_interface_attribs(fd, B19200);
    
    while(TRUE) {
		rdlen = readLine(fd,buf);
		writeToLog(logFile, buf);
		gettimeofday(&now, NULL);
		timediff = now.tv_sec - logCreated.tv_sec;
		if(timediff > 3) {
			logFile = createLogFile();
			gettimeofday(&logCreated, NULL);
		}
		
	}
    
    
    
    
    
    
    
    
	
	/*
    // simple noncanonical input
    do {
        unsigned char buf[300];
        int rdlen;

        rdlen = read(fd, buf, sizeof(buf) - 1);
        if (rdlen > 0) {
#ifdef DISPLAY_STRING
            buf[rdlen] = 0;
            printf("Read %d: \"%s\"\n", rdlen, buf);
#else // display hex 
            unsigned char   *p;
            printf("Read %d:", rdlen);
            for (p = buf; rdlen-- > 0; p++)
                printf(" 0x%x", *p);
            printf("\n");
#endif
        } else if (rdlen < 0) {
            printf("Error from read: %d: %s\n", rdlen, strerror(errno));
        }
        // repeat read to get full message 
    } while (1);
    * */
}
