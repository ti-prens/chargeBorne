#include <donnees_borne.h>
#include <memoireborne.h>
#include "boutons.h"
#include <stdio.h>


entrees *io;
int shmid;


boutons_charge()
{
	io=acces_memoire(&shmid);
	if(io==NULL) printf("Erreur memoire partage \n");
	if(io.bouton_charge==1)
	{
		io.bouton_charge=0;
		return 1;	
	}
	else return 0;
}
boutons_stop()
{
	io=acces_memoire(&shmid);
	if(io==NULL) printf("Erreur memoire partage \n");
	if(io.bouton_charge==1)
	{
		io.bouton_stop=0;
		return 1;	
	}
	else return 0;
}
