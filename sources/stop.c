#include "stop.h"

#include "boutons.h"
#include "log.h"


//fonction compatible avec l'ajout d'une autre thread qui verifie l'etat du boutons stop en parralel pendant les nombreux moments de pause  de la thread prinsipale  
void checkstop() //je verifie si il ya stop : si oui je rond la boucle actuelle ... et sa remonte avec d'autre appelles de checkstop()
{
	extern int STOP_B; 
	
	STOP_B = STOP_B || boutons_stop_status();
	if(STOP_B)
	{
		printf("bouton stop a ete appuyer \n \n");
		log_msg("on quitte tout le programme (oui ça casse tout... mais je fais le menage en partant)");
		
		//goto start; 	//I tried some magic xD
		//exit(1);    	//I tried atexit function l'exit on retourne au debut du programme
		//break;		//Now i just get out of loops (yes I am tired ...but it's fun)
	}	
}

