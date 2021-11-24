#include <iostream>
#include <vector>
#include <set>
#include <map>
using namespace std;

typedef set<int> nodeList;
typedef vector<int> edgeList;
typedef map<int, edgeList> adjList;

void printAdjList(adjList adj, nodeList nodes) {
    for (auto node : nodes) {
        cout << node << ": ";
        for (auto edge : adj[node]) {
            cout << edge << " ";
        }
        cout << "\n";
    }
}

int main() {
    nodeList nodes;
    adjList adj;
    long u, v;
    while (cin >> u >> v) {
        if (u < 0 and v < 0) break;
        else if (u == 0 and v == 0) {
            printAdjList(adj, nodes);
            nodes.clear();
            adj.clear();
            continue;
        }
        nodes.insert(u);
        nodes.insert(v);
        adj[u].push_back(v);
    }
}