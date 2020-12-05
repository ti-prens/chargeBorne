#include <unistd.h>
#include <stdio.h>
#include <baseclient.h>
#include <lcarte.h>

#include "lecteurcarte.h"

#include "baseclient.h"
#include "voyants.h"
#include "timer.h"
#include "boutons.h"
#include "prise.h"
#include "generateur.h"

#include "log.h"



entrees *io;
int shmid;
int num_client=0;



void lecteurcarte_initialiser()
{
	io=acces_memoire(&shmid);
	//ajouter un commentaire pour dire que la carte est ien initialisé
	/*associe la zone de memoire partagee au pointeur*/
	if(io==NULL) printf("Erreur pas de mem sh\n");
	//apres initialisation syteme passe à etat dispo
	voyants_set_dispo(VERT);
	prise_verrouiller();
}

void lecteurcarte_lire_carte()
{

	lecteurcarte_initialiser();
	
	
	unsigned short int numero;
	
	
	
	attente_insertion_carte();
	timer_initialiser();
	numero=lecture_numero_carte();
	
	
	printf("Badge inséré,numero lu %d \n", lecture_numero_carte());	
	attente_retrait_carte();	
	
	//une fois carte en traitement systeme n'est plus disponible
	//timer_pause(2);
	
	log_msg("succes de la verification client");
	 
	if (baseclient_authentifier(numero)==1)
		{
			num_client=numero;
			printf("authentification OK \n ");
		 	voyants_blink_charge(VERT);
		 	
		 	timer_reset();
		 	log_msg("Timer reset : compte des 60 secondes commence");
/*debug :*/	printf("timer get value = %d \n",timer_get_value());
		 	
			while(timer_get_value()<= 60)
			{
				if(boutons_charge_status() == 1)
		 		{
		 			
		 			log_msg("charge appui");
		 			log_msg("dispo set = OFF");
		 			voyants_set_dispo(OFF);
		 			
		 			timer_pause(2);
		 			
		 			//power 12V_DC
		 			log_msg("prise deverrouiller");
		 			prise_deverrouiller();
		 			
		 			log_msg("generateur_mode(DC);");
		 			generateur_mode(DC);
		 				//generateur_contacteur(FERME);
		 			
		 			timer_pause(2);
		 			
		 			
		 			log_msg("set_charge = ROUGE");
		 			voyants_set_charge(ROUGE);
		 			//attendre prise vehicule 
		 			log_msg("attendre prise vehicule avant boucle d'inactivité blocké à 12V");
		 			while(io->gene_u == 12)
		 			{
		 				//do nothing
		 				// prise branche => chute tension a cause de PDT
		 				//printf("i am stuck in while loop help ! lecteurcarte.c \n");
		 				timer_pause(0);
		 			}
		 			
		 			timer_pause(2);
		 			log_msg("sortie de la boucle d'inactivité blocké à 12V");
		 			//on arrive à la deuxirme couche ^^ enfin 
		 			generateur_charger_batterie();
		 			
		 		}
		 		
		 		
		 		if(boutons_stop_status() == 1)
		 		{
		 			log_msg("stop appui");
		 			timer_pause(2);
		 			break;			
		 		}
		 	}
		 
			if(timer_get_value()>60) 
			{
				log_msg("Temps ecoule!!! \n");
				timer_pause(2);
			}
		 			 	
		 }
	
	
	
	//échec de la verification client
	else
	{	
		log_msg("échec de la verification client");
		log_msg("blink defaut en ROUGE pour 8 secondes");
		voyants_blink_defaut(ROUGE);
		printf("authentification echouée \n");
		
		timer_pause(2);
	}
	
 }
		
	
			
	




