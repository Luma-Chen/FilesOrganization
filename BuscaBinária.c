#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tendereco
{
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2];
};
typedef struct Tendereco Endereco;

int main (int argc, char** argv)
{
	FILE *f;
	Endereco e;
	int inicio, fim, i, posicao, meio;
	char search[9]; 
	meio= 0;
	inicio= 0;
	i= 0;
   	printf ("\nDigite o seu CEP:");
	scanf ("%s", search);	
	f= fopen ("cep_ordenado.dat","r");
	fseek (f, 0, SEEK_END); 
    posicao= ftell (f); 
    fim= (posicao/ sizeof (Endereco)) - 1; 
    rewind (f);
	if (inicio > fim)
	{
		printf ("\nErro, CEP %s nao encontrado", search);
	}
	
	while (inicio <= fim)
	{
		i++;
		meio= (inicio + fim)/ 2;
		fseek (f, meio*sizeof (Endereco), SEEK_SET);  
		fread (&e, sizeof (Endereco), 1, f);
		if (strncmp (search, e.cep, 8) == 0)
		{
			printf ("\nAchou o endereco! \n%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s", e.logradouro, e.bairro, e.cidade, e.uf, e.sigla, e.cep);
			break;
		}
		else 
			if (strncmp (search, e.cep, 8) < 0)
				fim= meio - 1; 
			else
				inicio= meio + 1;		
    }
    printf ("Numero de buscas necessarias: %d", i);
	fclose (f);
	return 0;
}
