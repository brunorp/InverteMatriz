#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
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
    for (int i=0; i<l; i++)
        for (int j=0; j<c; j++)
        {
          matrizInvertida[i][j] = matriz[c-j-1][i];
        }

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



