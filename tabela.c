
# include "prototipo.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>

void executar()
{
    for(;;)
    {
        printf("Processo executando é: %d \n", permitido);
    }

}



proc* LerEntrada(char linha[MAX])
{
    proc *processo;
    int i = 0, j= 0;
    char buffer[8];

    processo = (proc*)malloc(sizeof(proc));
    processo->prox = NULL;
    processo->timer = 0;
    
    while(linha[i] != ';')
    {
        buffer[j] = linha[i];
        i++;
        j++;
    }
    buffer[j] = '\0';
    processo->id = atoi(buffer);
    printf("%d\n", processo->id);
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
    printf("%d\n",processo->chegada);
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
    printf("%d\n",processo->tempo);
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
        printf("%d\n",processo->ioI);
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
        printf("%d\n",processo->ioT);
    }
    else
    {
        processo->ioI = 0;
        processo->ioT = 0;
        printf("%d\n",processo->ioT);
        printf("%d\n",processo->ioI);

    }

    return processo;
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