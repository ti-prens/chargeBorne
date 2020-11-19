#include <donnees_borne.h>
#include <memoire_borne.h>
#include <stdio.h>

#include "boutons.h"


entrees *io;
int memeory_id;


int boutons_charge()
{
	io=acces_memoire(&memeory_id);
	if(io==NULL) printf("Erreur memoire partage \n");
	if(io->bouton_charge==1)
	{
		io->bouton_charge=0;
		return 1;	
	}
	else return 0;
}
int boutons_stop()
{
	io=acces_memoire(&memeory_id);//(&shmid);
	if(io==NULL) printf("Erreur memoire partage \n");
	if(io->bouton_charge==1)
	{
		io->bouton_stop=0;
		return 1;	
	}
	else return 0;
}
