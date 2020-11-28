#include <unistd.h>
#include <stdio.h>
#include <baseclient.h>

#include "lecteurcarte.h"



entrees *io;
int shmid;
int num_client=0;




void lecteurcarte_initialiser()
{
	io=acces_memoire(&shmid);
	//ajouter un commentaire pour dire que la carte est ien initialisé
	/*associe la zone de memoire partagee au pointeur*/
	if(io==NULL) printf("Erreur pas de mem sh\n");
}

void lecteurcarte_lire_carte()
{
	unsigned short int numero;
	
	attente_insertion_carte();
	timer_initialiser();
	numero=lecture_numero_carte();
	
	printf("Badge inséré,numero lu %d \n", lecture_numero_carte());
	
	//succes de la verification client 
	if (baseclient_authentifier(numero)==1)
		{
			num_client=numero;
			printf("authentification OK \n ");
		 	voyants_blink_charge(VERT);
		 	while((valeur_timer())< 60 && (boutons_charge_status()==0 && boutons_stop_status()==0))
			{
		 	}
		 
		 	if(boutons_stop_status()==1)
		 	{
		 		io->bouton_stop=0;
		 	}
		 
			 if(valeur_timer()>60)
		 	{
		 		printf("Temps ecoule!!! \n");
		 		lecteurcarte_initialiser();
		 	}
		 
		 	if(boutons_charge_status() == 1)
		 	{
		 		io->bouton_charge=0;
		 		printf("charge appui");
		 		voyants_set_dispo(OFF);
		 		boutons_charge_status();
		 		//fin charge
		 		attente_insertion_carte();
		 		numero=lecture_numero_carte();
		 		printf("numero lu %d \n",numero);
		 		
		 		while(numero != num_client)
		 		{
		 			voyants_blink_defaut(ROUGE);
		 			
		 			attente_insertion_carte();
		 			numero=lecture_numero_carte();
		 			printf("numero lu %d \n",numero);
		 		}
		 		attente_retrait_carte();
		 		//deconnecter();
		 		/*while(tension()!=12)
		 		{
		 		}*/
		 	
		 		//verouiller_trappe();
		 		//io->led_prise=OFF;
		 		//io->led_dispo=VERT;
		 	}
		 }
	//échec de la verification client
	else
	{	voyants_blink_defaut(ROUGE);
		printf("authentification echouée \n");
		lecteurcarte_initialiser();
	}
	
 }
		
	
			
	




