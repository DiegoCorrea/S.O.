# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>

# include "prototipo.h"


int main(int argc, char *argv[])
{
	long pid_algoritmo;
	permitido = 0;
    
	proc *processos = NULL, *andante;
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
        	
            printf("\n\n\nLinha do arquivo: %s\n", linha);

            if(strcmp("FCFS",argv[1])==0)
			{
				printf ("Você escolheu o FCFS\n");
				processos = FCFS(processos,LerEntrada(linha));	
			}

            
            if (strcmp("RR",argv[1])==0)
			{
				printf ("Você escolheu o RR\n");
				processos = RR(processos,LerEntrada(linha));
			}
			

			if (strcmp("SJF",argv[1])==0)
			{
				printf ("Você escolheu o SJF\n");
				processos = SJF(processos,LerEntrada(linha));
			}


			printf("Tabela de Processos:\n");
            for(andante = processos;andante != NULL; andante = andante->prox)
            {
            	printf("Tempo de Chegada: %d ... id: %d\n",andante->chegada,andante->id);
            }
        }
        fclose( fl_entrada );
    }
	
	pid_algoritmo = fork();


	if(pid_algoritmo == 0)
	{
		printf("processo filho\n");
	}
	else
	{
		//escalonador
	}

	if(pid_algoritmo == 0)
		printf("finalizei o filho\n");

	return EXIT_SUCCESS;
}
