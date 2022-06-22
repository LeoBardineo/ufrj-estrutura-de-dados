#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

class ListaInt {
    public:
        int arr[1000], tamanho;
        ListaInt();
        void inserir(int num);
        void printarListaInt();
};

ListaInt::ListaInt(){
    tamanho = 0;
};

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
        ListaInt adj[1000], topologicaOrdenada;
        bool visitados[1000];
        int vertices;
        Grafo(int v);
        void adicionaNo(int u, int v);
        void visitaVertice(int vertice);
        void printaOrdenacaoTopologica();
};

Grafo::Grafo(int v){
    vertices = v;
};

void Grafo::adicionaNo(int u, int v){
    adj[u].inserir(v);
}

void Grafo::visitaVertice(int vertice){
    visitados[vertice] = true;

    // for(ListaInt l : adj){
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
    cout << "===== Ordenação Topológica =====" << endl;
    cout << "Insira o número de vertices e as arestas:" << endl;
    int vertices, arestas;
    cin >> vertices >> arestas;
    Grafo grafo(vertices);
    cout << endl << "Insira as adjacências indicando o vértice de origem e o de destino:" << endl;
    for (int i = 0; i < arestas; i++) {
        cout << i+1 << "ª aresta: ";
        int u, v;
        cin >> u >> v;
        grafo.adicionaNo(u, v);
    }

    // Saída
    cout << endl << "Ordenação topológica: " << endl;
    grafo.printaOrdenacaoTopologica();
    return 0;
}