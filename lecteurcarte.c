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
}

void lecteurcarte_lire_carte()
{
	unsigned short int numero;
	
	
	
	attente_insertion_carte();
	timer_initialiser();
	numero=lecture_numero_carte();
	
	
	printf("Badge inséré,numero lu %d \n", lecture_numero_carte());
	attente_retrait_carte();	//une fois carte en traitement systeme n'est plus disponible
	
	
	//succes de la verification client 
	if (baseclient_authentifier(numero)==1)
		{
			num_client=numero;
			printf("authentification OK \n ");
		 	voyants_blink_charge(VERT);
		 	
		 	timer_reset();
/*debug :*/	printf("timer get value = %d \n",timer_get_value());
		 	
			while(timer_get_value()< 60)
			{
				if(boutons_charge_status() == 1)
		 		{
		 			
		 			printf("charge appui\n");
		 			voyants_set_dispo(OFF);
		 			
		 			//power 12V_DC
		 			generateur_mode(DC);
		 			generateur_contacteur(FERME);
		 			prise_deverrouiller();
		 			
		 			
		 			voyants_set_charge(ROUGE);
		 			//attendre prise vehicule 
		 			while(io->gene_u == 12)
		 			{
		 				//do nothing
		 				// prise branche => chute tension a cause de PDT
		 			}
		 			
		 			
		 			//on arrive à la deuxirme couche ^^ enfin 
		 			generateur_charger_batterie();
		 			
		 		}
		 		
		 		
		 		if(boutons_stop_status() == 1)
		 		{
		 			printf("stop appui\n");
		 			break;			
		 		}
		 	}
		 
			if(timer_get_value()>60) 
			{
				printf("Temps ecoule!!! \n");
			}
		 			 	
		 }
	
	
	
	//échec de la verification client
	else
	{	voyants_blink_defaut(ROUGE);
		printf("authentification echouée \n");
		lecteurcarte_initialiser();
	}
	
 }
		
	
			
	




