#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SEED time(0)

void printIntArray();
void bubbleSort();
void mergeSort();
void merge();
void quickSort();

int main(int argc, char *argv[]){
    int *arrNum;
    int qtd = atoi(argv[2]);
    char *mode = argv[3];
    printf("qtd: %d\n", qtd);
    arrNum = (int*) malloc(qtd * sizeof(int));

    srand(SEED);
    for (int i = 0; i < qtd; i++) arrNum[i] = rand();
    puts("Array original:");
    printIntArray(arrNum, qtd);
    
    if(mode == "-m"){
        mergeSort(arrNum, 0, qtd);
    } else if (mode == "-q") {
        // quickSort
    } else {
        bubbleSort(arrNum, qtd);
    }

    puts("\nArray sorteado:");
    printIntArray(arrNum, qtd);
    puts("\nArray sorteado certamente:");
    bubbleSort(arrNum, qtd);
    printIntArray(arrNum, qtd);

}

void printIntArray(int arr[], int tam){
    for (int i = 0; i < tam; i++) printf("%d ", arr[i]);
    puts("");
}

void bubbleSort(int arr[], int tam){
    int aux;
    for (int i = 1; i < tam; i++)
        for (int j = 0; j < tam - i; j++)
            if(arr[j] > arr[j + 1]){
                aux = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = aux;
            }
}

void merge(int arr[], int inicio, int meio, int fim){
    // Dividindo a lista em lista da esquerda e da direita
    int qtdEsquerda = meio - inicio + 1;
    int qtdDireita = meio - fim;
    int *listaEsquerda = malloc(qtdEsquerda * sizeof(int));
    int *listaDireita = malloc(qtdDireita * sizeof(int));
    for (int i = 0; i < qtdEsquerda; i++) listaEsquerda[i] = arr[inicio + i];
    for (int i = 0; i < qtdDireita; i++) listaDireita[i] = arr[meio + 1 + i];

    // Ordenando e juntando/"mergeando" as duas
    int topoEsquerda = 0;
    int topoDireita = 0;
    for (int i = inicio; i < fim; i++)
        if(topoEsquerda >= qtdEsquerda) { // Já foi percorrido toda a lista da esquerda, restando apenas a da direita ser adicionada à lista.
            arr[i] = listaDireita[topoDireita];
            topoDireita++;
        } else if (topoDireita >= qtdDireita) { // Só falta a da esquerda ser adicionada
            arr[i] = listaEsquerda[topoEsquerda];
            topoEsquerda++;
        } else if (listaEsquerda[topoEsquerda] < listaDireita[topoDireita]) { // O topo da lista da esquerda é menor que o topo da direita
            arr[i] = listaEsquerda[topoEsquerda];
            topoEsquerda++;
        } else {  // O topo da lista da direita é menor que o topo da esquerda
            arr[i] = listaDireita[topoDireita];
            topoDireita++;
        }
}

void mergeSort(int arr[], int inicio, int fim){
    int meio;
    if(fim - inicio > 1)
        meio = (fim + inicio) / 2;
        mergeSort(arr, inicio, meio);
        mergeSort(arr, meio + 1, fim);
        merge(arr, inicio, meio, fim);
}

void quickSort(int arr[], int tam){

}