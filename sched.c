# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# define MAX 50

# include "tabela.h"

# include "SJF.h"
# include "FCFS.h"
# include "RR.h"



int main(int argc, char *argv[])
{
    
	proc *processos = NULL, *bufferProcesso = NULL, *ponta = NULL;
    char linha[MAX];

	printf("O nome do arquivo de ENTRADA é: %s\n", argv[2]);
	printf("O nome do arquivo de SAIDA é: %s\n", argv[3]);

    FILE *fl_entrada = fopen(argv[2], "r" );

    if ( fl_entrada == 0 || fl_entrada == NULL) {
      fprintf(stderr, "Arquivo %s não encontrado\n", argv[1]);
      exit(1);
    }
    else 
    {
        while (fscanf(fl_entrada, "%s", linha) != EOF) 
        {
            printf("Linha do arquivo: %s\n", linha);
            bufferProcesso = LerEntrada(linha);
            if(processos == NULL)
            {
                processos = bufferProcesso;
                ponta = bufferProcesso;

            }
            else
            {
                ponta->prox = bufferProcesso;
                ponta = bufferProcesso;
            }
            printf("ID no Main: %d\n", bufferProcesso->id);

        }
        fclose( fl_entrada );
    }
	


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

	return EXIT_SUCCESS;
}
