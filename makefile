all:
	gcc -Wall sched.c tabela.c FCFS.c RR.c SJF.c -o sched