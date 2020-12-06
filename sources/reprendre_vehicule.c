#include <unistd.h>
#include <donnees_borne.h>
#include <memoire_borne.h>
#include <lcarte.h>
#include <stdio.h>

#include "reprendre_vehicule.h"

#include "generateur.h"
#include "prise.h"
#include "voyants.h"
#include "timer.h"
#include "baseclient.h"

#include "log.h"


entrees *io;
int shmid;


void reprendre_vehicule(int num_client)
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
	 	//printf("i am stuck in while loop help ! lecteurcarte.c \n")
	 	;timer_pause(0);
	}
	log_msg("client deconnecté -> prise debrancher");
	baseclient_client_toggle_connected(num_client);	
	timer_pause(2);
	log_msg("sortie de la boucle d'inactivité blocké à 9V");
	
	log_msg("passage à 12V DC");
	generateur_mode(DC);
	timer_pause(1);
	log_msg("verrouiller trappe");
	prise_verrouiller();
	log_msg("eteindre les voyants CHARGE et PRISE");
	voyants_set_charge(OFF);
	voyants_set_prise(OFF);
	log_msg("allumer voyants disponible");
	voyants_set_dispo(VERT);
	log_msg("arrete de generer tension");
	generateur_mode(OFF);
}
