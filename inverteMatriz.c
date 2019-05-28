#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<string.h>
#include<pthread.h>



//THREAD PARA INVERTER
void inverte(int l, int c, float matriz[l][c], float matrizInvertida[l][c])
{
	 for (int i=0; i<l; i++)
        for (int j=0; j<c; j++)
        {
          matrizInvertida[i][j] = matriz[c-j-1][i];
        }
}
	

int main(int argc, char *argv[]) //EXECUTANDO COM A THREAD PRINCIPAL
{
    int l, c, t;

    l=atoi(argv[1]);
    c=atoi(argv[2]);
    t=atoi(argv[3]);

    float matriz[l][c];
    float matrizInvertida[l][c];

    FILE *file = fopen(argv[4], "r");	
    FILE *fileSaida = fopen(argv[5], "w");

    if (!file)
        printf ("Erro na abertura do arquivo. \n");
    else
	for(int i=0; i<l; i++){
	    for(int j=0; j<c; j++){
	    	 fscanf(file, "%f", &matriz[i][j]);
	    }
	}
    
	//inverte matriz
	inverte(l,c,matriz,matrizInvertida);

	//JOIN - CONTINUAR EXECUTANDO APÓS EXECUTAR THREAD DO INVERTE
	//escreve o resultado em outro arquivo
   for ( int i=0; i<l; i++ ){
        for (int j=0; j<c; j++ )
        {
            fprintf(fileSaida, "%0.2f ", matrizInvertida[i][j]);
        }
        fprintf(fileSaida, "\n");
    }

    return 0;
}



