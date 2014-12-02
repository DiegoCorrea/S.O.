#include "prototipo.h"

proc* RR(proc *processos, proc *novoProcesso)
{
	int quantum = 1;
	proc *processosAux = NULL, *processoAnterior = NULL;
   
	int inicioDaLista = 1;
   
	printf("\tEscalonamento Round-Robin - Quantum: %d)\n", quantum);
   
	processosAux = processos;
	processoAnterior = processosAux;

	if (processos == NULL){
		processos = novoProcesso;
	}else{
		while ((processosAux != NULL) && (novoProcesso->timer < quantum ) && (novoProcesso->tempo > processosAux->tempo)) {
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
