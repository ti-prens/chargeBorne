#include <unistd.h>
#include "voyants.h"




entrees *io;
int shmid;

//initialistation des voyants 
void voyants_initialiser()
{
	io=acces_memoire(&shmid);
	/*associe la zone de memoire partagee au pointeur*/
	if(io==NULL) printf("Erreur pas de mem sh\n");
}


void voyants_set_charge(led  x)
{
	switch(x)
	{
		case OFF : io->led_charge=OFF; break;
		case ROUGE : io->led_charge=ROUGE;break;
		case VERT: io->led_charge=VERT;break;
		default : io->led_charge=OFF;
		printf("Erreur voyants_set_charge");
	}
}


void voyants_set_dispo(led  x)
{
	switch(x)
	{
		case OFF : io->led_dispo=OFF; break;
		case ROUGE : io->led_dispo=ROUGE;break;
		case VERT : io->led_dispo=VERT;break;
		default : io->led_dispo=OFF;
		printf("Erreur voyants_set_charge");
	}
}


void voyants_blink_charge(led x)
{
	int i;
	for(i=0;i<8;i++)
	{
		usleep(500000);//suspend le processus en cours
	 	voyants_set_charge(x);
	 	usleep(500000);
	 	voyants_set_charge(OFF);
	}
}

void voyants_blink_default(led x)
{
	int i;
	for(i=0;i<8;i++)
	{
		usleep(500000);//suspend le processus en cours
	 	voyants_set_default(x);
	 	usleep(500000);
	 	voyants_set_default(OFF);
	}
}

