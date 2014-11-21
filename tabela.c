
# include "prototipo.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
void executar()
{    
    while( !((areacritica->timer >= areacritica->ioI) && (areacritica->timer <= areacritica->ioT)) && (areacritica->timer < areacritica->tempo))
    {
        printf("Executando ID: %d \n",areacritica->id );
        printf("Que chegou no Tempo: %d\n", areacritica->chegada);
        printf("Que já executou: %d\n",areacritica->timer);
        areacritica->timer += 1;    
    }

    if((areacritica->timer >= areacritica->ioI) && (areacritica->timer <= areacritica->ioT))
    {
        printf("Entrou em IO\n");
    }

    if( areacritica->timer >= areacritica->tempo )
        printf("finalizou sua execução toda\n");

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


void contarTempoES(proc *processos)
{
    for(;processos != NULL;processos = processos->prox)
    {
        if( (processos->timer >= processos->ioI) && (processos->timer <= processos->ioT))
        {
            processos->timer += 1;
        }
    }
}

/*

proc* CriarTabela(char argv[])
{
    proc *processos = NULL, *bufferProcesso = NULL, *ponta = NULL;
    char linha[MAX];


    FILE *fl_entrada = fopen(argv[2], "r" );

    if ( fl_entrada == 0 || fl_entrada == NULL) {
      fprintf(stderr, "Arquivo %s não encontrado\n", argv[1]);
      exit(1);
    }
    else 
    {
        while (fscanf(fl_entrada, "%s", linha) != EOF) 
        {
            printf("Linha do arquivo: %s\n", linha);
            bufferProcesso = LerEntrada(linha);
            if(processos == NULL)
            {
                processos = bufferProcesso;
                ponta = bufferProcesso;

            }
            else
            {
                ponta->prox = bufferProcesso;
                ponta = bufferProcesso;
            }
        }
        fclose( fl_entrada );
    }
    return processos;
}
*/