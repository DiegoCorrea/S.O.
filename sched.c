#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#define MAX 50

int tabela[MAX][5];

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
	return EXIT_SUCCESS;
}

/*
void criando_tabela(char *argv)
{
    FILE *entrada = fopen(argv[2], "r" );

    if ( entrada == NULL) {
	  fprintf(stderr, "Arquivo %s não encontrado\n", argv[1]);
	  exit(1);
	}
    else 
    {
		while (fscanf(entrada, "%s", linha) != EOF) 
		{
		  printf("%s\n", linha);
		}
        fclose( file );
    }
    
}
*/