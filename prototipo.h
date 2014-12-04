# ifndef _PROTOTIPO_H_
# define _PROTOTIPO_H_

# include <stdio.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include <unistd.h>
# include <time.h>

# define TRUE 1
# define FALSE 0
# define MAX 50
# define SystemTime 1




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




void executar(proc *);
proc* FCFS(proc *processos, proc *novo);
proc* FCFS_execucao(proc *processos, proc *novo);
proc* RR(proc *processos, proc *novo);
proc* SJF(proc *processos, proc *novo);
void contarTempoES(proc *processos);
proc* empilharES(proc *, proc *);
proc* removelista(proc *lista, proc *pararemover);
char concatenarSaida(proc *processo);


proc* arquivoLer(char arquivo[], char algoritmo[], int *nprocessos);
proc* LerEntrada(char linha[MAX]);
void arquivoGravar(proc *processoNaCPU, char arquivo[], int tempoTotal);
void arquivoGravarSaida(char arquivo[], int tempoTotal, int nprocessos);


int CPU(proc *areacritica, int *semaforo);
void semaforoDown(int *semaforo);
void semaforoUp(int *semaforo);
void semaforoStart(int *semaforo);
void semaforoClose(int *semaforo);

void copiar(proc *areacritica, proc *listaDePronto);



# endif /*_PROTOTIPO_H_*/