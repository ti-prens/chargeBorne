#include <unistd.h>
#include <donnees_borne.h>
#include <memoire_borne.h>

#include "timer.h"


entrees *io;
int shmid;
int depart_timer;

void timer_initialiser()
{
	io=acces_memoire(&shmid);
	/*associe la zone de memoire partagee au pointeur*/
	if(io==NULL) printf("Erreur pas de mem sh\n");
	depart_timer=io->timer_sec;
}


int valeur_timer ()
{
	int timer=0;
	timer=(io->timer_sec)-depart_timer;
	return timer;
}

void timer_raz()
{	
	depart_timer=0;
}
