#include "prototipo.h"

int ESCALONADOR_SJF(proc *listaDePronto, proc *areacritica, int *semaforo, char *argv[], int *tempoTotal){

	proc *pilhaDeES = NULL, *andante = NULL, *buffer = NULL, *processoNaCPU = NULL;

	while(1)
	{
		printf("\nESCALONADOR: tempo total é: %d\n", *tempoTotal);
		if( *semaforo == 0 || *semaforo == -1 )
		{
			if(*semaforo == 0 && processoNaCPU != NULL)
			{
				processoNaCPU->timer = areacritica->timer;

				if (processoNaCPU->timer >= processoNaCPU->tempo)
				{
					arquivoGravar(processoNaCPU,argv[3],*tempoTotal);					

					printf("ESCALONADOR: Processo %d será morto, por tempo de execução ter terminado\n",processoNaCPU->id );
					free(processoNaCPU);
					processoNaCPU = NULL;							
				}
				else
				{
					pilhaDeES = ESempilhar(pilhaDeES, processoNaCPU);							
					printf("ESCALONADOR: Processo %d empilhado, ficará no IO de: %d até %d\n",processoNaCPU->id, processoNaCPU->ioI,processoNaCPU->ioT );							
				}
			}

			if (listaDePronto != NULL) 
			{

				for(andante = listaDePronto->prox, buffer = listaDePronto; andante!= NULL && *tempoTotal >= andante->chegada ; andante = andante->prox)
				{
					if (andante != NULL && andante->tempo < buffer->tempo)
						buffer = andante;
				}

				if (buffer->chegada <= *tempoTotal)
				{
					//colocando o primeiro do processo na area critica
					listaDePronto = removelista(listaDePronto, buffer);
					processoNaCPU = buffer;
					copiar(areacritica, buffer);				

					*semaforo = 1;
					printf("\nESCALONADOR: Processo %d escolhido para ir a CPU\n",areacritica->id );
				}
				
			}
			else
			{
				printf("ESCALONADOR: Nenhum processo disponivel para execucao\n");
			}
		}
		
		if (*semaforo > -1)
		{
			EScontarTempo(pilhaDeES);
			andante = pilhaDeES;
			while(andante != NULL)
		    {

		        if(andante->timer > andante->ioT)
		        {
		        	buffer = andante;
		        	andante = andante->prox;
		            pilhaDeES = removelista(pilhaDeES,buffer);
					
					listaDePronto = SJF_execucao(listaDePronto,buffer);
					printf("ESCALONADOR: Processo %d saindo do I/O, I/O Final %d, Vida %d\n",buffer->id, buffer->ioT,buffer->timer );	

		        }
		        else
		        	andante = andante->prox;
		    }
			
		}
		tempoContar(tempoTotal);
		sleep(SystemTime);
		if (listaDePronto == NULL && pilhaDeES == NULL && processoNaCPU == NULL)
		{
		    return -2;
		}			
	}
}

int ESCALONADOR_FCFS(proc *listaDePronto, proc *areacritica, int *semaforo, char *argv[], int *tempoTotal)

{
	proc *pilhaDeES = NULL, *andante = NULL, *buffer = NULL, *processoNaCPU = NULL;

	while(1)
	{
		printf("\nESCALONADOR: tempo total é: %d\n", *tempoTotal);
		if( *semaforo == 0 || *semaforo == -1 )
		{
			if(*semaforo == 0 && processoNaCPU != NULL)
			{
				processoNaCPU->timer = areacritica->timer;

				if (processoNaCPU->timer >= processoNaCPU->tempo)
				{
					arquivoGravar(processoNaCPU,argv[3],*tempoTotal);					

					printf("ESCALONADOR: Processo %d será morto, por tempo de execução ter terminado\n",processoNaCPU->id );
					free(processoNaCPU);
					processoNaCPU = NULL;							
				}
				else
				{
					pilhaDeES = ESempilhar(pilhaDeES, processoNaCPU);							
					printf("ESCALONADOR: Processo %d empilhado, ficará no IO de: %d até %d\n",processoNaCPU->id, processoNaCPU->ioI,processoNaCPU->ioT );							
				}
			}

			if ((listaDePronto != NULL) && (*tempoTotal >= listaDePronto->chegada))
			{
				//colocando o primeiro do processo na area critica
				copiar(areacritica,listaDePronto);
				
				processoNaCPU = listaDePronto;
				listaDePronto = listaDePronto->prox;
				processoNaCPU->prox = NULL;
				processoNaCPU->ant = NULL;

				*semaforo = 1;
				printf("\nESCALONADOR: Processo %d escolhido para ir a CPU\n",areacritica->id );
			}
			else
			{
				printf("ESCALONADOR: Nenhum processo disponivel para execucao\n");
			}
		}
		
		if (*semaforo > -1)
		{
			EScontarTempo(pilhaDeES);
			andante = pilhaDeES;
			while(andante != NULL)
		    {

		        if(andante->timer > andante->ioT)
		        {
		        	buffer = andante;
		        	andante = andante->prox;
		            pilhaDeES = removelista(pilhaDeES,buffer);
					
					listaDePronto = FCFS_execucao(listaDePronto,buffer);
					printf("ESCALONADOR: Processo %d saindo do I/O, I/O Final %d, Vida %d\n",buffer->id, buffer->ioT,buffer->timer );	

		        }
		        else
		        	andante = andante->prox;
		    }
			
		}
		tempoContar(tempoTotal);
		sleep(SystemTime);
		if (listaDePronto == NULL && pilhaDeES == NULL && processoNaCPU == NULL)
		{
		    return -2;
		}			
	}
}



