# include "prototipo.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>



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

proc* arquivoLer(char arquivo[], char algoritmo[], int *nprocessos)
{
    proc *listaDePronto = NULL;
    char linha[MAX];

    FILE *fl_entrada = fopen(arquivo, "r" );

    if ( fl_entrada == 0 || fl_entrada == NULL) {
      fprintf(stderr, "Arquivo %s não encontrado\n", arquivo);
      exit(1);
    }
    else 
    {
        while (fscanf(fl_entrada, "%s", linha) != EOF) 
        {
            
            if(strcmp("FCFS",algoritmo)==0)
            {
                listaDePronto = FCFS(listaDePronto,LerEntrada(linha));  
            }

            
            if (strcmp("RR",algoritmo)==0)
            {
                //Criar algoritmo de ordenação da entrada de acordo com o RR
                listaDePronto = RR(listaDePronto,LerEntrada(linha));
            }
            

            if (strcmp("SJF",algoritmo)==0)
            {
                //Criar algoritmo de ordenação da entrada de acordo com o SJF
                //listaDePronto = SJF(listaDePronto,LerEntrada(linha));
            }
            *nprocessos +=1;
        }
        fclose( fl_entrada );
    }
    return listaDePronto;
}

void arquivoGravar(proc *processoNaCPU, char arquivo[], int tempoTotal)
{
    FILE *fl_entrada = fopen(arquivo, "a" );

    if ( fl_entrada == 0 || fl_entrada == NULL) {
      fprintf(stderr, "Arquivo %s não pode ser escrito\n", arquivo);
      exit(1);
    }
    //linha = concatenarSaida(processoNaCPU);
    fprintf(fl_entrada,"%d;%d;%d\n", processoNaCPU->id,processoNaCPU->chegada,tempoTotal);

    fclose( fl_entrada );
}

void arquivoGravarSaida(char arquivo[], int tempoTotal, int nprocessos)
{
    float tempoMedio;
    
    FILE *fl_entrada = fopen(arquivo, "a" );

    if ( fl_entrada == 0 || fl_entrada == NULL) {
      fprintf(stderr, "Arquivo %s não pode ser escrito\n", arquivo);
      exit(1);
    }
    fprintf(fl_entrada,"Tempo total: %d\n", tempoTotal);
    tempoMedio = tempoTotal/nprocessos;
    fprintf(fl_entrada,"Tempo médio: %f\n", tempoMedio);

    fclose( fl_entrada );
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