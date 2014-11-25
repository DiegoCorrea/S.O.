#include "prototipo.h"
proc* SJF(proc *processos, proc *novoProcesso)
{

    proc *processosAux = NULL, *processoAnterior = NULL;
    proc *processosOrdenadosChegada = null;
    bool inicioDaLista = true;

     if(processos == NULL){
		processos = novoProcesso;
     }else{
            processosAux = processos;

            while((processosAux != null) && (novoProcesso->tempo > processosAux->tempo)){
                processoAnterior = processosAux;
                processosAux = processosAux->prox;
                inicioDaLista = false;
            }

            if (processosAux == null){
                processoAnterior->prox = novoProcesso;
                novoProcesso->ant = processoAnterior;
            }else{
                if (inicioDaLista){
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

	return processos;
}
