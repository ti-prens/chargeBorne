#ifndef VOYANTS_H
#define VOYANTS_H
#include <donnees_borne.h>
#include <memoire_borne.h>


void voyants_initialiser();

void voyants_set_dispo(led x);
void voyants_set_charge(led  x);

void voyants_blink_charge(led x);
void voyants_blink_default(led x);

#endif
