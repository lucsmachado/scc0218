#include <iostream>
#include <climits>
#include <array>
#include <vector>
#include <queue>

using namespace std;

#define MAX_NODES 100

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef array<vii, MAX_NODES> adjList;
typedef array<int, MAX_NODES> ai;
typedef array<ii, MAX_NODES> aii;
typedef array<bool, MAX_NODES> ab;
typedef queue<int> qi;

template <typename T, size_t L>
void arrayPrint(array<T, L> array) {
    for (T elem : array)
        cout << elem << " ";
    cout << "\n";
}

void adjListPrint(adjList graph) {
    for (int node = 0; node < MAX_NODES; node++) {
        if (!graph[node].empty()) {
            cout << node << ": ";
            for (ii edge : graph[node]) {
                cout << "(" << edge.first << ", " << edge.second << ") ";
            }
            cout << "\n";
        }
    }
}

void adjListCopy(adjList source, adjList *dest) {
    for (int node = 0; node < MAX_NODES; node++)
        (*dest)[node] = source[node];
}

int getEdgeCapacity(adjList network, int u, int v, int id) {
    int i = 0;
    for (ii edge : network[u]) {
        if (i == id and edge.first == v) {
            return edge.second;
        }
        i++;
    }
    return 0;
}

void setEdgeCapacity(adjList *network, int u, int v, int id, int capacity) {
    int i = 0;
    for (ii edge : (*network)[u]) {
        if (i == id and edge.first == v) {
            (*network)[u][i] = make_pair(edge.first, capacity);
            return;
        }
        i++;
    }
}

// BFS to determine if there is a path connecting nodes 's' and 't'
bool augmentingPath(adjList network, aii *previous, int s, int t) {
    (*previous)[s] = make_pair(-1, -1);
    
    ab visited;
    visited.fill(false);
    visited[s] = true;

    qi next;
    next.push(s);

    while(!next.empty()) {
        int current = next.front();
        next.pop();

        int i = 0;
        for (ii adjacent : network[current]) {
            if (!visited[adjacent.first] and adjacent.second > 0) {
                visited[adjacent.first] = true;
                (*previous)[adjacent.first] = make_pair(current, i);
                next.push(adjacent.first);
            }
            i++;
        }
    }

    return (visited[t]);
}

// Ford-Fulkerson/Edmonds-Karp algorithm to compute the maximum flow in a network between source node 's' and sink node 't'
int maxFlow(adjList network, adjList *residual, int s, int t) {
    int value = 0;
    adjListCopy(network, residual);

    aii previous;

    while (augmentingPath(*residual, &previous, s, t)) {
        int bottleneck = INT_MAX;
        for (int v = t; v != s; v = previous[v].first) {
            int u = previous[v].first;
            int residualCapacity = getEdgeCapacity(*residual, u, v, previous[v].second);
            bottleneck = min(bottleneck, residualCapacity);
        }

        for (int v = t; v != s; v = previous[v].first) {
            int u = previous[v].first;
            int residualCapacity = getEdgeCapacity(*residual, u, v, previous[v].second);
            setEdgeCapacity(residual, u, v, previous[v].second, residualCapacity-bottleneck);
            setEdgeCapacity(residual, v, u, previous[v].second, residualCapacity+bottleneck);
        }

        value += bottleneck;
    }
    return value;
}

int main() {
    int test_cases = 0, num_nodes, num_edges, source, sink;
    while (cin >> num_nodes) {
        if (num_nodes == 0) break;

        adjList network;
        adjList residual;
        
        cin >> source >> sink >> num_edges;

        int u, v, capacity;
        for (int i = 0; i < num_edges; i++) {
            cin >> u >> v >> capacity;
            network[u].emplace_back(v, capacity);
            network[v].emplace_back(u, capacity);
        }

        cout << "Network " << ++test_cases << "\n";
        cout << "The bandwidth is " << maxFlow(network, &residual, source, sink) << ".\n\n";

        /* cout << "Graph:\n";
        adjListPrint(network);
        cout << "Residual Graph:\n";
        adjListPrint(residual); */
    }
}