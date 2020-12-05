#include <unistd.h>
#include <donnees_borne.h>
#include <memoire_borne.h>
#include <lcarte.h>
#include <stdio.h>

#include "prise.h"

#include "voyants.h"

entrees *io;
int shmid;

void prise_verrouiller()
{
 	io->led_trappe=OFF;
}

void prise_deverrouiller()
{
 	io->led_trappe=VERT;
}


void prise_initialiser()
{
	io=acces_memoire(&shmid);
	/* associe la zone de memoire partagee au pointeur */
	if (io==NULL) printf("Erreur pas de mem sh\n");	
	prise_verrouiller();
}


