#include <stdio.h>
#include <stdlib.h>

#include <setjmp.h>

#include <memoire_borne.h>
#include <donnees_borne.h>


#include "borne.h" 			//sert à l'initialisation de la borne 
#include "log.h"			//sert au monitoring pour l'integration 

#include "lecteurcarte.h"	//sert à lancer le programme

#include "baseclient.h" 	// dans borne.c "baseclient.h"  ne sert qu' à creer une base de donnes client de test

//Des variables globales pour la commnication avec tt le monde

int STOP_B;
int INSTALLE;
int CHARGE;
int DISPO;
int REPRIS;

void initialisation_BORNE()
{
	lecteurcarte_initialiser();    
    voyants_initialiser();
   	boutons_initialiser();
   	prise_initialiser();
   	generateur_initialiser(); 	
}

void initialisation_var_globales()
{
	DISPO		= 1;
	STOP_B		= 0;
	INSTALLE	= 0;
	CHARGE		= 0;
	REPRIS		= 0;
}


int main()
{
   	setvbuf(stdout, NULL, _IONBF,0); // permet de desactive le buffer de linux pour sauvegarder les log dans un fichier 
   	
   	log_init(); 					//initialise le compte du log (important pour se retrouver)
    log_msg("reussite de l'init");	//test du bon fonctionnement du monitoring
    
    /* en commentaire (car pas nécessaire) si baseclient.bin la "base de donnes "crypté" :D existe deja ou est gerer ailleurs */
   	log_msg("generer une liste de client authentifiable");
   	baseclient_init();
   	
   	
    initialisation_BORNE();
    log_msg("initialisation de la borne");  
    initialisation_var_globales();
    log_msg("initialisation des variables globales");  
     	
    
    while(1)
    {    	 	
		lecteurcarte_lire_carte();
    }
    
    //atexit(initialisation_BORNE);

}
