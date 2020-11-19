#include <baseclient.h>

static unsigned int carte [8]={1,2,3,4,5,6,7,9};

int baseclient_authentifier(int numcarte)
{

int ok=0;
int i;
int n=8;

for(i=0;i<n;i++)
	{if(carte[i]==numcarte) ok=1;	
	}



return ok;}
