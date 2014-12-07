# include "prototipo.h"

proc* ESempilhar(proc *emEs, proc *processo)
{
    if(emEs != NULL)
    {
        emEs->ant = processo;
        processo->prox = emEs;
        processo->ant = NULL;
    }
    return processo;
}


void EScontarTempo(proc *pilhaEs)
{
    for(;pilhaEs != NULL;pilhaEs = pilhaEs->prox)
    {
        pilhaEs->timer += 1;
        printf("-> I/O Processo %d, já executou %d\n", pilhaEs->id, pilhaEs->timer );        
    }
}