# ifndef _PROTOTIPO_H_
# define _PROTOTIPO_H_

# include <stdio.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# define MAX 50

int permitido;


typedef struct proc
{
    int  id;			//ID do processo
    int  chegada;		//Instante de chegada
    int  tempo;			//Tempo de processamento
    int  ioI;			//Instante que inicia o IO
    int  ioT;			//Instante que termina o IO
    int  timer;
    struct   proc *prox;
    struct   proc *ant;
}proc;
proc *areacritica;




void executar();
proc* LerEntrada(char linha[MAX]);
//proc* CriarTabela(char *argv[]);
proc* FCFS(proc *processos, proc *novo);
proc* RR(proc *processos, proc *novo);
proc* SJF(proc *processos, proc *novo);
void contarTempoES(proc *processos);

# endif /*_PROTOTIPO_H_*/