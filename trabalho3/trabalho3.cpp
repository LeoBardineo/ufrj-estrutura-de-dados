#include <iostream>
#include <string>
#include <vector>

using namespace std;

// "# vertices" "# arestas"
int main(){
    // Entrada
    int espacoPos, vertices, arestas;
    cin >> vertices >> arestas;
    vector<vector<int>> grafo(vertices);
    for (int i = 0; i < arestas; i++) {
        int u, v;
        cin >> u >> v;
        grafo[u].push_back(v);
    }

    // Saída
    for(int i = 0; i < grafo.size(); i++){
        if(!grafo[i].size()) continue;
        vector<int> adj = grafo[i];
        cout << "grafo[" << i << "]: " << endl;
        for(int j : adj)
            cout << j << endl;
    }
    return 0;
}