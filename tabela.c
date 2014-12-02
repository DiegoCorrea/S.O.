# include "prototipo.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>


void executar(proc *areacritica)
{    
    areacritica->timer += 1;
    printf("--CPU: Processo %d, de chegada %d , executou %d vezes\n",areacritica->id, areacritica->chegada, areacritica->timer );
}




proc* LerEntrada(char linha[MAX])
{
    proc *processo;
    int i = 0, j= 0;
    char buffer[8];

    processo = (proc*)malloc(sizeof(proc));
    processo->prox = NULL;
    processo->ant = NULL;
    processo->timer = 0;
    
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

proc* empilharES(proc *emEs, proc *processo)
{
    if(emEs != NULL)
    {
        emEs->ant = processo;
        processo->prox = emEs;
        processo->ant = NULL;
    }
    return processo;
}


void contarTempoES(proc *pilhaEs)
{
    for(;pilhaEs != NULL;pilhaEs = pilhaEs->prox)
    {
        pilhaEs->timer += 1;
        printf("-> I/O Processo %d, já executou %d\n", pilhaEs->id, pilhaEs->timer );        
    }
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

    return lista;
}

/*
void ES_verifica_saida(proc **pilhaDeES, proc **listaDePronto)
{
    proc *buffer;

    for(buffer = *pilhaDeES; buffer != NULL ; buffer = buffer->prox )
    {
        if(buffer->timer > buffer->ioT)
        {
            //pilhaDeES = removelista(pilhaDeES,buffer);
            listaDePronto = ;
        }
    }
}
*/


char concatenarSaida(proc *processo)
{
    return 'a';
}