#include <stdio.h>
#include <stdlib.h>

int main(){
    int N, numN = 0, numAtual, inicio, fim;
    int numeros[101];
    int **matriz;

    while(1){
        scanf("%d", &N);
        if(N == 0) break;
        numeros[numN] = N;
        numN++;
    }
    
    for(int k = 0; k < numN; k++){
        N = numeros[k];

        // Alocando memória para a matriz
        matriz = (int **) malloc(N * sizeof(int *));
        for (int i = 0; i < N; i++){
            matriz[i] = (int *) malloc(N * sizeof(int));
        }

        inicio = 0;
        numAtual = 1;
        fim = N;

        // Preenchendo a matriz
        while(1){
            for (int i = inicio; i < fim; i++)
                for (int j = inicio; j < fim; j++)
                    matriz[i][j] = numAtual;
            if(fim == 0) break;
            numAtual++;
            inicio++;
            fim--;
        }

        // Saída
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if(j == 0)
                    printf("%3d", matriz[i][j]);
                else
                    printf(" %3d", matriz[i][j]);                
            }
            printf("\n");
        }
        printf("\n");

        free(matriz);
    }
    return 0;
}