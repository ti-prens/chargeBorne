#include <unistd.h>
#include <donnees_borne.h>
#include <memoire_borne.h>
#include <lcarte.h>
#include <stdio.h>


#include "generateur.h"

#include "log.h"


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



int generateur_dispo(void)
{	//si le generateur n'est pas occuper il retoune 1 et 0 sinon
	int dispo = 0;
	return dispo = (io->gene_u == 0)? 1 : 0 ;
}
