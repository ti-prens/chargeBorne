#include <unistd.h>
#include "voyants.h"




entrees *io;
int shmid;

//initialistation des voyants 
void voyants_initialiser()
{
io=acces_memoire(&shmid);
/*associe la zone de memoire partagee au pointeur*/
if(io==NULL) printf("Erreur pas de mem sh\n");
}


void set_charge()
{
}
void set_dispo()
{io->led_dispo=VERT;
}

int dispo()
{
}


void blink_charge()
{
int i;
for(i=0;i<8;i++)
	{usleep(500000);//suspend le processus en cours
	 io->led_charge=VERT;
	 usleep(500000);
	 io->led_charge=OFF;
	}

}
