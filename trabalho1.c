#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SEED time(NULL)

int qtd = 0;
void printIntArray();
void bubbleSort();
void mergeSort();
void quickSort();

// argc, argv
int main(int argc, char *argv[]){
    /*
    ordenação n^2
    mergeSort (m)
    quickSort
    vetor com 10 numeros aleatorios
    marcar o tempo de execução durante a ordenação (benchmark)
    tamanhos diferentes (não entendi, 10 numeros e tamanhos diferentes?) */
    int *arrNum;
    char *mode = argv[2];
    qtd = atoi(argv[1]);
    printf("qtd: %d\n", qtd);
    arrNum = (int*) malloc(qtd * sizeof(int));

    srand(SEED);
    for (int i = 0; i < qtd; i++) arrNum[i] = (rand() % 11);
    puts("Array original:");
    printIntArray(arrNum);
    
    if(mode == "m"){
        // mergeSort
    } else if (mode == "q") {
        // quickSort
    } else {
        // n^2
        bubbleSort(arrNum);
    }

    puts("\nArray sorteado:");
    printIntArray(arrNum);
    puts("\nArray sorteado certamente:");
    bubbleSort(arrNum);
    printIntArray(arrNum);

}

void printIntArray(int arr[]){
    for (int i = 0; i < qtd; i++) printf("%d ", arr[i]);
    puts("");
}

void bubbleSort(int arr[]){
    int aux;
    for (int i = 1; i < qtd; i++) {
        for (int j = 0; j < qtd - i; j++) {
            if(arr[j] > arr[j + 1]){
                aux = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = aux;
            }
        }
    }
}

void mergeSort(int arr[]){
    
}

void quickSort(int arr[]){
}