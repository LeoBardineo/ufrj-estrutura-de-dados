#include <iostream>

using namespace std;

#define MAX 500 // não pode depois de 719 (?)

// Lista do tipo int
class ListaInt {
    public:
        int arr[MAX], tamanho;
        ListaInt();
        ListaInt(int t, int valor);
        void inserir(int num);
        void printarListaInt();
};

ListaInt::ListaInt(){
    tamanho = 0;
}

ListaInt::ListaInt(int t, int valor){
    tamanho = t;
    for (int i = 0; i < tamanho; i++) {
        arr[i] = valor;
    }
}

void ListaInt::inserir(int num){
    arr[tamanho] = num;
    tamanho++;
}

void ListaInt::printarListaInt(){
    cout << "[ ";
    for(int i = 0; i < tamanho; i++)
        cout << arr[i] << " ";
    cout << "]\n";
}

// Fila do tipo int
class Fila{
    int arr[MAX];
    int capacidade;
    int primeiro;
    int ultimo;
    int tamanho;
    public:
        Fila(int t);
        int peek();
        int pop();
        int retornaTamanho();
        void inserir(int valor);
        bool isEmpty();
        bool isFull();
};

Fila::Fila(int t){
    tamanho = 0;
    primeiro = 0;
    ultimo = -1;
    capacidade = t;
}

int Fila::pop(){
    if (isEmpty()){
        cout << "Underflow\n";
        exit(EXIT_FAILURE);
    }
 
    int valor = arr[primeiro];
 
    primeiro = (primeiro + 1) % capacidade;
    tamanho--;
 
    return valor;
}

void Fila::inserir(int item){
    if (isFull()){
        cout << "Overflow\n";
        exit(EXIT_FAILURE);
    }

    ultimo = (ultimo + 1) % capacidade;
    arr[ultimo] = item;
    tamanho++;
}
 
int Fila::peek(){
    if (isEmpty()){
        cout << "Underflow\n";
        exit(EXIT_FAILURE);
    }
    return arr[primeiro];
}
 
int Fila::retornaTamanho() {
    return tamanho;
}
 
bool Fila::isEmpty() {
    return (retornaTamanho() == 0);
}
 
bool Fila::isFull() {
    return (retornaTamanho() == capacidade);
}

// Grafo
class Grafo{
    public:
        ListaInt adj[MAX], topologicaOrdenada;
        int vertices;
        Grafo(int v);
        void adicionaNo(int u, int v);
        void visitaVertice(int vertice);
        void ordernaTopologica();
};

Grafo::Grafo(int v){
    vertices = v;
}

void Grafo::adicionaNo(int u, int v){
    adj[u].inserir(v);
}

void Grafo::ordernaTopologica(){
    ListaInt graus(vertices, 0);
    Fila grauZero(vertices);

    for (int i = 0; i < vertices; i++) {
        ListaInt l = adj[i];
        for (int j = 0; j < l.tamanho; j++)
            graus.arr[l.arr[j]]++;
    }

    for (int i = 0; i < vertices; i++) {
        if(graus.arr[i] == 0){
            grauZero.inserir(i);
        }
    }

    int contaVisitados = 0;

    while(grauZero.retornaTamanho() != 0){
        int x = grauZero.peek();
        grauZero.pop();
        topologicaOrdenada.inserir(x);

        for (int i = 0; i < adj[x].tamanho; i++) {
            int num = adj[x].arr[i];
            graus.arr[num]--;
            if(graus.arr[num] == 0){
                grauZero.inserir(num);
            }
        }
        contaVisitados++;
    }

    if(contaVisitados != vertices){
        cout << "Ciclo\n";
        return;
    }
}

// "# vertices" "# arestas"
int main(){
    // Entrada
    cout << "===== Ordenacao Topologica =====" << endl;
    cout << "Insira o numero de vertices e as arestas:" << endl;
    int vertices, arestas;
    cin >> vertices >> arestas;
    Grafo grafo(vertices);
    cout << endl << "Insira as adjacencias indicando o vertice de origem e o de destino:" << endl;
    for (int i = 0; i < arestas; i++) {
        cout << i+1 << "a adjacencia: ";
        int u, v;
        cin >> u >> v;
        grafo.adicionaNo(u, v);
    }

    // Saída
    cout << endl << "Ordenacao topologica: " << endl;
    grafo.ordernaTopologica();
    grafo.topologicaOrdenada.printarListaInt();
    return 0;
}