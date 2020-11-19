#include "prise.h"

#include <donnees_borne.h>
#include <memoire_borne.h>
#include <donnees.h>
#include <mem_sh.h>

entrees *io;
int memory_id;
	

void prise_initialiser()
{
	io = acces_memoire(&memory_id);
	if (io==NULL) printf("Erreur de memoire Sh \n");
}

void prise_verouiller_trappe()
{
	io->
}

void prise_deverouiller_trappe()
{

}

void prise_set_prise()
{

}
