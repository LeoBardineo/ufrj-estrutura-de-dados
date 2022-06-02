/*
    Nome: Leonardo de Melo Soares
    DRE: 120134414
    Forma de execução: .\trabalho1 -n 10 [-m || -q](opcional)
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define SEED time(NULL)

void printIntArray();

void bubbleSort();

void mergeSort();
void merge();

void quickSort();
int particao();

int main(int argc, char *argv[]){
    if(argc <= 2){
        puts("Entrada invalida.");
        return 1;
    }

    int *arrNum, qtd = atoi(argv[2]);
    char mode = argc == 4 ? argv[3][1] : 'b';
    char *modeName;
    arrNum = malloc(qtd * sizeof(int));

    srand(SEED);
    for (int i = 0; i < qtd; i++) arrNum[i] = rand();
    puts("Array gerado aleatoriamente:");
    printIntArray(arrNum, qtd);
    
    if(mode == 'm'){
        modeName = "Merge Sort";
        mergeSort(arrNum, 0, qtd - 1);
    } else if (mode == 'q') {
        modeName = "Quick Sort";
        quickSort(arrNum, 0, qtd - 1); // qtd - 1 pois um deles será o pivot
    } else {
        modeName = "Bubble Sort";
        bubbleSort(arrNum, qtd);
    }

    printf("\nArray sorteado crescentemente utilizando o %s:\n", modeName);
    printIntArray(arrNum, qtd);
    free(arrNum);

    return 0;
}

void printIntArray(int arr[], int tam){
    for (int i = 0; i < tam-1; i++) printf("%d, ", arr[i]);
    printf("%d\n", arr[tam-1]);
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

void merge(int arr[], int inicio, int meio, int fim) {
    int qtdEsquerda = meio - inicio + 1;
    int qtdDireita = fim - meio;
    int *listaEsquerda = malloc(qtdEsquerda * sizeof(int));
    int *listaDireita = malloc(qtdDireita * sizeof(int));
 
    for (int i = 0; i < qtdEsquerda; i++)
        listaEsquerda[i] = arr[inicio + i];

    for (int i = 0; i < qtdDireita; i++)
        listaDireita[i] = arr[meio + 1 + i];
 
    int i = inicio, topoEsq = 0, topoDir = 0;
    while (topoEsq < qtdEsquerda && topoDir < qtdDireita) {
        // O topo da esquerda é menor que o topo da direita, logo o da esquerda deve ser adicionado à lista
        // para que o menor fique à esquerda, caso contrário, o da direita é adicionado, já que ele é o menor
        if (listaEsquerda[topoEsq] <= listaDireita[topoDir]) {
            arr[i] = listaEsquerda[topoEsq];
            topoEsq++;
        } else {
            arr[i] = listaDireita[topoDir];
            topoDir++;
        }
        i++;
    }

    // Já foi percorrido toda a lista da direita, restando apenas a da esquerda ser adicionada à lista.
    while (topoEsq < qtdEsquerda) {
        arr[i] = listaEsquerda[topoEsq];
        topoEsq++; i++;
    }

    // Só falta a da direita ser adicionada.
    while (topoDir < qtdDireita) {
        arr[i] = listaDireita[topoDir];
        topoDir++; i++;
    }
}

void mergeSort(int arr[], int inicio, int fim) {
    int meio = 0;
    if (inicio < fim) {
        meio = (fim + inicio) / 2;
        mergeSort(arr, inicio, meio);
        mergeSort(arr, meio + 1, fim);
        merge(arr, inicio, meio, fim);
    }
}

int particao(int arr[], int inicio, int fim){
    int pivot = arr[fim];
    int j = inicio;
    int aux;
    for (int i = inicio; i < fim; i++) // Percorre os elementos e se for menor que o pivot, realiza a troca
        if(arr[i] <= pivot){
            aux = arr[i];
            arr[i] = arr[j];
            arr[j] = aux;
            j++;
        }
    // Troca o pivot para a posição certa e retorna a posição do pivot
    aux = arr[j];
    arr[j] = arr[fim];
    arr[fim] = aux;
    return j;
}

void quickSort(int arr[], int inicio, int fim){
    if (inicio < fim) {
        int pivot = particao(arr, inicio, fim);
        quickSort(arr, inicio, pivot - 1); // QuickSort com os da esquerda do pivot
        quickSort(arr, pivot + 1, fim); // QuickSort com os da direita do pivot
    }
}