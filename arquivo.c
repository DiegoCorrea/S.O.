# include "prototipo.h"

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
                listaDePronto = SJF(listaDePronto,LerEntrada(linha));
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
    tempoMedio = (float)tempoTotal/nprocessos;
    fprintf(fl_entrada,"Tempo médio: %f\n", tempoMedio);

    fclose( fl_entrada );
}

