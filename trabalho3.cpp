#include <iostream>
#include <string>
#include <vector>

using namespace std;

// "# vertices" "# arestas"
int main(){
    // Entrada
    int espacoPos, vertices, arestas;
    cin >> vertices >> arestas;
    vector<vector<int>> grafo(vertices, vector<int>(arestas));
    for (int i = 0; i < arestas; i++) {
        int u, v;
        cin >> u >> v;
        grafo[u].push_back(v);
    }

    cout << "salve\n";

    // Saída
    for(vector<int> l : grafo)
        for(int a : l)
            cout << a << endl;
    return 0;
}