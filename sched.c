#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
	printf("O nome do arquivo de ENTRADA é: %s\n", argv[2]);
	printf("O nome do arquivo de SAIDA é: %s\n", argv[3]);

	if(strcmp("FCFS",argv[1])==0)
	{
		printf ("Você escolheu o FCFS\n");
	}	
		else if (strcmp("RR",argv[1])==0)
		{
			printf ("Você escolheu o RR\n");
		}
			else if (strcmp("SJF",argv[1])==0)
		{
				printf ("Você escolheu o SJF\n");
		}
			else
				printf ("Você não escolheu nenhuma opção válida! Finalizando processo\n");

	return EXIT_SUCCESS;
}
