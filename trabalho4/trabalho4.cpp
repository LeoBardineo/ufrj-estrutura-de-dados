#include <iostream>
#include <algorithm>

using namespace std;

#define MAX 500

class Aresta {
    public:
        int x, y, p;
        Aresta(){};
        Aresta(int x, int y, int p):x(x), y(y), p(p){};
};

class ListaInt {
    public:
        Aresta arr[MAX]; 
        int tamanho;

        ListaInt(){ tamanho = 0; }

        void inserir(int x, int y, int p){
            arr[tamanho] = Aresta(x, y, p);
            tamanho++;
        }
        
        void printarListaInt(){
            cout << "x -- p --> y\n";
            for(int i = 0; i < tamanho; i++){
                cout << arr[i].x << " -- " << arr[i].p << " --> " << arr[i].y << endl;
            }
        }
};

class UnionFind {
    int parent[MAX];
    int ranks[MAX];
  
    public:
        UnionFind(int N) {    
            for (int i = 0; i < N; i++) {
                parent[i] = -1;
                ranks[i] = 1;
            }
        }
  
    int find(int i) {
        if (parent[i] == -1) return i;
        return parent[i] = find(parent[i]);
    }
    
    void unite(int x, int y) {
        int n1 = find(x), n2 = find(y);
  
        if (n1 != n2) {
            if (ranks[n1] < ranks[n2]) {
                parent[n1] = n2;
                ranks[n2] += ranks[n1];
            } else {
                parent[n2] = n1;
                ranks[n1] += ranks[n2];
            }
        }
    }
};

bool ordenaAresta(Aresta a, Aresta b){
    return a.p < b.p;
}

class Grafo{
    public:
        ListaInt adj, topologicaOrdenada;
        int vertices;

        Grafo(int v){ vertices = v; }

        void adicionaNo(int u, int v, int p){
            adj.inserir(u, v, p);
        }

        // void printar(){
        //     for(int i = 0; i < vertices; i++){
        //         ListaInt lista = adj[i];
        //         if(lista.tamanho == 0) continue;
        //         cout << i << "\n";
        //         lista.printarListaInt();
        //     }
        // }
        void kruskal();
};

void Grafo::kruskal() {
    sort(adj.arr, adj.arr + adj.tamanho, ordenaAresta);

    // adj.printarListaInt();

    UnionFind s(vertices+1);
    int custo = 0;
    for (int i = 0; i < adj.tamanho;i++) {
        Aresta aresta = adj.arr[i];
        int p = aresta.p, x = aresta.x, y = aresta.y;
        
        if (s.find(x) != s.find(y)) {
            s.unite(x, y);
            custo += p;
        }
    }
    cout << custo << endl;
}

int main(){
    int vertices, arestas;
    // cout << "===== Arvore Geradora Minima de Kruskal =====" << endl;
    // cout << "Insira o numero de vertices e as arestas:" << endl;
    cin >> vertices >> arestas;
    Grafo grafo(vertices);
    // cout << endl << "Insira as adjacencias indicando o vertice de origem e o de destino, e o peso:" << endl;
    for (int i = 0; i < arestas; i++) {
        // cout << i+1 << "a adjacencia: ";
        int u, v, p;
        cin >> u >> v >> p;
        grafo.adicionaNo(u, v, p);
    }
    grafo.kruskal();
    return 0;
}