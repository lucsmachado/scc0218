#include <iostream>
#include <vector>

using namespace std;

#define MAX_NODES 100

typedef pair<int, int> ii;
typedef vector<ii> vii;

void adjListPrint(vii adjList[]) {
    for (int node = 0; node < MAX_NODES; node++) {
        if (!adjList[node].empty()) {
            cout << node << ": ";
            for (ii edge : adjList[node]) {
                cout << "(" << edge.first << ", " << edge.second << ") ";
            }
            cout << "\n";
        }
    }
}

int main() {
    int test_cases = 0, num_nodes, num_edges, source, sink;
    while (cin >> num_nodes) {
        if (num_nodes == 0) break;

        vii adjList[MAX_NODES];
        
        cin >> source >> sink >> num_edges;

        int u, v, capacity;
        for (int i = 0; i < num_edges; i++) {
            cin >> u >> v >> capacity;
            adjList[u].emplace_back(v, capacity);
            adjList[v].emplace_back(u, capacity);
        }

        //adjListPrint(adjList);
        cout << "Network " << ++test_cases << "\n";
        cout << "The bandwidth is " << ".\n\n";
    }
}