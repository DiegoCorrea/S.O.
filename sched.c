#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#define MAX 50

typedef struct processos
{
   int  id;			//ID do processo
   int  chegada;	//Instante de chegada
   int  tempo;		//Tempo de processamento
   int  oiI;		//Instante que inicia o IO
   int  oiT;		//Instante que termina o IO
   struct   processos *ant;
   struct   processos *prox;
};


int main(int argc, char *argv[])
{
	char linha[20];
	int l,c, j, a, b;

	printf("O nome do arquivo de ENTRADA é: %s\n", argv[2]);
	printf("O nome do arquivo de SAIDA é: %s\n", argv[3]);

	if(strcmp("FCFS",argv[1])==0)
	{
		printf ("Você escolheu o FCFS\n");
	}	
		else if (strcmp("RR",argv[1])==0)
		{
			printf ("Você escolheu o RR\n");
		}
			else if (strcmp("SJF",argv[1])==0)
		{
				printf ("Você escolheu o SJF\n");
		}
			else
				printf ("Você não escolheu nenhuma opção válida! Finalizando processo\n");


	//retirando itens do arquivo
    FILE *fl_entrada = fopen(argv[2], "r" );

    if ( fl_entrada == 0 || entrada == NULL) {
	  fprintf(stderr, "Arquivo %s não encontrado\n", argv[1]);
	  exit(1);
	}
    else 
    {
    	l=0;
		while (fscanf(fl_entrada, "%s", linha) != EOF) 
		{
			j = 0;
			c = 0;
			printf("Linha do arquivo: %s\n", linha);
			processo->id = linha[0];
			processo->chegada = linha[2];
			processo->tempo = linha[4];

			if(linha[6] == ";")
			{
				processo->ioI = 0;
				processo->ioT = 0;
			}
			else
			{
				processo->ioI = linha[6];
				processo->ioT = linha[8];
			}

			while(linha[j] != '\n')
			{
				if (linha[j] != ';')
				{
					tabela[l][c] = atoi(&linha[j]);
					c++;
				}
				if (j > 0 && linha[j] == ';' && linha[j-1] == ';')
				{
					tabela[l][c] = 0;
					c++;
				}
				j++;
			}			
			l++;
		}
			a =0;
			b =0;
			while(a < l)
			{
				b = 0;
				while(b < 5)
				{
				printf("%d \n", tabela[a][4]);				
				b++;
				}
				a++;
			}
        fclose( fl_entrada );
    }
	return EXIT_SUCCESS;
}

/*
void criando_tabela(char *argv)
{
     FILE *entrada = fopen(argv[2], "r" );

    if ( entrada == 0 || entrada == NULL) {
	  fprintf(stderr, "Arquivo %s não encontrado\n", argv[1]);
	  exit(1);
	}
    else 
    {
    	l=0;
		while (fscanf(entrada, "%s", linha) != EOF) 
		{
			j = 0;
			c = 0;
			printf("Linha do arquivo: %s\n", linha);

			while(linha[j] != '\n')
			{
				if (linha[j] != ';')
				{
					tabela[l][c] = atoi(&linha[j]);
					c++;
				}
				if (j > 0 && linha[j] == ';' && linha[j-1] == ';')
				{
					tabela[l][c] = 0;
					c++;
				}
				j++;
			}			
			l++;
		}
			a =0;
			b =0;
			while(a < l)
			{
				b = 0;
				while(b < 5)
				{
				printf("%d \n", tabela[a][4]);				
				b++;
				}
				a++;
			}
        fclose( entrada );
    }
    
}
*/