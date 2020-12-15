//librairie externe
#include <unistd.h>
#include <stdio.h>
#include <lcarte.h>

#include "installer_vehicule.h"


//bibliotheque d'integration / de monitoring
#include "log.h"

//control bas niveau materielle
/* 
//ils sont repris à l'identique dans borne.h : 

#include "voyants.h"
#include "timer.h"
#include "boutons.h"
#include "prise.h"
#include "generateur.h"
#include "stop.h"
*/

#include "borne.h" //timer + voyants + prise + boutons + generateur + stop = 6
#include "stop.h"

entrees *io;
int shmid;



extern int STOP_B;
extern int DISPO;





int installer_vehicule(int num_client) { 
//retoune la raison de la fin de installer vehicule  {1 -> bon fonctionnement & 0 -> pas finis & 2 -> temps depasse}
int sortie_approuve = 0;
log_msg("blink charge en vert");
voyants_blink_charge(VERT);
		 	
timer_reset();
log_msg("Timer reset : compte des 60 secondes commence");
/*debug :*/	printf("timer get value = %d \n",timer_get_value());
do 
{			
	if(boutons_charge_status() == 1 && timer_get_value()<= 60)
	{
		log_msg("charge appui");
		log_msg("dispo set = OFF");
		DISPO = 0;
		voyants_set_dispo(OFF);
		
		checkstop();
	 	if(STOP_B){break;}
	 	timer_pause(2);
	 			
		//power 12V_DC
		log_msg("prise deverrouiller");
		prise_deverrouiller();
			
		log_msg("generateur_mode(DC);");
		generateur_mode(DC);
		//generateur_contacteur(FERME);
	 			
		checkstop();
	 	if(STOP_B){break;}
	 	timer_pause(2);
				
			
		log_msg("set_charge = ROUGE");
	 	voyants_set_charge(ROUGE);
	 	
	 	//attendre prise vehicule 
	 	log_msg("attendre prise vehicule avant boucle d'inactivité blocké à 12V");
	 	while(io->gene_u == 12)
	 	{
	 		//do nothing
	 		// prise branche => chute tension a cause de PDT
	 		printf("i am stuck in while loop help ! installer_vehicule.c \n");
	 		timer_pause(4);
	 		checkstop();
	 		if(STOP_B){break;}
	 	}
	 	
	 	checkstop();
	 	if(STOP_B){break;}
	 			
	 	timer_pause(2);
	 	log_msg("sortie de la boucle d'inactivité blocké à 12V");
	 	sortie_approuve = 1;
	}
	 	
	 if(timer_get_value()>60 && STOP_B == 0 )//&& CHARGE == 1) 
	{
		log_msg("Temps ecoule!!! \n");
		timer_pause(2);
		sortie_approuve = 2;
	}
}while(sortie_approuve == 0);

checkstop();
return(sortie_approuve); 

}
