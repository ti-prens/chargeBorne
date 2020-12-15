#ifndef BASECLIENT_H
#define BASECLIENT_H

#define clients_details_file "./bins/donneesbaseclient.bin"



//static unsigned int carte [8]={1,2,3,4,5,6,7,9};
//static char clients_details_file = "donneesbaseclient.bin";

typedef enum {client_connecte,client_deconnecte,client_inconnu,gerant} operateur;

operateur baseclient_authentifier(int numcarte);
void baseclient_init();
void baseclient_client_toggle_connected(int num_client);

#endif
