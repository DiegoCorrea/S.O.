# include "prototipo.h"


void semaforoUp(int *semaforo)
{
    *semaforo = 1;
}

void semaforoDown(int *semaforo)
{
    *semaforo = 0;
}

void semaforoStart(int *semaforo)
{
    *semaforo = -1;
}

void semaforoClose(int *semaforo)
{
    *semaforo = -2;
}