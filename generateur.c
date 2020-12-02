#include <unistd.h>
#include <donnees_borne.h>
#include <memoire_borne.h>
#include <lcarte.h>
#include <stdio.h>


#include "generateur.h"


entrees *io;
int shmid;

void generateur_initialiser()
{
	io=acces_memoire(&shmid);
	/* associe la zone de memoire partagee au pointeur */
	if (io==NULL) printf("Erreur pas de mem sh\n");	
	generateur_mode(OFF);
	generateur_contacteur(OUVERT);
}

void generateur_mode(pwm x)
{
	switch(x)
	{
		case STOP 	: io->gene_pwm  =OFF; 	break;
		case DC		: io->gene_pwm  =DC; 	break;
		case AC_1K	: io->gene_pwm  =AC_1K;	break;
		case AC_CL	: io->gene_pwm  =AC_CL;	break;
		default 	: io->gene_pwm  =OFF;
		printf("Erreur generateur_mode");
	}
}

void generateur_contacteur(C_AC x) //OUVERT, FERME
{
	switch(x)
	{
		case OUVERT	: io->contacteur_AC = 0;	break;
		case FERME	: io->contacteur_AC = 1;	break;
		default 	: io->contacteur_AC = 0;
		printf("Erreur generateur_contacteur");
	}
}

void generateur_charger_batterie()
{
	printf("debut 2ieme partie");
}


