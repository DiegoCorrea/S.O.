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
# include <string.h>


# define TRUE 1
# define FALSE 0
# define MAX 50
# define SystemTime 1
# define END -2
# define START -1




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


proc* RR(proc *processos, proc *novo);
proc* RR_execucao(proc *processos, proc *novo);

proc* SJF(proc *processos, proc *novo);
proc* SJF_execucao(proc *processos, proc *novo);

proc* FCFS(proc *processos, proc *novo);
proc* FCFS_execucao(proc *processos, proc *novo);

void EScontarTempo(proc *processos);
proc* ESempilhar(proc *, proc *);


proc* arquivoLer(char arquivo[], char algoritmo[], int *nprocessos);
void arquivoGravar(proc *processoNaCPU, char arquivo[], int tempoTotal);
void arquivoGravarSaida(char arquivo[], int tempoTotal, int nprocessos);

void CPUexecutar(proc *);
int CPU_FCFS(proc *areacritica, int *semaforo);
int CPU_RR(proc *areacritica, int *semaforo);
int CPU_SJF(proc *areacritica, int *semaforo);

void semaforoDown(int *semaforo);
void semaforoUp(int *semaforo);
void semaforoStart(int *semaforo);
void semaforoClose(int *semaforo);

proc* removelista(proc *lista, proc *pararemover);
proc* LerEntrada(char linha[MAX]);
void copiar(proc *areacritica, proc *listaDePronto);
void tempoContar(int *tempoTotal);

int ESCALONADOR_FCFS(proc *listadePronto, proc *areacritica, int *semaforo, char *argv[], int *tempoTotal);
int ESCALONADOR_RR(proc *listadePronto, proc *areacritica, int *semaforo, char *argv[], int *tempoTotal);
int ESCALONADOR_SJF(proc *listadePronto, proc *areacritica, int *semaforo, char *argv[], int *tempoTotal);


# endif /*_PROTOTIPO_H_*/
