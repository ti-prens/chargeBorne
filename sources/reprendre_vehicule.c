#include <unistd.h>
#include <lcarte.h>
#include <stdio.h>

#include <donnees_borne.h>
#include <memoire_borne.h>

#include "reprendre_vehicule.h"

#include "borne.h"

#include "log.h"


entrees *io;
int shmid;


int reprendre_vehicule()
{
	extern int REPRIS;
	extern int STOP_B;
	do 
	{
	
	log_msg("le proprietaire de la voiture est de retour");
	log_msg("blink charge en vert");
	voyants_blink_charge(VERT);
	log_msg("prise deverouiller");
	prise_deverrouiller();
	timer_pause(2);
	log_msg("attendre retrait de la prise par l'usager");
	while(io->gene_u == 9)
	{
	 	//do nothing
	 	// prise branche => chute tension a cause de PDT
	 	printf("i am stuck in while loop help ! reprendre_vehicule.c \n");
	 	checkstop();
		if(STOP_B){break;}
	 	timer_pause(4);
	}
	checkstop();
	if(STOP_B){break;}
	
	
	timer_pause(2);
	log_msg("sortie de la boucle d'inactivité blocké à 9V");
	
	log_msg("passage à 12V DC");
	generateur_mode(DC);
	timer_pause(1);
	checkstop();
	if(STOP_B){break;}
	log_msg("verrouiller trappe");
	prise_verrouiller();
	log_msg("eteindre les voyants CHARGE et PRISE");
	voyants_set_charge(OFF);
	voyants_set_prise(OFF);
	log_msg("allumer voyants disponible");
	voyants_set_dispo(VERT);
	log_msg("arrete de generer tension");
	generateur_mode(OFF);
	REPRIS = 1;
	
	}while(REPRIS ==0);
	
	checkstop();
	return (REPRIS);
}
