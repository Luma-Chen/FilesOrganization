#include <stdio.h>
#include <stdlib.h>

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

int compara (const void *e1, const void *e2)
{
	return strncmp (((Endereco*) e1) -> cep, ((Endereco*) e2) -> cep, 8);
}
int main (int argc, char**argv)
{
	FILE *file, *saida;
	Endereco *en;
	int posicao, qnt, qnt2, qnt3, qnt4, qnt5, qnt6, qnt7, qnt8, oitavo1, oitavo2, oitavo3, oitavo4, oitavo5, oitavo6, oitavo7, oitavo8;
	//inicio da divisão
	file= fopen ("cep.dat", "r");
	fseek (file, 0, SEEK_END);
	posicao= ftell (file);
	qnt= posicao/ (sizeof (Endereco));
	oitavo1= qnt/ 8; 
	en= (Endereco*) malloc (oitavo1 * sizeof (Endereco));  //aloca o primeira oitavo do arquivo na memoria
	rewind (file);
	printf("\nPRIMEIRO OITAVO");
	if (fread (en, sizeof (Endereco), oitavo1, file) == oitavo1)
	{
		printf ("\nO arquivo foi lido");
	}
	qsort (en, oitavo1, sizeof (Endereco), compara);
	printf ("\nO primeiro oitavo foi ordenado");
	saida= fopen ("cep_1.dat", "w");
	fwrite (en, sizeof (Endereco), oitavo1, saida);
	fclose (saida);
	printf ("\nO primeiro oitavo foi escrito");
	free (en);

	qnt2= qnt - oitavo1; //atualiza o tamanho do arquivo restante
	oitavo2= qnt2/ 7; 
	en= (Endereco*) malloc ((oitavo2 * sizeof (Endereco)));
	printf ("\nSEGUNDO OITAVO");
	if (fread (en, sizeof (Endereco), oitavo2, file) == oitavo2)
	{
		printf ("\nO arquivo foi lido");
	}
	qsort (en, oitavo2, sizeof (Endereco), compara);
	printf ("\nO segundo oitavo foi ordenado");
	saida= fopen ("cep_2.dat", "w");
	fwrite (en, sizeof (Endereco), oitavo2, saida);
	fclose (saida);
	printf ("\nO segundo oitavo foi escrito");
	free (en);

	qnt3= qnt2 - oitavo2; 
	oitavo3= qnt3/ 6;
	en= (Endereco*) malloc ((oitavo3 * sizeof (Endereco)));
	printf ("\nTERCEIRO OITAVO");
	if (fread (en, sizeof (Endereco), oitavo3, file) == oitavo3)
	{
		printf ("\nO arquivo foi lido");
	}
	qsort (en, oitavo3, sizeof (Endereco), compara);
	printf ("\nO terceiro oitavo foi ordenado");
	saida= fopen ("cep_3.dat", "w");
	fwrite (en, sizeof (Endereco), oitavo3, saida);
	fclose (saida);
	printf ("\nO terceiro oitavo foi escrito");
	free (en);
 
	qnt4= qnt3 - oitavo3; 
	oitavo4= qnt4/ 5;
	en= (Endereco*) malloc ((oitavo4 * sizeof (Endereco)));
	printf ("\nQUARTO OITAVO");
	if (fread (en, sizeof (Endereco), oitavo4, file) == oitavo4)
	{
		printf("\nO arquivo foi lido");
	}
	qsort (en, oitavo4, sizeof (Endereco), compara);
	printf ("\nO quarto oitavo foi ordenado");
	saida= fopen ("cep_4.dat", "w");
	fwrite (en, sizeof (Endereco), oitavo4, saida);
	fclose (saida);
	printf ("\nO quarto oitavo foi escrito");
	free (en);

	qnt5= qnt4 - oitavo4; 
	oitavo5= qnt5/ 4; 
	en= (Endereco*) malloc ((oitavo5 * sizeof (Endereco)));
	printf ("\nQUINTO OITAVO");
	if (fread (en, sizeof (Endereco), oitavo5, file) == oitavo5)
	{
		printf ("\nO arquivo foi lido");
	}
	qsort (en, oitavo5, sizeof (Endereco), compara);
	printf ("\nO quinto oitavo foi ordenado");
	saida= fopen ("cep_5.dat", "w");
	fwrite (en, sizeof (Endereco), oitavo5, saida);
	fclose (saida); 
	printf ("\nO quinto oitavo foi escrito");
	free (en);

	qnt6= qnt5 - oitavo5; 
	oitavo6= qnt6/ 3; 
	en= (Endereco*) malloc ((oitavo6 * sizeof (Endereco)));
	printf ("\nSEXTO OITAVO");
	if (fread (en, sizeof (Endereco), oitavo6, file) == oitavo6)
	{
		printf ("\nO arquivo foi lido");
	}
	qsort (en, oitavo6, sizeof (Endereco), compara);
	printf ("\nO sexto oitavo foi ordenado");
	saida= fopen ("cep_6.dat", "w");
	fwrite (en, sizeof (Endereco), oitavo6, saida);
	fclose (saida);
	printf ("\nO sexto oitavo foi escrito");
	free (en);

	qnt7= qnt6 - oitavo6; 
	oitavo7= qnt7/ 2;  
	en= (Endereco*) malloc ((oitavo7 * sizeof (Endereco)));
	printf ("\nSETIMO OITAVO");
	if (fread (en, sizeof (Endereco), oitavo7, file) == oitavo7)
	{
		printf ("\nO arquivo foi lido");
	}
	qsort (en, oitavo7, sizeof (Endereco), compara);
	printf ("\nO setimo oitavo foi ordenado");
	saida= fopen ("cep_7.dat", "w");
	fwrite (en, sizeof (Endereco), oitavo7, saida);
	fclose (saida);
	printf ("\nO setimo oitavo foi escrito");
	free (en);

	qnt8= qnt7 - oitavo7; 
	oitavo8= qnt8/ 2;   
	en= (Endereco*) malloc ((oitavo8 * sizeof (Endereco)));
	printf ("\nOITAVO OITAVO");
	if (fread (en, sizeof (Endereco), oitavo8, file) == oitavo8)
	{
		printf ("\nO arquivo foi lido");
	}
	qsort (en, oitavo8, sizeof (Endereco), compara);
	printf ("\nO oitavo oitavo foi ordenado");
	saida= fopen ("cep_8.dat", "w");
	fwrite (en, sizeof (Endereco), oitavo8, saida);
	fclose (saida); 
	printf ("\nO oitavo oitavo foi escrito");
	free (en);
	fclose (file);
	
	//começo da intercalação
	FILE *a, *b, *c, *d, *e, *f, *g, *h;  //variaveis de divisão do arquivo
    FILE *saida1, *saida2, *saida3, *saida4;
	Endereco en1, en2, en3, en4, en5, en6, en7, en8;
	a= fopen ("cep_1.dat", "r");
	b= fopen ("cep_2.dat", "r");
    c= fopen ("cep_3.dat", "r");
    d= fopen ("cep_4.dat", "r");
	e= fopen ("cep_5.dat", "r");
	f= fopen ("cep_6.dat", "r"); 
	g= fopen ("cep_7.dat", "r"); 
	h= fopen ("cep_8.dat", "r");
	saida1= fopen ("saida1.dat", "w");
    saida2= fopen ("saida2.dat", "w");
    saida3= fopen ("saida3.dat", "w");
	saida4= fopen ("saida4.dat", "w"); 
	fread (&en1, sizeof (Endereco), 1, a); 
	fread (&en2, sizeof (Endereco), 1, b);
    fread (&en3, sizeof (Endereco), 1, c);
   	fread (&en4, sizeof (Endereco), 1, d);
    fread (&en5, sizeof (Endereco), 1, e);
    fread (&en6, sizeof (Endereco), 1, f);
    fread (&en7, sizeof (Endereco), 1, g);
    fread (&en8, sizeof (Endereco), 1, h);

	while (!feof (a) && !feof (b))  
	{
		if (compara (&en1, &en2) < 0) 
		{
			fwrite (&en1, sizeof (Endereco), 1, saida1);
			fread (&en1, sizeof (Endereco), 1, a);  
		}
		else
		{
			fwrite (&en2, sizeof (Endereco), 1, saida1);
			fread (&en2, sizeof (Endereco), 1, b);
		}
	}
	while (!feof (a))
	{
		fwrite (&en1, sizeof (Endereco), 1, saida1);
		fread (&en1, sizeof (Endereco), 1, a);		
	}
	while (!feof (b))
	{
		fwrite (&en2, sizeof (Endereco), 1, saida1);
		fread (&en2, sizeof (Endereco), 1, b);		
	}
	fclose (a);
	fclose (b);
	fclose (saida1);

	while (!feof (c) && !feof (d))  
	{
		if (compara (&en3, &en4) < 0) 
		{
			fwrite (&en3, sizeof (Endereco), 1, saida2);
			fread (&en3, sizeof (Endereco), 1, c);  
		}
		else
		{
			fwrite (&en4, sizeof (Endereco), 1, saida2);
			fread (&en4, sizeof (Endereco), 1, d);
		}
	}
	while (!feof (c))
	{
		fwrite (&en3, sizeof (Endereco), 1, saida2);
		fread (&en3, sizeof (Endereco), 1, c);		
	}
	while (!feof (d))
	{
		fwrite (&en4, sizeof (Endereco), 1, saida2);
		fread (&en4, sizeof (Endereco), 1, d);		
	}
	fclose (c);
	fclose (d);
	fclose (saida2); 
	
	while (!feof (e) && !feof (f))  
	{
		if (compara (&en5, &en6) < 0) 
		{
			fwrite (&en5, sizeof (Endereco), 1, saida3);
			fread (&en5, sizeof (Endereco), 1, e);  
		}
		else
		{
			fwrite (&en6, sizeof (Endereco), 1, saida3);
			fread (&en6,sizeof (Endereco), 1, f);
		}
	}
	while (!feof (e))
	{
		fwrite (&en5, sizeof (Endereco), 1, saida3);
		fread (&en5, sizeof (Endereco), 1, e);		
	}
	while (!feof (f))
	{
		fwrite (&en6, sizeof (Endereco), 1, saida3);
		fread (&en6, sizeof (Endereco), 1, f);		
	}
	fclose (e);
	fclose (f);
	fclose (saida3);
	
	while (!feof (g) && !feof (h))  
	{
		if (compara (&en7, &en8) < 0) 
		{
			fwrite (&en7, sizeof (Endereco), 1, saida4);
			fread (&en7, sizeof (Endereco), 1, g);  
		}
		else
		{
			fwrite (&en8, sizeof (Endereco), 1, saida4);
			fread (&en8, sizeof (Endereco), 1, h);
		}
	}
	while (!feof (g))
	{
		fwrite (&en7, sizeof (Endereco), 1, saida4);
		fread (&en7, sizeof (Endereco), 1, g);		
	}
	while (!feof (h))
	{
		fwrite (&en8, sizeof (Endereco), 1, saida4);
		fread (&en8, sizeof (Endereco), 1, h);		
	}
	fclose (g);
	fclose (h);
	fclose (saida4); 
	
    FILE *saida5, *saida6;  
	Endereco esaida1, esaida2, esaida3, esaida4;
	saida1= fopen ("saida1.dat", "r"); 
	saida2= fopen ("saida2.dat", "r");
   	saida3= fopen ("saida3.dat", "r");
	saida4= fopen ("saida4.dat", "r");	
	saida5 = fopen("saida5.dat","w"); 
	saida6 = fopen("saida6.dat","w");
	fread (&esaida1, sizeof (Endereco), 1, saida1); 
	fread (&esaida2, sizeof (Endereco), 1, saida2);
	fread (&esaida3, sizeof (Endereco), 1, saida3);
	fread (&esaida4, sizeof (Endereco), 1, saida4);
	//intercalando as saídas
	while (!feof (saida1) && !feof (saida2))  
	{
		if (compara (&esaida1, &esaida2) < 0) 
		{
			fwrite (&esaida1, sizeof (Endereco), 1, saida5);
			fread (&esaida1, sizeof (Endereco), 1, saida1);  
		}
		else
		{
			fwrite (&esaida2, sizeof (Endereco), 1, saida5);
			fread (&esaida2, sizeof (Endereco), 1, saida2);
		}
 	}
	while (!feof (saida1))
	{
		fwrite (&esaida1, sizeof (Endereco), 1, saida5);
		fread (&esaida1, sizeof (Endereco), 1, saida1);		
	}
	while (!feof (saida2))
	{
		fwrite (&esaida2, sizeof (Endereco), 1, saida5);
		fread (&esaida2, sizeof (Endereco), 1, saida2);		
	}	
	fclose (saida5); 

	while (!feof (saida3) && !feof (saida4))  
	{
		if (compara (&esaida3, &esaida4) < 0) 
		{
			fwrite (&esaida3, sizeof (Endereco), 1, saida6);
			fread (&esaida3, sizeof (Endereco), 1, saida3);  
		}
		else
		{
			fwrite (&esaida4, sizeof (Endereco), 1, saida6);
			fread (&esaida4, sizeof (Endereco), 1, saida4);
		}
	}
	while (!feof (saida3))
	{
		fwrite (&esaida3, sizeof (Endereco), 1, saida6);
		fread (&esaida3, sizeof (Endereco), 1, saida3);		
	}
	while (!feof (saida4))
	{
		fwrite (&esaida4, sizeof (Endereco), 1, saida6);
		fread (&esaida4, sizeof (Endereco), 1, saida4);		
	}
	fclose(saida6); 

	//intercalando as últimas saídas em um arquivo único ordenado
	FILE *final; //arquivo ordenado
	Endereco esaida5, esaida6;
	saida5= fopen ("saida5.dat", "r");  
	saida6= fopen ("saida6.dat", "r");
	final= fopen ("final.dat", "w"); 
	fread (&esaida5, sizeof (Endereco), 1, saida5); 
	fread (&esaida6, sizeof (Endereco), 1, saida6);
	while (!feof (saida5) && !feof (saida6))  
	{
		if (compara (&esaida5, &esaida6) < 0) 
		{
			fwrite (&esaida5, sizeof (Endereco), 1, final);
			fread (&esaida5, sizeof (Endereco), 1, saida5);  
		}
		else
		{
			fwrite (&esaida6, sizeof (Endereco), 1, final);
			fread (&esaida6, sizeof (Endereco), 1, saida6);
		}
	}
	while (!feof (saida5))
	{
		fwrite (&esaida5, sizeof (Endereco), 1, final);
		fread (&esaida5, sizeof (Endereco), 1, saida5);		
	}
	while (!feof (saida6))
	{
		fwrite (&esaida6, sizeof (Endereco), 1, final);
		fread (&esaida6, sizeof (Endereco), 1, saida6);		
	}
	fclose (saida6); 
	fclose (saida5); 
	fclose (final); 
	return 0; 
}
