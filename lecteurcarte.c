#include <unistd.h>
#include <stdio.h>
#include "lecteurcarte.h"

#include <baseclient.h>


int numero=0;




void lecteurcarte_initialiser()
{
}

void lecteurcarte_lire_carte()
{
	attente_insertion_carte();
	printf("numero lu %d \n", lecture_numero_carte());
	if (carte_inseree()/*&& voyants disponibles */)
	{
		baseclient_authentifier(numero);
	}

}

