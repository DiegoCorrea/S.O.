# include "prototipo.h"


void CPUexecutar(proc *areacritica)
{    
    areacritica->timer += 1;
    printf("--CPU: Processo %d, de chegada %d , executou %d vezes\n",areacritica->id, areacritica->chegada, areacritica->timer );
}

int CPU_FCFS(proc *areacritica, int *semaforo)
{
	while(1)
	{
		if ( *semaforo == 1 )
		{
			while( (areacritica->timer < areacritica->tempo) && !((areacritica->timer >= areacritica->ioI) && (areacritica->timer <= areacritica->ioT)) )
			{
				CPUexecutar(areacritica);
				sleep(SystemTime);
			}
			semaforoDown(semaforo);
			printf("--CPU: Semaforo desligado\n");
		}
		else
		{
			printf("--CPU idle...\n");
			sleep(SystemTime);
		}
		if(*semaforo == -2)
			return EXIT_SUCCESS;
		
	}
}

int CPU_RR(proc *areacritica, int *semaforo)
{
	while(1)
	{
		if ( *semaforo == 1 )
		{
			CPUexecutar(areacritica);
			sleep(SystemTime);
			semaforoDown(semaforo);
			printf("--CPU: Semaforo desligado\n");
		}
		else
		{
			printf("--CPU idle...\n");
			sleep(SystemTime);
		}
		if(*semaforo == -2)
			return EXIT_SUCCESS;
		
	}
}