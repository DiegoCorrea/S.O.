#include "prototipo.h"

void insereNoFim(proc *processoAnterior, proc *novoProcesso){

	processoAnterior->prox = novoProcesso;
	novoProcesso->ant = processoAnterior;
}

void insereNoInicio(proc *processosAux, proc *novoProcesso, proc *processos){

 	novoProcesso->prox = processosAux;
	processosAux->ant = novoProcesso;
  	processos = novoProcesso;
}

void insereNoMeio(proc *processoAnterior, proc *novoProcesso, proc *processosAux){

	processoAnterior->prox = novoProcesso;
  	processosAux->ant = novoProcesso;
  	novoProcesso->prox = processosAux;
  	novoProcesso->ant = processoAnterior;
}
	
void caminha(proc *processoAnterior, proc *processosAux){

	processoAnterior = processosAux;
 	processosAux = processosAux->prox;
}

proc* SJF(proc *processos, proc *novoProcesso)
{
    proc *processosAux = NULL, *processoAnterior = NULL;     
	if(processos == NULL){
		processos = novoProcesso;
     }else{
            processosAux = processos;

            while((processosAux != NULL) && (novoProcesso->chegada > processosAux->chegada)){
                processoAnterior = processosAux;
 					 processosAux = processosAux->prox;      
            }

            if (processosAux == NULL){
                processoAnterior->prox = novoProcesso;
					 novoProcesso->ant = processoAnterior;
            }else{
		             if (processosAux == processos){
							novoProcesso->prox = processosAux;
							processosAux->ant = novoProcesso;
						  	processos = novoProcesso;			
						 }else{
                   			processoAnterior->prox = novoProcesso;
								  	processosAux->ant = novoProcesso;
								  	novoProcesso->prox = processosAux;
								  	novoProcesso->ant = processoAnterior;;
                			}
            	  }
			}

		/*
		processoAnterior = processos;
		processosAux = processos->prox;
	   proc *cabecaLista = processos;
		proc *aux = (proc *) malloc(sizeof(proc));;		

		while((processosAux != NULL)){
			while (processoAnterior->chegada == processosAux->chegada){					
					if (processoAnterior->tempo > processosAux->tempo){
						aux->id = processosAux->id;
						aux->chegada = processosAux->chegada;
						aux->tempo = processosAux->tempo;
						aux->ioI = processosAux->ioI;
						aux->ioT = processosAux->ioT;
						aux->timer = processosAux->timer;

						processosAux->id = processoAnterior->id;
						processosAux->chegada = processoAnterior->chegada;
						processosAux->tempo = processoAnterior->tempo;
						processosAux->ioI = processoAnterior->ioI;
						processosAux->ioT = processoAnterior->ioT;
						processosAux->timer = processoAnterior->timer;
					
						processosAux->id = aux->id;
						processosAux->chegada = aux->chegada;
						processosAux->tempo = aux->tempo;
						processosAux->ioI = aux->ioI;
						processosAux->ioT = aux->ioT;
						processosAux->timer = aux->timer;

					}
				processoAnterior = processos;
				processosAux = processos->prox;	
			}
			processoAnterior = processos;
			processosAux = processos->prox;
		}
			
	*/			
	return processos;
}

proc* SJF_execucao(proc *processos, proc *novoProcesso)
{
	 int inicioDaLista = 1;

    proc *processosAux = NULL, *processoAnterior = NULL;

	  printf("\tEscalonamento SJF \n");
     
	if(processos == NULL){
		processos = novoProcesso;
     }else{
            processosAux = processos;

            while((processosAux != NULL) && (novoProcesso->chegada > processosAux->chegada)){
                processoAnterior = processosAux;
                processosAux = processosAux->prox;
                
					 if (inicioDaLista == 1){
						 inicioDaLista = 0;
					 }
            }

            if (processosAux == NULL){
                processoAnterior->prox = novoProcesso;
                novoProcesso->ant = processoAnterior;
            }else{
                if (inicioDaLista == 1){
                    novoProcesso->prox = processosAux;
                    processosAux->ant = novoProcesso;
                    processos = novoProcesso;
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
