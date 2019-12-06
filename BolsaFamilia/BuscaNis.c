#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ArvoreB.h"
 
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

ArvoreB_Pagina* ArvoreB_alocaPagina ()
{
    int i;
    ArvoreB_Pagina* resp= (ArvoreB_Pagina*) malloc (sizeof (ArvoreB_Pagina));
    resp -> quantidadeElementos= 0;
    resp -> paginaEsquerda= 0;
    for (i= 0; i< TAM_PAG; i++)
    {
        memset (resp -> elementos[i].chave, '\0', TAM_CHAVE);
        resp -> elementos[i].paginaDireita= 0;
        resp -> elementos[i].posicaoRegistro= 0;
    }
    return resp;
}
void ArvoreB_desalocaPagina (ArvoreB_Pagina* p)
{
    if (p)
    {
        free (p);
    }
}
ArvoreB* ArvoreB_Abre (const char* nomeArquivo)
{
    ArvoreB* resp= (ArvoreB*) 0;
    ArvoreB_Cabecalho* cabecalho= (ArvoreB_Cabecalho*) 0;
    ArvoreB_Pagina* raiz= (ArvoreB_Pagina*) 0;
    FILE* f= fopen (nomeArquivo, "r");
    if (!f)
    {
        f= fopen (nomeArquivo, "w");
        if (!f)
        {
            fprintf (stderr, "Arquivo %s não pode ser criado\n", nomeArquivo);
            return resp;
        }
        cabecalho= (ArvoreB_Cabecalho*) malloc (sizeof (ArvoreB_Cabecalho));
        cabecalho -> raiz= sizeof (ArvoreB_Cabecalho);
        fwrite (cabecalho, sizeof (ArvoreB_Cabecalho), 1, f);
        raiz= ArvoreB_alocaPagina ();
        fwrite (raiz, sizeof (ArvoreB_Pagina), 1, f);
        ArvoreB_desalocaPagina (raiz);
        free (cabecalho);
    }
    fclose (f);
    f= fopen (nomeArquivo, "rb+");
    resp= (ArvoreB*) malloc (sizeof (ArvoreB));
    resp -> f= f;
    resp -> cabecalho= (ArvoreB_Cabecalho*) malloc (sizeof (ArvoreB_Cabecalho));
    fread (resp-> cabecalho, sizeof (ArvoreB_Cabecalho), 1, f);
    return resp;
}
int ArvoreB_Compara (const void *e1, const void* e2)
{
    return strncmp (((ArvoreB_Elemento*) e1) -> chave, ((ArvoreB_Elemento*) e2) -> chave, TAM_CHAVE); 
}
void ArvoreB_escreveCabecalho (ArvoreB* arvore)
{
    fseek (arvore -> f, 0, SEEK_SET);
    fwrite (arvore -> cabecalho, sizeof (ArvoreB_Cabecalho), 1, arvore -> f);
}
void ArvoreB_Fecha (ArvoreB* arvore)
{
    if (arvore)
    {
        ArvoreB_escreveCabecalho (arvore);
        fclose (arvore -> f);
        free (arvore -> cabecalho);
        free (arvore);
    }
}
ArvoreB_Elemento* ArvoreB_Split (ArvoreB *arvore, long posicaoPagina, ArvoreB_Pagina* pagina, ArvoreB_Elemento* overflow)
{
    int i;
    ArvoreB_Elemento aux;
    ArvoreB_Elemento* resp;
    ArvoreB_Pagina* paginaSplit;
    //O elemento na área de overflow é menor que o ultimo elemento da página?
    if (ArvoreB_Compara (overflow,&pagina -> elementos[pagina -> quantidadeElementos - 1]) < 0)
    {
        //Trocar o último com o elemento no overflow e reordenar a página
        aux= *overflow;
        *overflow= pagina -> elementos[pagina -> quantidadeElementos - 1];
        pagina -> elementos[pagina -> quantidadeElementos - 1]= aux;
        qsort (pagina -> elementos, pagina -> quantidadeElementos, sizeof (ArvoreB_Elemento), ArvoreB_Compara);
    }
    paginaSplit= ArvoreB_alocaPagina ();
    for (i= TAM_PAG/ 2+1; i< TAM_PAG; i++)
    {
        paginaSplit -> elementos[paginaSplit->quantidadeElementos]= pagina-> elementos[i];
        paginaSplit -> quantidadeElementos++;
    }
    paginaSplit -> elementos[paginaSplit->quantidadeElementos]= *overflow;
    paginaSplit -> quantidadeElementos++;
    pagina -> quantidadeElementos= TAM_PAG/ 2;
    fseek (arvore -> f, posicaoPagina, SEEK_SET);
    fwrite (pagina, sizeof (ArvoreB_Pagina), 1, arvore -> f);
    fseek (arvore -> f, 0, SEEK_END);
    resp= (ArvoreB_Elemento*) malloc (sizeof (ArvoreB_Elemento));
    paginaSplit -> paginaEsquerda= pagina -> elementos[TAM_PAG/2].paginaDireita;
    memcpy (resp -> chave, pagina -> elementos[TAM_PAG/2].chave, TAM_CHAVE);
    resp -> posicaoRegistro= pagina -> elementos[TAM_PAG/2].posicaoRegistro;
    resp -> paginaDireita= ftell (arvore -> f);
    fwrite (paginaSplit, sizeof (ArvoreB_Pagina), 1, arvore -> f);
    ArvoreB_desalocaPagina (paginaSplit);
    return resp;
}
ArvoreB_Elemento* ArvoreB_Insere_Recursiva (ArvoreB* arvore, long posicaoPagina, char chave[TAM_CHAVE], long posicaoRegistro)
{
    int i;
    long posicaoPaginaFilho;
    ArvoreB_Elemento* resp= (ArvoreB_Elemento*) 0;
    ArvoreB_Elemento *elementoSplit= (ArvoreB_Elemento*) 0;
    ArvoreB_Elemento overflow;
    //printf("Inserindo %.8s na página %ld\n", chave, posicaoPagina);
    ArvoreB_Pagina *pagina= ArvoreB_alocaPagina ();
    fseek (arvore -> f, posicaoPagina, SEEK_SET);
    fread (pagina, sizeof (ArvoreB_Pagina), 1, arvore -> f);
    if (pagina -> paginaEsquerda == 0) //Folha
    {
        if (pagina -> quantidadeElementos < TAM_PAG)
        {
            memcpy (pagina-> elementos[pagina->quantidadeElementos].chave, chave, TAM_CHAVE);
            pagina -> elementos[pagina -> quantidadeElementos].posicaoRegistro= posicaoRegistro;
            pagina -> quantidadeElementos++;
            qsort (pagina -> elementos, pagina -> quantidadeElementos, sizeof (ArvoreB_Elemento), ArvoreB_Compara);
            fseek (arvore -> f, posicaoPagina, SEEK_SET);
            fwrite (pagina, sizeof (ArvoreB_Pagina), 1, arvore -> f);
        }
        else
        {
            memcpy (overflow.chave, chave, TAM_CHAVE);
            overflow.posicaoRegistro= posicaoRegistro;
            overflow.paginaDireita= 0;
            resp= ArvoreB_Split (arvore, posicaoPagina, pagina, &overflow);
        }
    }
    else //Não é folha
    {
        posicaoPaginaFilho= pagina -> paginaEsquerda;
        for (i= 0; i< pagina-> quantidadeElementos; i++)
        {
            if (strncmp (chave, pagina -> elementos[i].chave, TAM_CHAVE) < 0)
            {
                break;
            }
            posicaoPaginaFilho= pagina-> elementos[i].paginaDireita;
        }
        elementoSplit= ArvoreB_Insere_Recursiva (arvore, posicaoPaginaFilho, chave, posicaoRegistro);
        if (elementoSplit)
        {
            if (pagina-> quantidadeElementos < TAM_PAG)
            {
                pagina-> elementos[pagina->quantidadeElementos]= *elementoSplit;
                pagina-> quantidadeElementos++;
                qsort (pagina-> elementos, pagina-> quantidadeElementos, sizeof (ArvoreB_Elemento), ArvoreB_Compara);
                fseek (arvore-> f, posicaoPagina, SEEK_SET);
                fwrite (pagina, sizeof (ArvoreB_Pagina), 1, arvore-> f);
                free (elementoSplit);
            }
            else
            {
                resp= ArvoreB_Split (arvore, posicaoPagina, pagina, elementoSplit);
                free (elementoSplit);
            }
        }
    }
    ArvoreB_desalocaPagina (pagina);
    return resp;
}
void ArvoreB_Insere (ArvoreB* arvore, char chave[TAM_CHAVE], long posicaoRegistro)
{
    ArvoreB_Pagina *novaRaiz;
    ArvoreB_Elemento *elementoSplit;
    elementoSplit= ArvoreB_Insere_Recursiva (arvore, arvore -> cabecalho -> raiz, chave, posicaoRegistro);
    if (elementoSplit)
    {
        novaRaiz= ArvoreB_alocaPagina ();
        novaRaiz-> quantidadeElementos= 1;
        novaRaiz -> elementos[0]= *elementoSplit;
        novaRaiz -> paginaEsquerda= arvore -> cabecalho -> raiz;
        fseek (arvore -> f, 0, SEEK_END);
        arvore -> cabecalho -> raiz= ftell (arvore -> f);
        fwrite (novaRaiz, sizeof (ArvoreB_Pagina), 1, arvore -> f);
        ArvoreB_escreveCabecalho (arvore);
        ArvoreB_desalocaPagina (novaRaiz);
        free (elementoSplit);
    }
}
long ArvoreB_Busca_Recursiva (ArvoreB* arvore, long posicaoPagina, char chave[TAM_CHAVE])
{
	int i;
    if (posicaoPagina == 0)
    {
        return -1;
    }
    ArvoreB_Pagina *pagina= ArvoreB_alocaPagina ();
    fseek (arvore-> f, posicaoPagina, SEEK_SET);
    fread (pagina, sizeof (ArvoreB_Pagina), 1, arvore-> f);
    long posicaoPaginaFilho= pagina-> paginaEsquerda;
    for (i= 0; i< pagina-> quantidadeElementos; i++)
    {
        if (strncmp (chave, pagina-> elementos[i].chave, TAM_CHAVE) == 0)
        {
            // Achei
            long resp= pagina-> elementos[i].posicaoRegistro;
            ArvoreB_desalocaPagina (pagina);
            return resp;
        }
        if (strncmp (chave, pagina-> elementos[i].chave, TAM_CHAVE) < 0)
        {
            break;
        }
        posicaoPaginaFilho= pagina-> elementos[i].paginaDireita;
    }
    ArvoreB_desalocaPagina (pagina);
    return ArvoreB_Busca_Recursiva (arvore, posicaoPaginaFilho, chave);
}
long ArvoreB_Busca (ArvoreB* arvore, char chave[TAM_CHAVE])
{
    return ArvoreB_Busca_Recursiva (arvore, arvore-> cabecalho-> raiz, chave);
}
void ArvoreB_PrintDebug (ArvoreB* arvore)
{
    long posicaoPagina;
    int i;
    ArvoreB_Pagina *pagina= ArvoreB_alocaPagina ();
    fseek (arvore -> f, sizeof (ArvoreB_Cabecalho), SEEK_SET);
    posicaoPagina= ftell (arvore->f);
    while (fread (pagina, sizeof (ArvoreB_Pagina), 1, arvore -> f))
    {
        if (posicaoPagina == arvore -> cabecalho -> raiz)
        {
            printf ("* ");
        }
        else
        {
            printf ("  ");
        }
        printf ("%5ld => %5ld|", posicaoPagina, pagina -> paginaEsquerda);
        for (i= 0; i< pagina->quantidadeElementos; i++)
        {
 
            printf ("(%.8s)|%5ld|", pagina -> elementos[i].chave, pagina -> elementos[i].paginaDireita);
        }
        printf ("\n");
        posicaoPagina= ftell (arvore-> f);
    }
}

