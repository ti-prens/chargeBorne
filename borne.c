#include <stdio.h>
#include <memoire_borne.h>
#include <donnees_borne.h>

#include "lecteurcarte.h"
#include "voyants.h"
#include "boutons.h"

// manque biblio de generateur

int main()
{

    lecteurcarte_initialiser();
    voyants_initialiser();
    boutons_initialiser();
   	// prise_initialiser();
    //reste prise et generateur 

    while (1)
    {
		lecteurcarte_lire_carte();
    }

}
