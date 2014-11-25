# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>

# include "prototipo.h"


int main(int argc, char *argv[])
{
	long pid_algoritmo;
	proc *processos = NULL, *andante, *emEs = NULL;
    char linha[MAX];

	//memoria compartilhada
	int shmid, shmid2;
	key_t key, key2;

	proc *areacritica;
	int *semaforo;

	key = 1420450;
	key2 = 123456;
    

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


    //area compartilhada do tamnho do proc
    areacritica = (proc *) malloc(sizeof(proc));
	if ((shmid = shmget(key, sizeof(proc), IPC_CREAT | 0666)) < 0) {
		perror("shmget");
		exit(1);
	}

	if ((areacritica = shmat(shmid, NULL, 0)) == (proc *) -1) {
		perror("shmat");
		exit(1);
	}

	//semaforo para permitir a execução
	semaforo = (int *) malloc(sizeof(int));
	if ((shmid2 = shmget(key2, 1, IPC_CREAT | 0666)) < 0) {
		perror("shmget");
		exit(1);
	}

	if ((semaforo = shmat(shmid2, NULL, 0)) == (int *) -1) {
		perror("shmat");
		exit(1);
	}




	andante = NULL;
	*semaforo = -1;
	pid_algoritmo = fork();
	





	if(pid_algoritmo != 0)
	{
		//Escalonador
		while(1)
		{
			if( *semaforo == 0 || *semaforo == -1 )
			{
				if (processos != NULL)
				{

					if(*semaforo == 0)
					{

						processos->timer = areacritica->timer;
						
						if ((processos->timer >= processos->tempo))
						{
							printf("ESCALONADOR: Processo %d será morto, por tempo de execução ter terminado\n",areacritica->id );
							//entrou se processo estiver morto
							if (processos->prox == NULL)
							{
								free(processos);
								processos = NULL;
							}
							else
							{
								processos = processos->prox;
								free(processos->ant);
								processos->ant = NULL;
							}
						}
						else
						{
							
							//entrou se processo vai para IO, processo colocado na pilha de IO
							if(processos->prox != NULL)
							{
								//caso a lista de pronto tenha varios processos
								printf("ESCALONADOR: Varios processos na fila de pronto\n");
								andante = processos;
								processos = processos->prox;
								processos->ant = NULL;
								andante->prox = NULL;
								andante->ant = NULL;
								emEs = empilharES(emEs, andante);
								
							}
							else
							{
								//caso ele seja o unico processo da lista de pronto
								printf("ESCALONADOR: Unico processo na fila de pronto\n");
								emEs = empilharES(emEs, processos);
								processos = NULL;
							}
							printf("ESCALONADOR: Processo %d entrara em IO\n",emEs->id );
							printf("ESCALONADOR: Processo ficará no IO de: %d até %d\n",emEs->ioI,emEs->ioT );
							
						}
					}
					else
					{
						if(*semaforo == -1)
							printf("ESCALONADOR: Entrando pela primeira vez\n");
					}

					if (processos != NULL)
					{
						//colocando o primeiro do processo na area critica
						areacritica->id = processos->id;
						areacritica->tempo = processos->tempo;
						areacritica->timer = processos->timer;
						areacritica->ioI = processos->ioI;
						areacritica->ioT = processos->ioT;
						areacritica->chegada = processos->chegada;
						*semaforo = 1;
						printf("\nESCALONADOR: Processo %d escolhido para ir a CPU\n",areacritica->id );
					}

				}
				else
				{
					printf("ESCALONADOR: Nenhum processo disponivel para execucao\n");
				}
			}
			sleep(SystemTime);
			//após dormir, incrementando o tempo de todos que estão em IO
			
			
			//contarTempoES(emEs);
			/*
			andante = emEs;
			while(andante == NULL)
			{
				//trazendo o processo que estou o tempo de IO
				andante = verificandotempoEs(emEs);
				
				emEs = removelista(emEs,andante);

				//adicionando o processo na lista de processo pronto
				processos = FCFS(processos, andante);


			}
			*/
		}
	}
	else
	{
		//CPU
		while(1)
		{
			if ( *semaforo == 1 )
			{
			    printf("Executando Processo de ID: %d \n",areacritica->id );
			    printf("Que chegou no Tempo: %d\n", areacritica->chegada);
				while( (areacritica->timer < areacritica->tempo) && !((areacritica->timer >= areacritica->ioI) && (areacritica->timer <= areacritica->ioT)) )
				{
					executar(areacritica);
				}
				*semaforo = 0; 
				printf("--CPU: Semaforo desligado\n");
			}
			else
			{
				printf("--CPU idle...\n");
				sleep(SystemTime);
			}
			
		}
	}

	return EXIT_SUCCESS;
}
