#ifndef BASECLIENT_H
#define BASECLIENT_H

#define clients_details_file "./bins/donneesbaseclient.bin"

int baseclient_authentifier(int numcarte);
void baseclient_init();
void baseclient_client_toggle_connected(int num_client);

#endif
