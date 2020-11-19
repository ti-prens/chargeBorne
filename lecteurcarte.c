#include <unistd.h>
#include <stdio.h>
#include "lecteurcarte.h"

#include <baseclient.h>



entrees *io;
int shmid;
int num_client=0;




void lecteurcarte_initialiser()
{io=acces_memoire(&shmid);

//ajouter un commentaire pour dire que la carte est ien initialisé
/*associe la zone de memoire partagee au pointeur*/
if(io==NULL) printf("Erreur pas de mem sh\n");
}

void lecteurcarte_lire_carte()
{unsigned short int numero;
	attente_insertion_carte();
	timer_initialiser();
	numero=lecture_numero_carte();
	printf("Badge inséré,numero lu %d \n", lecture_numero_carte());
	
	
	if (baseclient_authentifier(numero)==1)
		{num_client=numero;
		printf("authentification OK \n ");
		 blink_charge();
		 while((valeur_timer())< 60 && (charge()==0 && stop()==0))
		 {
		 }
		 
		 if(stop()==1)
		 {io->bouton_stop=0;
		 }
		 
		 if(valeur_timer()>60)
		 {printf("Temps ecoule!!! \n");
		 lecteurcarte_initialiser();
		 }
		 
		 if(charge() == 1)
		 	{io->bouton_charge=0;
		 	printf("charge appui");
		 	io->led_dispo=OFF;
		 	charge();
		 	//fin charge
		 	attente_insertion_carte();
		 	numero=lecture_numero_carte();
		 	printf("numero lu %d \n",numero);
		 	while(numero != num_client)
		 		{usleep(1000000);
		 		io->led_defaut=ROUGE;
		 		usleep(1000000);
		 		io->led_defaut=OFF;
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
		 else{
		      printf("authentification echouée \n");
		     lecteurcarte_initialiser();
		     
		     }
 }
		
	
			
	




