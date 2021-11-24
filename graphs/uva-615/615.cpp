#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>
using namespace std;

typedef vector<long> vl;
typedef queue<long> ql;
typedef set<long> sl;
typedef map<long, long> mll;
typedef map<long, bool> mlb;
typedef map<long, vl> mlvl;

void graphAddEdge(mlvl *adjList, sl *nodes, mll *parent, long u, long v) {
    (*nodes).insert(u);
    (*nodes).insert(v);
    (*adjList)[u].push_back(v);
    (*parent)[v] = u;
}

void graphPrint(mlvl adjList, sl nodes) {
    for (long node : nodes) {
        cout << node << ": ";
        for (long edge : adjList[node])
            cout << edge << " ";
        cout << "\n";
    }
}

void graphClear(mlvl *adjList, sl *nodes, mll *parent, mlb *visited) {
    for (long node : *nodes)
        (*adjList)[node].clear();
    (*nodes).clear();
    (*parent).clear();
    (*visited).clear();
}

bool bfs(mlvl adjList, sl nodes, mlb *visited, long root) {
    ql q;
    q.push(root);
    (*visited)[root] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (long v : adjList[u]) {
            if (!(*visited)[v]) {
                (*visited)[v] = true;
                q.push(v);
            } else {
                return false;
            }
        }
    }

    return true;
}

int main() {
    mlb visited;
    mll parent;
    mlvl adjList;
    sl nodes;
    long u, v;
    int testCase = 1;
    
    while (cin >> u >> v) {
        if (u < 0 and v < 0) break;
        if (u == 0 and v == 0) {
            //graphPrint(adjList, nodes);
            
            long root;
            int noInEdgesNodeCount = 0;
            for (long node : nodes) {
                if (parent[node] == 0) {
                    root = node;
                    noInEdgesNodeCount++;
                }
            }

            bool isTree = true;
            if (noInEdgesNodeCount > 1)
                isTree = false;
            else {
                isTree = bfs(adjList, nodes, &visited, root);
                if (isTree) {
                    for (long node : nodes) {
                        if (!visited[node]) {
                            isTree = bfs(adjList, nodes, &visited, node);
                            noInEdgesNodeCount++;
                        }
                    }
                    if (noInEdgesNodeCount > 1)
                        isTree = false;
                }
            }

            cout << "Case " << testCase++ << " is" << (!isTree ? " not" : "") << " a tree.\n";

            graphClear(&adjList, &nodes, &parent, &visited);
            continue;
        }
        graphAddEdge(&adjList, &nodes, &parent, u, v);
    }
}