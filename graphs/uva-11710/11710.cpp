#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>
using namespace std;

typedef set<string> ss;
typedef pair<string, int> psi;
typedef pair<int, string> pis;
typedef vector<psi> vpsi;
typedef vector<pis> vpis;
typedef map<string, vpsi> msvs;
typedef map<string, bool> msb;
typedef priority_queue<pis, vpis, greater<pis>> asc_pqpis;

template <typename T>
void setPrint(set<T> st) {
    for (T elem : st)
        cout << elem << " ";
    cout << "\n";
}

template <typename T, typename U>
void adjListPrint(map<T, vector<pair<T, U>>> adjList) {
    for (auto node : adjList) {
        cout << node.first << ": ";
        for (pair<T, U> edge : node.second) {
            cout << "(" << edge.first << ", " << edge.second << ") ";
        }
        cout << "\n";
    }
}

void dfs(msvs adjList, msb *visited, string u) {
    (*visited)[u] = true;

    for (auto v : adjList[u])
        if (!(*visited)[v.first])
            dfs(adjList, visited, v.first);
}

bool graphStronglyConnected(msvs adjList, ss nodes, string root) {
    msb visited;
    for (auto node : nodes)
        visited[node] = false;

    dfs(adjList, &visited, root);
    for (auto node : nodes)
        if (!visited[node])
            return false;

    return true;
}

int mstPrim(msvs adjList, ss nodes, string root) {
    ss tree;
    tree.insert(root);

    asc_pqpis edges;
    for (auto node : adjList[root])
        edges.emplace(node.second, node.first);
    
    int mst_cost = 0;
    while (tree != nodes) {
        pis min_edge = edges.top();
        edges.pop();

        if (tree.find(min_edge.second) == tree.end()) {
            mst_cost += min_edge.first;
            tree.insert(min_edge.second);

            for (auto node : adjList[min_edge.second])
                if (tree.find(node.first) == tree.end())
                    edges.emplace(node.second, node.first);
        }
    }

    return mst_cost;
}

int main() {
    int stations, lines;
    while (cin >> stations >> lines) {
        if (!stations and !lines) break;
        
        ss nodes;
        msvs adjList;

        for (int s = 0; s < stations; s++) {
            string name;
            cin >> name;
            nodes.insert(name);
        }

        for (int l = 0; l < lines; l++) {
            string from, to;
            int monthly_ticket;
            cin >> from >> to >> monthly_ticket;
            adjList[from].emplace_back(to, monthly_ticket);
            adjList[to].emplace_back(from, monthly_ticket);
        }

        string start;
        cin >> start;

        /*  printf("Stations: %d\n", stations);
        setPrint(nodes);
        printf("Lines: %d\n", lines);
        adjListPrint(adjList);
        cout << "START @ " << start << "\n"; */

        if (!graphStronglyConnected(adjList, nodes, start)) {
            cout << "Impossible\n";
            continue;
        }

        int min_monthly_expense = mstPrim(adjList, nodes, start);
        cout << min_monthly_expense << "\n";
    }
}