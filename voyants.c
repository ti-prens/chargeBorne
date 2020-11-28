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


void voyants_set_charge(int x)
{
	switch(x)
	{
		case 0 : io->led_charge=OFF; break;
		case 1 : io->led_charge=ROUGE;break;
		case 2 : io->led_charge=VERT;break;
		default : io->led_charge=OFF;
		printf("Erreur voyants_set_charge");
	}
}


void voyants_set_dispo(int x)
{
	switch(x)
	{
		case 0 : io->led_dispo=OFF; break;
		case 1 : io->led_dispo=ROUGE;break;
		case 2 : io->led_dispo=VERT;break;
		default : io->led_dispo=OFF;
		printf("Erreur voyants_set_charge");
	}
}


void voyants_blink_charge()
{
	int i;
	for(i=0;i<8;i++)
	{
		usleep(500000);//suspend le processus en cours
	 	voyants_set_charge(2);
	 	usleep(500000);
	 	voyants_set_charge(0);
	}
}