int main (int argc, char** argv)
{
    ArvoreB* a= ArvoreB_Abre ("arvore.dat");
   	FILE *f= fopen ("bolsa.csv", "r");
    char linha[2048];
    char nis[15];
    int n;
	n= 0;
    int coluna;
	coluna= 0;
    long posicao;
    char* campo;
    fgets (linha, 2048, f);
    posicao= ftell (f);
    fgets (linha, 2048, f);
    if (argc != 2)
    {
        fprintf (stderr, "\nErro na chamada do comando",  argv[0]);
        return 1;
    }
    sprintf (nis, "%s", argv[1]);
    posicao= ArvoreB_Busca (a, nis);
  	if (posicao > -1)
  	{
  		 while (!feof (f))
   		{
        	coluna= 0;
        	campo= strtok (linha, "\t");
       		while (campo)
        	{
            	if (coluna == 7)
            	{
                	strcpy (nis, campo);
                	printf ("NIS => %s esta em %ld\n", nis, posicao);
            	}
            	coluna++;
            	campo= strtok (NULL, "\t");
        	}
        	printf ("------------------------------------\n");
        	posicao= ftell (f);
        	fgets (linha, 2048, f);
        	n++;
        	if (n == 10)
        	{
            	break;
        	}
    	}
    }
	else
        printf ("\nNis nao encontrado"); 
    ArvoreB_Fecha (a);
    fclose (f);
    return 0;
}
