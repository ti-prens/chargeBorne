#include <unistd.h>
#include "boutons.h"

entrees *io;
int shmid;

void boutons_initialiser()
{
	io=acces_memoire(&shmid);
	/* associe la zone de memoire partagee au pointeur */
	if (io==NULL) printf("Erreur pas de mem sh\n");	
}


int boutons_charge_status()
{	
	int bouton;
 	if(io->bouton_charge==1)
   		bouton=1;
 	else
   		bouton=0;

	return bouton;
}

int boutons_stop_status()
{	
	int bouton;
	if(io->bouton_stop==1)
		bouton=1;
	else
  		bouton=0;
  		
  	return bouton; 
}
