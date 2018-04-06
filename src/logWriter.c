#include <time.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#include <logWriter.h>

char date[30];

void setTime(){
	time_t now;
	time(&now);
	struct tm tm = *localtime(&now);
	
	memset(date,0,30);
	//strcpy(date,ctime(&now));
	
	sprintf(date,"%04d%02d%02d_%02d:%02d:%02d",tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour, tm.tm_min, tm.tm_sec);
	
	//date[strlen(date)-1]='\0';
	//printf("%s \n", date);
}

FILE* createLogFile(){
	char title[]="WeatherDataLog";
	char filetype[]=".log";
	char fileName[128];
	memset(fileName,0,128);

	setTime();
	strcat(fileName,title);
	strcat(fileName,date);
	strcat(fileName,filetype);

	FILE *fp;

	fp=fopen(fileName,"w");
	//fprintf(fp,"Date,Vad,Vdd,Temp\n");

	return fp;
}

int writeToLog(FILE * logfile, char *buf){
	struct timeval now;
	long milliseconds;
	int mil;
	char str[4];
	int result=0;
	setTime();
	gettimeofday(&now, NULL);
	
	milliseconds = now.tv_usec/1000;
	mil = (int)milliseconds%1000;
	sprintf(str, "%d", mil);
	strcat(date,":");
	strcat(date,str);
	//printf("%ld \n", mil);
	
    result = fprintf(logfile,"%s %s\n",date,buf);

    return result;
}

