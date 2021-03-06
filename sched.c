# include "prototipo.h"


int main(int argc, char *argv[])
{
	long pid_algoritmo;
	int tempoTotal, nprocessos = 0;

	proc *listaDePronto = NULL, *andante = NULL;

	//memoria compartilhada
	int shmid, shmid2;
	key_t key = 1420450, key2 = 123456;

	proc *areacritica;
	int *semaforo;

	listaDePronto = arquivoLer(argv[2],argv[1], &nprocessos);
	andante = listaDePronto;
    //Neste ponto todos os listaDePronto foram carregados do arquivo e o primeiro processo está no ponteiro *listaDePronto;
    //Que uma lista duplamente encadiada
		
	printf("\nTabela de Processos:\n");
    for(andante = listaDePronto;andante != NULL; andante = andante->prox)
    {
    	printf("Tempo de Chegada: %d ... id: %d\n",andante->chegada,andante->id);
    }

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
	semaforoStart(semaforo);
	tempoTotal = 0;
	pid_algoritmo = fork();
	

	if(pid_algoritmo != 0)
	{
		//Escalonador
		if(strcmp("FCFS",argv[1])==0)
		{
			*semaforo = ESCALONADOR_FCFS(listaDePronto, areacritica, semaforo, argv, &tempoTotal);
		}

        
      if (strcmp("RR",argv[1])==0)
		{
			*semaforo = ESCALONADOR_RR(listaDePronto, areacritica, semaforo, argv, &tempoTotal);
		}
		

		if (strcmp("SJF",argv[1])==0)
		{
			*semaforo = ESCALONADOR_SJF(listaDePronto, areacritica, semaforo, argv, &tempoTotal);
		}	
		
		arquivoGravarSaida(argv[3],tempoTotal,nprocessos);
	}
	else
	{	
		if(strcmp("FCFS",argv[1])==0)
		{
			CPU_FCFS(areacritica,semaforo);
		}
        
      	if (strcmp("RR",argv[1])==0)
		{
			CPU_RR(areacritica,semaforo);
		}
		
		if (strcmp("SJF",argv[1])==0)
		{
			CPU_SJF(areacritica,semaforo);
		}
	}	

	return EXIT_SUCCESS;
}
