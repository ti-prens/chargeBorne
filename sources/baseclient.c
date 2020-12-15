#include <stdlib.h>
#include <stdio.h>

#include "baseclient.h"



static int SIZE_OF_BASE = 9 ;

struct clients
{
	unsigned short int id, connected, security_byte ;
};//connected = 0 si la voiture n'est pas branché et 1 sinon
// Je ne suis pas encore sure de ce que je veux faire de security_byte ^^ 




void baseclient_init() //write some clients to bin file for test purposes 
{
	FILE *fpointeur;
	
	if ( (fpointeur = fopen(clients_details_file,"wb+"))== NULL) //baseclient_init overwrite old file
	{
		printf("je n'arrive pas a trouver les clients");
		exit(1);
	}
	
	struct clients LeBuffer;
	for(int i =1;i<= SIZE_OF_BASE;i++)
	{
		LeBuffer.id = i;
		LeBuffer.connected =0;
		LeBuffer.security_byte = 5*i+1;
		fwrite(&LeBuffer,sizeof(struct clients),1,fpointeur);
	}
	
	fclose(fpointeur);
		
}



int baseclient_authentifier(int numcarte)
{ // retourne le statut du client 
	/* 
		0 => non reconnue
		1 => premier passage
		2 => vient recuperer sa voiture
	*/
	int client_status = 0; 
	
	int n; //variable inutile si ce n'est que ça enleve un warning inutile
	
	
	struct clients atrouver;
	struct clients LeBuffer;
	
	
	atrouver.id=numcarte;
	atrouver.security_byte=5*atrouver.id+1;
	
	
	FILE *fpointeur;
	if ( (fpointeur = fopen(clients_details_file,"rb+"))== NULL) //do NOT overwrite old file
	{
		printf("je n'arrive pas a trouver le fichier clients");
		exit(1);
	}
	
	
	
	for(int j =0 ; j <= SIZE_OF_BASE ;j++)
	{
		
		n = fread(&LeBuffer,sizeof(struct clients),1,fpointeur);
		
		if ( 	LeBuffer.id == atrouver.id &&
				LeBuffer.security_byte == atrouver.security_byte )
		{
			if (LeBuffer.connected == 1) {client_status=2;}
			else 
				if (LeBuffer.connected == 0) {client_status=1;}
				else {client_status= 0;}
		} 
	}if (n == SIZE_OF_BASE){printf("Interessant");}
	
	fclose(fpointeur);
	
	return client_status;
}

void baseclient_client_toggle_connected(int num_client)
{
	int n; //variable inutile si ce n'est que ça enleve un warning inutile
	
	struct clients atrouver;
	struct clients LeBuffer;
	
	
	atrouver.id=num_client;
	atrouver.security_byte=5*atrouver.id+1;
	
	
	FILE *fpointeur;
	if ( (fpointeur = fopen(clients_details_file,"rb+"))== NULL) //do NOT overwrite old file
	{
		printf("je n'arrive pas a trouver le fichier clients");
		exit(1);
	}
	
	
	
	for(int j =0 ; j <= SIZE_OF_BASE ;j++)
	{
		
		n = fread(&LeBuffer,sizeof(struct clients),1,fpointeur); //ça retourne le ombre de structure lue 
		// ignorer le warning
		if ( 	LeBuffer.id == atrouver.id &&
				LeBuffer.security_byte == atrouver.security_byte )
		{
			fseek(fpointeur,-1*sizeof(struct clients),SEEK_CUR); //ftell();
			if (LeBuffer.connected == 1) { 	atrouver.connected = 0 ; }
			else atrouver.connected =1;
			
			fwrite(&atrouver,sizeof(struct clients),1,fpointeur);
		}
		 
	}
	if (n == SIZE_OF_BASE){printf("Interessant");}
	fclose(fpointeur);
}
/*
void basecleint_add(int numcarte)
{

}
void basecleint_remove_client(int numcarte, file)
{

}

void baseclient_search_client(int numcarte, file)
{
	fread(&

}

void baseclient_add_user(int numcarte)
{

}*/

