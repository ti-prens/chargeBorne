#include <unistd.h>
#include <donnees_borne.h>
#include <memoire_borne.h>

#include "timer.h"


entrees *io;
int shmid;
int TIMER;

void timer_initialiser()
{
	io=acces_memoire(&shmid);
	/*associe la zone de memoire partagee au pointeur*/
	if(io==NULL) printf("Erreur pas de mem sh\n");
}


int timer_get_value()
{
	int diff;
	diff = (io->timer_sec)-TIMER;
	return diff;
}

void timer_reset()
{	
	TIMER=io->timer_sec;
}

void timer_pause(int x)
{
	int pause = io->timer_sec;
	
	while(io->timer_sec < pause+x)
	{
		usleep(5000); //do nothing for at least 5ms
		//j'imagiine que usleep ne monopolise pas l'os et que d'autre threads peuvent etre traiter 
	}
}

