#include <stdio.h>

#include "log.h"


int log_number;

void log_init()
{	
	log_number=0;
}

void log_msg(char msg[])
{
	//extern int log_number;
	printf("log # %d   %s \n", log_number, msg);
	log_number++;
}
