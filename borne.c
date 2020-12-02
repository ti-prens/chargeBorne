#include <stdio.h>
#include <memoire_borne.h>
#include <donnees_borne.h>

#include "lecteurcarte.h"
#include "voyants.h"
#include "boutons.h"
#include "prise.h"
#include "generateur.h"


int main()
{

    lecteurcarte_initialiser();
    voyants_initialiser();
    boutons_initialiser();
   	prise_initialiser();
    generateur_initialiser();

    while (1)
    {
		lecteurcarte_lire_carte();
    }

}
