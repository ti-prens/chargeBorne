#include <unistd.h>
#include "timer.h"
#include <donnees_borne.h>
#include <memoire_borne.h>

entrees *io;
int shmid;
int depart_timer;

void timer_initialiser()
{
io=acces_memoire(&shmid);
/*associe la zone de memoire partagee au pointeur*/
if(io=NULL) printf("Erreur pas de mem sh\n");
depart_timer=io->timer_sec;
}


int timer_valeur()
{
timer=O;
timer=(io->timer_sec)-depart_timer;
return timer;
}

void timer_raz()
{depart_timer=0;
}
