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
	areacritica = NULL;
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
        	
            printf("\nLinha do arquivo: %s\n", linha);

            if(strcmp("FCFS",argv[1])==0)
			{
				printf ("Você escolheu o FCFS\n");
				processos = FCFS(processos,LerEntrada(linha));	
			}

            
            if (strcmp("RR",argv[1])==0)
			{
				//Criar algoritmo de ordenação da entrada de acordo com o RR
				printf ("Você escolheu o RR\n");
				processos = RR(processos,LerEntrada(linha));
			}
			

			if (strcmp("SJF",argv[1])==0)
			{
				//Criar algoritmo de ordenação da entrada de acordo com o SJF
				printf ("Você escolheu o SJF\n");
				processos = SJF(processos,LerEntrada(linha));
			}
        }
        fclose( fl_entrada );
    }

	printf("\nTabela de Processos:\n");
    for(andante = processos;andante != NULL; andante = andante->prox)
    {
    	printf("Tempo de Chegada: %d ... id: %d\n",andante->chegada,andante->id);
    }
    //Neste ponto todos os processos foram carregados do arquivo e o primeiro processo está no ponteiro *processos;
    //Que uma lista duplamente encadiada

	
	pid_algoritmo = fork();


	if(pid_algoritmo == 0)
	{

		printf("processo filho\n");
		while(1)
		{
			contarTempoES(processos);
			printf("indo para a area critica\n");
			printf("indo executar processo de ID: %d\n", areacritica->id);
			if ( areacritica != NULL )
			{
				printf("em area critica\n");
				executar();
				areacritica = NULL;
			}
			sleep(1);
		}
	}
	else
	{
		while(1)
		{
			if(areacritica == NULL)
			{
				printf("criando area critica\n primeiro processo %d\n", processos->id );
				for (andante = processos; (andante != NULL) && !((andante->timer >= andante->ioI) && (andante->timer <= andante->ioT)) ; andante = andante->prox)
					printf("%d\n", andante->id );
				
				if (andante == NULL)
				{
					printf("Nenhum processo disponivel para execução\n");
				}
				else
				{
					areacritica = andante;
					printf("inserindo na area critica processo de ID: %d\n", areacritica->id);
				}
			}
			sleep(1);
		}
	}


	return EXIT_SUCCESS;
}
