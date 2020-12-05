#ifndef GENERATEUR_H
#define GENERATEUR_H


typedef enum {OUVERT, FERME} C_AC;

void generateur_initialiser();
void generateur_mode(pwm x);
void generateur_contacteur(C_AC x); //OUVERT, FERME

void generateur_charger_batterie();

#endif 
