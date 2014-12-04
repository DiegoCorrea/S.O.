# include "prototipo.h"


void executar(proc *areacritica)
{    
    areacritica->timer += 1;
    printf("--CPU: Processo %d, de chegada %d , executou %d vezes\n",areacritica->id, areacritica->chegada, areacritica->timer );
}

int CPU(proc *areacritica, int *semaforo)
{
	while(1)
	{
		if ( *semaforo == 1 )
		{
			while( (areacritica->timer < areacritica->tempo) && !((areacritica->timer >= areacritica->ioI) && (areacritica->timer <= areacritica->ioT)) )
			{
				executar(areacritica);
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