# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>

# include "prototipo.h"


int main(int argc, char *argv[])
{
	long pid_algoritmo;
	proc *listaDePronto = NULL, *andante, *pilhaDeES = NULL;
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
				listaDePronto = FCFS(listaDePronto,LerEntrada(linha));	
			}

            
            if (strcmp("RR",argv[1])==0)
			{
				//Criar algoritmo de ordenação da entrada de acordo com o RR
				printf ("Você escolheu o RR\n");
				listaDePronto = RR(listaDePronto,LerEntrada(linha));
			}
			

			if (strcmp("SJF",argv[1])==0)
			{
				//Criar algoritmo de ordenação da entrada de acordo com o SJF
				printf ("Você escolheu o SJF\n");
				//listaDePronto = SJF(listaDePronto,LerEntrada(linha));
			}
        }
        fclose( fl_entrada );
    }

	printf("\nTabela de listaDePronto:\n");
    for(andante = listaDePronto;andante != NULL; andante = andante->prox)
    {
    	printf("Tempo de Chegada: %d ... id: %d\n",andante->chegada,andante->id);
    }
    //Neste ponto todos os listaDePronto foram carregados do arquivo e o primeiro processo está no ponteiro *listaDePronto;
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
				if (listaDePronto != NULL)
				{

					if(*semaforo == 0)
					{

						listaDePronto->timer = areacritica->timer;
						
						if ((listaDePronto->timer >= listaDePronto->tempo))
						{
							printf("ESCALONADOR: Processo %d será morto, por tempo de execução ter terminado\n",areacritica->id );
							//entrou se processo estiver morto
							if (listaDePronto->prox == NULL)
							{
								free(listaDePronto);
								listaDePronto = NULL;
							}
							else
							{
								listaDePronto = listaDePronto->prox;
								free(listaDePronto->ant);
								listaDePronto->ant = NULL;
							}
						}
						else
						{
							
							//entrou se processo vai para IO, processo colocado na pilha de IO
							if(listaDePronto->prox != NULL)
							{
								//caso a lista de pronto tenha varios listaDePronto
								//printf("ESCALONADOR: Varios listaDePronto na fila de pronto\n");
								andante = listaDePronto;
								listaDePronto = listaDePronto->prox;
								listaDePronto->ant = NULL;
								andante->prox = NULL;
								andante->ant = NULL;
								pilhaDeES = empilharES(pilhaDeES, andante);
								
							}
							else
							{
								//caso ele seja o unico processo da lista de pronto
								//printf("ESCALONADOR: Unico processo na fila de pronto\n");
								pilhaDeES = empilharES(pilhaDeES, listaDePronto);
								listaDePronto = NULL;
							}
							printf("ESCALONADOR: Processo %d entrara em IO\n",pilhaDeES->id );
							printf("ESCALONADOR: Processo ficará no IO de: %d até %d\n",pilhaDeES->ioI,pilhaDeES->ioT );
							
						}
					}
					else
					{
						if(*semaforo == -1)
							printf("ESCALONADOR: Entrando pela primeira vez\n");
					}

					if (listaDePronto != NULL)
					{
						//colocando o primeiro do processo na area critica
						areacritica->id = listaDePronto->id;
						areacritica->tempo = listaDePronto->tempo;
						areacritica->timer = listaDePronto->timer;
						areacritica->ioI = listaDePronto->ioI;
						areacritica->ioT = listaDePronto->ioT;
						areacritica->chegada = listaDePronto->chegada;
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
			if (*semaforo > -1)
			{
				//ES_verifica_saida(&pilhaDeES,&listaDePronto);

				for(andante = pilhaDeES; andante != NULL ; andante = andante->prox )
			    {
			        if(andante->timer > andante->ioT)
			        {
			            pilhaDeES = removelista(pilhaDeES,andante);

			            if(strcmp("FCFS",argv[1])==0)
						{
							printf ("Você escolheu o FCFS\n");
							listaDePronto = FCFS(listaDePronto,andante);	
						}

			            
			            if (strcmp("RR",argv[1])==0)
						{
							//Criar algoritmo de ordenação da entrada de acordo com o RR
							printf ("Você escolheu o RR\n");
							listaDePronto = RR(listaDePronto,andante);
						}
						

						if (strcmp("SJF",argv[1])==0)
						{
							//Criar algoritmo de ordenação da entrada de acordo com o SJF
							printf ("Você escolheu o SJF\n");
							//listaDePronto = SJF(listaDePronto,andante);
						}

			            
			        }
			    }

				/////////////////////////
				contarTempoES(pilhaDeES);
			}			
		}
	}
	else
	{
		//CPU
		while(1)
		{
			if ( *semaforo == 1 )
			{
			    printf("--CPU: Executando Processo de ID: %d \n",areacritica->id );
			    printf("--CPU:Que chegou no Tempo: %d\n", areacritica->chegada);
				while( (areacritica->timer < areacritica->tempo) && !((areacritica->timer >= areacritica->ioI) && (areacritica->timer <= areacritica->ioT)) )
				{
					executar(areacritica);
					sleep(SystemTime);
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
