#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<pthread.h>

//struct que será passada como parâmetro para a função que gira a matriz 90 graus para a direita
typedef struct dados {
	int l;
	int c;
	int t;
	int posicao;
	double **matriz;
    	double **matrizInvertida;
}DADOS;

//função que retorna a linha da posição atual em que a thread está
int retornaLinha(int posicaoAtual, int coluna){	
	return posicaoAtual/coluna;
}

//função que retorna a coluna da posição atual em que a thread está
int retornaColuna(int posicaoAtual, int coluna){
	return posicaoAtual%coluna;
}

//Função que gira a matriz 90 graus para a direita, as threads percorrem a matriz de forma intercalada
void *inverte(void *argts){
	DADOS *argumentos = argts;
	                                              
	int posicaoatual = argumentos->posicao;
	
	//Percorre a matriz da posição atual até o final dela.
	while (posicaoatual<(argumentos->l * argumentos->c)){
		if(argumentos->l != argumentos->c){ //se a matriz não for quadrada
			int linhaAtual = retornaLinha(posicaoatual, argumentos->c);
			int colunaAtual = retornaColuna(posicaoatual, argumentos->c);
			argumentos->matrizInvertida[colunaAtual][linhaAtual] = argumentos->matriz[argumentos->l - linhaAtual - 1][colunaAtual];
			posicaoatual = posicaoatual + argumentos->t;
		}else{ //se a matriz for quadrada
			int linhaAtual = retornaLinha(posicaoatual, argumentos->c);
			int colunaAtual = retornaColuna(posicaoatual, argumentos->c);	
			argumentos->matrizInvertida[linhaAtual][colunaAtual] = argumentos->matriz[argumentos->c - colunaAtual - 1][linhaAtual];
			posicaoatual = posicaoatual + argumentos->t;
		}
		
	} 
}

int main(int argc, char *argv[])
{
	DADOS argumentos[16];
	int l = atoi(argv[1]); //numero de linhas
	int c = atoi(argv[2]); //numero de colunas
	int t = atoi(argv[3]); //numero de threads
    	FILE *file = fopen(argv[4], "r");
	
    
	//alocação dinâmica da matriz
    double **matriz = (double **)malloc(l * sizeof(double *));
       for (int i = 0; i < l; i++){ 
       	matriz[i] = (double*) malloc(c * sizeof(double));
       	for (int j = 0; j < c; j++){ 
           fscanf(file, "%lf", &matriz[i][j]);
       }
  }
	//alocação dinâmica da matriz invertida
 double **matrizInvertida = (double **)malloc(c * sizeof(double *));
       for (int i = 0; i < c; i++){ 
       	matrizInvertida[i] = (double*) malloc(l * sizeof(double)); 
       	for (int j = 0; j < l; j++){ 
           matrizInvertida[i][j] = 0;
       }
  }
    
    pthread_t threads[t];
  
    if (!file)
        printf ("Erro na abertura do arquivo. \n");
	
	float inicial = clock(); //Inicializa a contagem de tempo das threads

	//da valor as variaveis da struct e executa a função inverte com as threads.
	for(int i=0; i<t; i++){	
		argumentos[i].matriz = matriz;
		argumentos[i].matrizInvertida = matrizInvertida;
		argumentos[i].l = l;
		argumentos[i].c = c;
		argumentos[i].t = t;
		argumentos[i].posicao = i;
		pthread_create(&threads[i], NULL, &inverte, (void *)&argumentos[i]);
	}
	for(int i=0; i<t; i++){	
		pthread_join(threads[i], NULL);
	}

	float final = clock(); // Finaliza a contagem de tempo das threads
	

    	FILE *fileSaida = fopen(argv[5], "w");
	
	   //escreve a matriz resultado (matriz invertida) em outro arquivo.
	   for ( int i=0; i<c; i++ ){
		for (int j=0; j<l; j++ )
		{
		    fprintf(fileSaida, "%0.2lf ", matrizInvertida[i][j]);
		}
		fprintf(fileSaida, "\n");
	    }

	fclose(file);
	fclose(fileSaida);

	float tep = (final - inicial) * 1000.0 / CLOCKS_PER_SEC; //Cálcula o tempo gasto com N threads
	printf("Tempo de execucação com [%d] threads: %f milissegundos \n", t,tep); 	//Imprime o tempo de execução com N threads


    return 0;
}
