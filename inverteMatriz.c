#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<string.h>
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
int retornaLinha(int posicaoAtual, int linha, int coluna){	
	int soma=0;
	for (int i=0; i<linha; i++){
        	for (int j=0; j<coluna; j++){
			if(posicaoAtual == i+j+soma)
				return i;
		}
		soma = soma+2;
	}
}

//função que retorna a coluna da posição atual em que a thread está
int retornaColuna(int posicaoAtual, int linha, int coluna){
	int soma=0;
	for (int i=0; i<linha; i++){
        	for (int j=0; j<coluna; j++){
			if(posicaoAtual == i+j+soma)
				return j;
		}
		soma = soma+2;
	}
}

//Função que gira a matriz 90 graus para a direita, as threads percorrem a matriz de forma intercalada
void *inverte(void *argts){
	DADOS *argumentos = argts;
	                                              
	int posicaoatual = argumentos->posicao;

	while (posicaoatual<(argumentos->l * argumentos->c)){
		int linhaAtual = retornaLinha(posicaoatual, argumentos->l, argumentos->c);
		int colunaAtual = retornaColuna(posicaoatual, argumentos->l, argumentos->c);

		argumentos->matrizInvertida[linhaAtual][colunaAtual] = argumentos->matriz[argumentos->c - colunaAtual - 1][linhaAtual];
		posicaoatual = posicaoatual + argumentos->t;
		
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
 double **matrizInvertida = (double **)malloc(l * sizeof(double *));
       for (int i = 0; i < l; i++){ 
       	matrizInvertida[i] = (double*) malloc(c * sizeof(double)); 
       	for (int j = 0; j < c; j++){ 
           matrizInvertida[i][j] = 0;
       }
  }
    
    pthread_t threads[t];
  
    if (!file)
        printf ("Erro na abertura do arquivo. \n");
	
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
	

    	FILE *fileSaida = fopen(argv[5], "w");
	
	//escreve a matriz resultado (matriz invertida) em outro arquivo.
   for ( int i=0; i<l; i++ ){
        for (int j=0; j<c; j++ )
        {
            fprintf(fileSaida, "%0.2lf ", matrizInvertida[i][j]);
        }
        fprintf(fileSaida, "\n");
    }

	fclose(file);
	fclose(fileSaida);

    return 0;
}


