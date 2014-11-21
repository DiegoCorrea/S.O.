# ifndef _PROTOTIPO_H_
# define _PROTOTIPO_H_

# include <stdio.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# define MAX 50

int timer;
int permitido;


typedef struct proc
{
    int  id;			//ID do processo
    int  chegada;		//Instante de chegada
    int  tempo;			//Tempo de processamento
    int  ioI;			//Instante que inicia o IO
    int  ioT;			//Instante que termina o IO
    struct   proc *prox;
}proc;
void executar();
proc* LerEntrada(char linha[MAX]);
//proc* CriarTabela(char *argv[]);
proc* FCFS(proc *);

# endif /*_PROTOTIPO_H_*/