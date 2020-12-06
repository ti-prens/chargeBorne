#ifndef GENERATEUR_H
#define GENERATEUR_H


typedef enum {OUVERT, FERME} C_AC;

void generateur_initialiser();
void generateur_mode(pwm x);
void generateur_contacteur(C_AC x); //OUVERT, FERME
int generateur_dispo(void); //1:0 selon dispo

void generateur_charger_batterie(); 
//2ieme partie du programme point de vue conception UML

#endif 
