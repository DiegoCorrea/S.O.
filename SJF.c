#include<stdio.h>
#include <stdlib.h>
#include "prototipo.h"
#include <unistd.h>
#include <string.h>


proc* SJF(proc *processos, proc *novoProcesso)
{
	 int inicioDaLista = 1;

    proc *processosAux = NULL, *processoAnterior = NULL;

     if(processos == NULL){
		processos = novoProcesso;
     }else{
            processosAux = processos;

            while((processosAux != NULL) && (novoProcesso->tempo > processosAux->tempo)){
                processoAnterior = processosAux;
                processosAux = processosAux->prox;
                inicioDaLista = 0;
            }

            if (processosAux == NULL){
                processoAnterior->prox = novoProcesso;
                novoProcesso->ant = processoAnterior;
            }else{
                if (inicioDaLista == 1){
                    novoProcesso->prox = processosAux;
                    processosAux->ant = novoProcesso;
                    processosAux = novoProcesso;
                }else{
                    processoAnterior->prox = novoProcesso;
                    processosAux->ant = novoProcesso;
                    novoProcesso->prox = processosAux;
                    novoProcesso->ant = processoAnterior;
                }
            }
			}

	return processos;
}	
