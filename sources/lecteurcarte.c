//librairie externe
#include <unistd.h>
#include <stdio.h>
#include <lcarte.h>

//base de donnes indispensable pour l'identifiaction
#include "baseclient.h"

//bibliotheque des chefs d'orchestre
#include "lecteurcarte.h"

//bibliotheque pour les clients 
#include "installer_vehicule.h"
#include "charger_batterie.h"
#include "reprendre_vehicule.h"

//bibliotheque pour les gerants
/*
#include "gerer_clients.h"
#include "gerer_borne.h"
*/

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
int num_client=0;

// acquerir les varibales globales pour synchroniser les morceaux

extern int STOP_B;
extern int DISPO;

extern int INSTALLE;
extern int CHARGE;
extern int REPRIS;

void checkdispo(void)
{
	extern int DISPO;
	DISPO = DISPO && generateur_dispo();
	//printf("Dispo = %d \n",DISPO);
}




void lecteurcarte_initialiser()
{
	io=acces_memoire(&shmid);
	//ajouter un commentaire pour dire que la carte est ien initialisé
	/*associe la zone de memoire partagee au pointeur*/
	if(io==NULL) printf("Erreur pas de mem sh\n");
	/*
	log_msg("utlisation des procedures/fonctions fournies pour l'initialisation du lecteur de carte");
    initialisations_ports();
    */	
}



void lecteurcarte_lire_carte()
{
	log_msg("debut lecteurcarte_lire_carte()\n");
	
	
	unsigned short int numero;
		
	attente_insertion_carte();	
	numero=lecture_numero_carte();
	
	printf("Badge inséré,numero lu %d \n", lecture_numero_carte());	
	attente_retrait_carte();	
	
	//une fois carte en traitement systeme n'est plus disponible
	timer_pause(2); //temps pour suivre le programme
	
	checkstop(); // refresh STOP_B value
	checkdispo(); //refresh DISPO value
	if (baseclient_authentifier(numero)== 0)
	{	//échec de la verification client
		log_msg("échec de connexion");
		printf("Ereur 404 : (super fancy)\n -votre carte n'est pas reconnue");
		log_msg("blink defaut en ROUGE pour 8 secondes");
		voyants_blink_defaut(ROUGE);
	}
	
	checkstop(); // refresh STOP_B value
	checkdispo(); //refresh DISPO value
		
	if (baseclient_authentifier(numero)== 2 && STOP_B == 0 && DISPO == 0)
	{
		REPRIS = reprendre_vehicule(); 
		
		if (REPRIS == 1)
		{ 
			log_msg("bonne execution de reprendre_vehicule");
			log_msg("client deconnecté -> prise debrancher");
			baseclient_client_toggle_connected(num_client);	
			REPRIS = 0;
			INSTALLE = 0;
		}
	}
	
	checkstop(); // refresh STOP_B value
	checkdispo(); //refresh DISPO value
			
	if(baseclient_authentifier(numero)== 1 && STOP_B == 0 && DISPO == 1 && generateur_dispo())
	{	//si c'est le premier passage d'un client et que la borne est disponible :
		DISPO = 0; //des qu'un utilisateur commence ses config la borne n'est plus disponible
		// on appelle installer vehicule
		log_msg("succes de la verification client");
		num_client=numero;
		printf("authentification OK \n ");
		
		INSTALLE = installer_vehicule(num_client);
		if (INSTALLE == 1)
		{ 
			log_msg("bonne execution de installer_vehicule");
			baseclient_client_toggle_connected(num_client);
			log_msg("enregistrer presence vehicule sur la borne");
		}
		else if (INSTALLE == 2)
		{
			log_msg("bonne execution de installer_vehicule");
			log_msg("MAIS depassement du temps limite");	
			INSTALLE = 0;
		}
	
	
		checkstop(); // refresh STOP_B value
	
		if (INSTALLE == 1 && STOP_B == 0)
		{	//une fois que le vehicule a ete installer
			
			//on arrive à la deuxirme couche ^^ enfin 
			CHARGE = charger_batterie();
			if (CHARGE == 1){ log_msg("bonne execution de charger_batterie");}	
		}
	}
	checkstop(); // refresh STOP_B value
	checkdispo(); //refresh DISPO value
	
	if(baseclient_authentifier(numero)== 1 && STOP_B == 0 && DISPO == 0) 
	{	//chargeur non disponible 
	
		log_msg("bon numero mais chargeur pas disponible");
		printf("Ereur 404 : (super fancy)\n");
		log_msg("blink defaut en ROUGE pour 8 secondes");
		voyants_blink_defaut(ROUGE);
	}
	
	
	
	//netoyage et fin de boucle programme
	timer_pause(5);
	checkstop(); // refresh STOP_B value
	checkdispo(); //refresh DISPO value
	
	if(STOP_B == 1)
	{
		checkstop();
		STOP_B = 0;
	}
	
	log_msg("utlisation des procedures(fonctions) fournies pour liberer les ports");
	liberation_ports();
 }
		
	
			
	




