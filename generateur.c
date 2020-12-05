#include <unistd.h>
#include <donnees_borne.h>
#include <memoire_borne.h>
#include <lcarte.h>
#include <stdio.h>


#include "generateur.h"
#include "prise.h"
#include "voyants.h"
#include "timer.h"

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

void generateur_charger_batterie()
{
	printf("\ndebut 2ieme couche\nCharger batterie\n\n");
	
	timer_pause(2);
	
	prise_verrouiller();
	voyants_set_prise(VERT);
	timer_pause(2);
	//generer une tension +9V/-12V
	generateur_mode(AC_1K);
	//vehicule ferme contacteur S2
	//tension passe à 6V
	timer_pause(2);
	generateur_contacteur(FERME); //AC
	//generer une tension +6V/-12V
	//vehicule ouvre S2 (quand batterie charge)
	//vehicule fait remonter tension à +9V/-12V
	timer_pause(2);
	generateur_contacteur(OUVERT); //AC
	//generer une tension +9V
	timer_pause(2);
	voyants_set_charge(VERT);		

}


