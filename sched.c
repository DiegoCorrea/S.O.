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
    struct   proc *ant;
    struct   proc *prox;
}proc;

void Inserir_tabela(proc *processos, char linha[30]);

int main(int argc, char *argv[])
{
	proc *processos = NULL;
	char linha[20];

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


	//retirando itens do arquivo
    FILE *fl_entrada = fopen(argv[2], "r" );

    if ( fl_entrada == 0 || fl_entrada == NULL) {
	  fprintf(stderr, "Arquivo %s não encontrado\n", argv[1]);
	  exit(1);
	}
    else 
    {
		while (fscanf(fl_entrada, "%s", linha) != EOF) 
		{
			printf("Linha do arquivo: %s\n", linha);
			Inserir_tabela(processos,linha);
		}
        fclose( fl_entrada );
    }
	return EXIT_SUCCESS;
}

void Inserir_tabela(proc *processos, char linha[30])
{
	proc *processo, *andarilho;
	int i = 0, j= 0;
	char buffer[8];

	processo = (proc*)malloc(sizeof(proc));
	processo->ant = NULL;
	processo->prox = NULL;
	
	while(linha[i] != ';')
	{
		buffer[j] = linha[i];
		i++;
		j++;
	}
	buffer[j] = '\0';
	processo->id = atoi(buffer);
	printf("%d\n", processo->id);
	j = 0;
	i++;
	while(linha[i] != ';')
	{
		buffer[j] = linha[i];
		i++;
		j++;
	}
	buffer[j] = '\0';
	processo->chegada = atoi(buffer);
	printf("%d\n",processo->chegada);
	j = 0;
	i++;
	while(linha[i] != ';')
	{
		buffer[j] = linha[i];
		i++;
		j++;
	}
	buffer[j] = '\0';
	processo->tempo = atoi(buffer);
	printf("%d\n",processo->tempo);
	j = 0;
	i++;
	
	if( linha[i] != ';' )
	{	
		while(linha[i] != ',')
		{
			buffer[j] = linha[i];
			i++;
			j++;
		}
		buffer[j] = '\0';
		processo->ioI = atoi(buffer);
		printf("%d\n",processo->ioI);
		j = 0;
		i++;
		while(linha[i] != ';')
		{
			buffer[j] = linha[i];
			i++;
			j++;
		}
		buffer[j] = '\0';
		processo->ioT = atoi(buffer);
		printf("%d\n",processo->ioT);
	}
	else
	{
		processo->ioI = 0;
		processo->ioT = 0;
		printf("%d\n",processo->ioT);
		printf("%d\n",processo->ioI);

	}

/*
	if( processos == NULL )
	{
		processos = processo;
	}
	else
	{
		for(andarilho = processos; andarilho->prox != NULL; andarilho = andarilho->prox);
	}
*/
}