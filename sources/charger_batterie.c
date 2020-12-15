#include <unistd.h>
#include <donnees_borne.h>
#include <memoire_borne.h>
#include <lcarte.h>
#include <stdio.h>

#include "charger_batterie.h"

#include "borne.h"
#include "log.h"


entrees *io;
int shmid;


int CHARGE = 0;

int charger_batterie()
{	extern int STOP_B;
	do
	{
	
	log_msg("debut 2ieme couche\nCharger batterie\n\n");
	
	timer_pause(2);
	log_msg("prise verrouiller");
	prise_verrouiller();
	
	log_msg("voyant set prise = VERT");
	voyants_set_prise(VERT);
	timer_pause(2);
	
	
	//generer une tension +9V/-12V
	log_msg("pour generer du 9V/-12V : generateur_mode(AC_1K); ");
	generateur_mode(AC_1K);
	
	//vehicule ferme contacteur S2
	log_msg("test de contacteur S2 ferme par le vehicule");
	
	
	//tension passe à 6V
	log_msg("le vehicule a doit passer la tension à 6V");
	timer_pause(2);
	
	log_msg("contacteur AC ferme");
	generateur_contacteur(FERME); //AC
	//generer une tension +6V/-12V
	log_msg("generer une tension +6V/-12V -> passage en mode AC_CL");
	generateur_mode(AC_CL);
	log_msg("devrait observer le chargement de la batterie");
	//vehicule ouvre S2 (quand batterie charge)
	log_msg("vehicule ouvre s2 qd batterie charger");
	//vehicule fait remonter tension à +9V/-12V
	log_msg("test fin recharge");
	do
	{
		log_msg("test fin recharge");
		checkstop();
		if(STOP_B == 1)
		{
			printf("appuie bouton stop detecté\n");
			generateur_mode(DC);
			log_msg("arret du chargement du véhicule : generateur passe à DC et arret voyants charge");
			voyants_set_charge(OFF);
			generateur_contacteur(OUVERT);
			prise_deverrouiller();
			while(io->gene_u == 9)
			{
				printf("Debrancher votre vehicule\n");
			}
			voyants_set_prise(OFF);
			log_msg("vehicule debranché");
			
			CHARGE = 2;
			
			break;
		}
		timer_pause(4);
	}while(io->gene_u !=9);
	
	checkstop();
	if(STOP_B == 1){break;}
	
	
	timer_pause(2);
	log_msg("contacteur AC OUVERT");
	generateur_contacteur(OUVERT); //AC
	//generer une tension +9V
	log_msg("generer une tension +9V : mode DC");
	generateur_mode(DC);
	timer_pause(2);
	log_msg("voyant Charge passe au VERT");
	voyants_set_charge(VERT);	
	
	CHARGE = 1;
	
	}while(CHARGE == 0);
	
	return(CHARGE);
		

}
