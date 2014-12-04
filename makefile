all:
	gcc -Wall sched.c tabela.c FCFS.c RR.c SJF.c CPU.c -o sched