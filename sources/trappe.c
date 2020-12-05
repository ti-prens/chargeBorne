

#include <donnees_borne.h>
#include <memoire_borne.h>
#include <unistd.h>


#include "voyants.h"
#include "trappe.h"



entrees *io;
int shmid;

//initialistation des voyants 
void trappe_initialiser()
{
	io=acces_memoire(&shmid);
	/*associe la zone de memoire partagee au pointeur*/
	if(io==NULL) printf("Erreur pas de mem sh\n");
}


void trappe_verrouiller()
{
	voyants_set_trappe(OFF);
	//contacteur_AC = 0; // circuit ouvert 
}
void trappe_deverrouiller()
{
	voyants_set_trappe(VERT);
	//contacteur_AC = 1; // circuit fermé 
}


bool trappe_state()
{
	return contacteur_AC;
}
