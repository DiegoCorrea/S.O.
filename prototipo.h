# ifndef PROTOTIPO_H_INCLUDED
# define PROTOTIPO_H_INCLUDED

# include <stdio.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# define MAX 50




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

# endif /*PROTOTIPO_H*/