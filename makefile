all:
	gcc -Wall sched.c operacoes.c FCFS.c RR.c SJF.c CPU.c ES.c semaforo.c arquivo.c escalonador.c -o sched