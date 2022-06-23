#include <iostream>

using namespace std;

#define MAX 500 // não pode depois de 719 (?)

class ListaInt {
    public:
        int arr[MAX], tamanho;
        ListaInt();
        void inserir(int num);
        void printarListaInt();
};

ListaInt::ListaInt(){
    tamanho = 0;
}

void ListaInt::inserir(int num){
    arr[tamanho] = num;
    tamanho++;
}

void ListaInt::printarListaInt(){
    cout << "[";
    for(int i = 0; i < tamanho; i++)
        cout << arr[i] << " ";
    cout << "]\n";
}

class Grafo{
    public:
        ListaInt adj[MAX], topologicaOrdenada;
        bool visitados[MAX];
        int vertices;
        Grafo(int v);
        void adicionaNo(int u, int v);
        void visitaVertice(int vertice);
        void printaOrdenacaoTopologica();
};

Grafo::Grafo(int v){
    vertices = v;
}

void Grafo::adicionaNo(int u, int v){
    adj[u].inserir(v);
}

void Grafo::visitaVertice(int vertice){
    visitados[vertice] = true;

    for(int i = 0; i < adj->tamanho; i++){
        ListaInt l = adj[i];
        for(int j = 0; j < l.tamanho; j++){
            if(!visitados[j]){
                visitaVertice(j);
            }
        }
    }

    topologicaOrdenada.inserir(vertice);
}

void Grafo::printaOrdenacaoTopologica(){
    for(int i = 0; i < vertices; i++){
        visitados[i] = false;
    }

    for(int i = 0; i < vertices; i++){
        if(visitados[i] == false){
            visitaVertice(i);
        }
    }

    for(int i = topologicaOrdenada.tamanho-1; i > -1; --i){
        cout << topologicaOrdenada.arr[i] << " ";
    }
    cout << endl;
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
        cout << i+1 << "a adjacência: ";
        int u, v;
        cin >> u >> v;
        grafo.adicionaNo(u, v);
    }

    // Saída
    cout << endl << "Ordenacao topologica: " << endl;
    grafo.printaOrdenacaoTopologica();
    return 0;
}