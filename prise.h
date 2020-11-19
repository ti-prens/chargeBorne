#ifndef PRISE_H
#define PRISE_H
#include <donnees_borne.h>
#include <memoire_borne.h>
#include <lcarte.h>
#include <stdio.h>
#include "baseclient.h"
#include "voyants.h"
#include "timer.h"
#include "boutons.h"
#include "lecteurcarte.h"

void prise_initialiser();
void verouiller_trappe();
void deverouiller();
void set_prise();


#endif 
