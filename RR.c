#include "prototipo.h"

proc* RR(proc *processos, proc *novo)
{
	proc *caminhante = NULL, *anterior = NULL;
		

	for(caminhante = processos; (caminhante != NULL) && (caminhante->chegada < novo->chegada) ;anterior = caminhante, caminhante = caminhante->prox);
	if(processos == NULL)
	{
		processos = novo;
	}
	else
	{
		if(processos == caminhante)
		{
			novo->prox = caminhante;
			caminhante->ant = novo;
			processos = novo;
		}
		else
		{
			if(caminhante == NULL)
			{
				anterior->prox = novo;
				novo->ant = anterior;
				
			}
			else
			{
				anterior->prox = novo;
				caminhante->ant = novo;

				novo->prox = caminhante;
				novo->ant = anterior;
			}
		}
	}

	return processos;
}



proc* RR_execucao(proc *processos, proc *novo)
{
	proc *caminhante = NULL, *anterior = NULL;
		

		for(caminhante = processos; (caminhante != NULL) && (caminhante->chegada < novo->chegada) ;anterior = caminhante, caminhante = caminhante->prox);
		if(processos == NULL)
		{
			processos = novo;
		}
		else
		{
			if(processos == caminhante)
			{
				novo->prox = caminhante;
				caminhante->ant = novo;
				processos = novo;
			}
			else
			{
				if(caminhante == NULL)
				{
					anterior->prox = novo;
					novo->ant = anterior;
					
				}
				else
				{
					anterior->prox = novo;
					caminhante->ant = novo;

					novo->prox = caminhante;
					novo->ant = anterior;
				}
			}
		}
	return processos;
}




