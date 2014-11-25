# include "prototipo.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>


void executar(proc *areacritica)
{    
    areacritica->timer += 1;
    printf("Que ja executou: %d\n",areacritica->timer);
    sleep(SystemTime);
}




proc* LerEntrada(char linha[MAX])
{
    proc *processo;
    int i = 0, j= 0;
    char buffer[8];

    processo = (proc*)malloc(sizeof(proc));
    processo->prox = NULL;
    processo->ant = NULL;
    processo->timer = 1;
    
    while(linha[i] != ';')
    {
        buffer[j] = linha[i];
        i++;
        j++;
    }
    buffer[j] = '\0';
    processo->id = atoi(buffer);
    j = 0;
    i++;
    while(linha[i] != ';')
    {
        buffer[j] = linha[i];
        i++;
        j++;
    }
    buffer[j] = '\0';
    processo->chegada = atoi(buffer);
    j = 0;
    i++;
    while(linha[i] != ';')
    {
        buffer[j] = linha[i];
        i++;
        j++;
    }
    buffer[j] = '\0';
    processo->tempo = atoi(buffer);
    j = 0;
    i++;
    
    if( linha[i] != ';' )
    {   
        while(linha[i] != ',')
        {
            buffer[j] = linha[i];
            i++;
            j++;
        }
        buffer[j] = '\0';
        processo->ioI = atoi(buffer);
        j = 0;
        i++;
        while(linha[i] != ';')
        {
            buffer[j] = linha[i];
            i++;
            j++;
        }
        buffer[j] = '\0';
        processo->ioT = atoi(buffer);
    }
    else
    {
        processo->ioI = -1;
        processo->ioT = -1;
    }

    return processo;
}

proc* colocaremES(proc *emEs, proc *processo)
{
    if(emEs == NULL)
    {
        emEs = processo;
    }
    else
    {
        emEs->ant = processo;
        processo->prox = emEs;
        processo->ant = NULL;
        emEs = processo;
    }
    return emEs;
}


void contarTempoES(proc *processos)
{
    for(;processos != NULL;processos = processos->prox)
    {
        printf("Processo usando IO: %d\n", processos->id );
        processos->timer += 1;
    }
}

proc* verificandotempoEs(proc *emEs)
{

    for(; (emEs!=NULL) && (emEs->timer < emEs->ioT) ; emEs = emEs->prox);

    return emEs;
}


proc* removelista(proc *lista, proc *pararemover)
{

    if(lista == pararemover && lista->prox == NULL)
    {
        lista = NULL;
    }
    else
    {
        if (lista == pararemover)
        {
            lista = lista->prox;
            lista->ant = NULL;
        }
        else
        {
            if (pararemover->prox == NULL)
            {
                pararemover->ant->prox = NULL;
            }
            else
            {
                pararemover->ant->prox = pararemover->prox;
                pararemover->prox->ant = pararemover->ant;
            }
            
        }
    }

    free(pararemover);

    return lista;
}