int ESCALONADOR_RR(proc *listaDePronto, proc *areacritica, int *semaforo, char *argv[], int *tempoTotal)

{
	proc *pilhaDeES = NULL, *andante = NULL, *buffer = NULL, *processoNaCPU = NULL, *proximoProcesso;

	while(1)
	{
		printf("\nESCALONADOR: tempo total é: %d\n", *tempoTotal);

		if( *semaforo == 0 || *semaforo == -1 )
		{
			if(*semaforo == 0 && processoNaCPU != NULL)
			{
				processoNaCPU->timer = areacritica->timer;
				
				if (processoNaCPU->timer >= processoNaCPU->tempo)
				{
					arquivoGravar(processoNaCPU,argv[3],*tempoTotal);

					printf("ESCALONADOR: Processo %d será morto, por tempo de execução ter terminado\n",processoNaCPU->id );
					free(processoNaCPU);
					processoNaCPU = NULL;							
				}
				else 
				{
					if((processoNaCPU->timer >= processoNaCPU->ioI) && (processoNaCPU->timer <= processoNaCPU->ioT))
					{
						pilhaDeES = ESempilhar(pilhaDeES, processoNaCPU);							
						printf("ESCALONADOR: Processo %d empilhado, ficará no IO de: %d até %d\n",processoNaCPU->id, processoNaCPU->ioI,processoNaCPU->ioT );							
					}
					else
					{
						listaDePronto = FCFS_execucao(listaDePronto,processoNaCPU);
					} 
				}
				

				processoNaCPU = proximoProcesso;
				if (processoNaCPU != NULL)
				{
					proximoProcesso = proximoProcesso->prox;
					listaDePronto = removelista(listaDePronto,processoNaCPU);
				}
				
				
			}
			if (*semaforo == -1)
			{
				processoNaCPU = listaDePronto;
				proximoProcesso = listaDePronto->prox;
				listaDePronto = removelista(listaDePronto,processoNaCPU);
			}
				

			if ((processoNaCPU != NULL) && (*tempoTotal >= processoNaCPU->chegada))
			{
				//colocando o primeiro do processo na area critica
				copiar(areacritica,processoNaCPU);

				*semaforo = 1;
				printf("\nESCALONADOR: Processo %d escolhido para ir a CPU\n",areacritica->id );
			}
			else
			{
				printf("ESCALONADOR: Voltando ao inicio da lista\n");
				*semaforo = -1;
			}
		}
		
		if (*semaforo > -1)
		{
			EScontarTempo(pilhaDeES);
			andante = pilhaDeES;
			while(andante != NULL)
		    {
		        if(andante->timer > andante->ioT)
		        {
		        	buffer = andante;
		        	andante = andante->prox;
		            pilhaDeES = removelista(pilhaDeES,buffer);

					listaDePronto = RR_execucao(listaDePronto,buffer);
					printf("ESCALONADOR: Processo %d saindo do I/O, I/O Final %d, Vida %d\n",buffer->id, buffer->ioT,buffer->timer );	
		        }
		        else
		        	andante = andante->prox;
		    }
		}

		tempoContar(tempoTotal);

		sleep(SystemTime);

		if (listaDePronto == NULL && pilhaDeES == NULL && processoNaCPU == NULL)
		{
		    return -2;
		}			
	}
}
