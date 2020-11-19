#include <unistd.h>
#include "boutons.h"

entrees *io;
int shmid;

void prise_initialiser()
{
	io=acces_memoire(&shmid);
	/* associe la zone de memoire partagee au pointeur */
	if (io==NULL) printf("Erreur pas de mem sh\n");	
}

void verouiller_trappe()
{
 io->led_trappe=OFF;
}

void deverouiller()
{
 io->led_trappe=VERT;
}

void set_prise()
{
 io->led_trappe=VERT;
}
