# include "prototipo.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>


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

void copiar(proc *areacritica, proc *listaDePronto)
{
    areacritica->id = listaDePronto->id;
    areacritica->tempo = listaDePronto->tempo;
    areacritica->timer = listaDePronto->timer;
    areacritica->ioI = listaDePronto->ioI;
    areacritica->ioT = listaDePronto->ioT;
    areacritica->chegada = listaDePronto->chegada;
}