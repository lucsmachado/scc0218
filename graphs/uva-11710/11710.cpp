#include <iostream>
#include <vector>
#include <set>
#include <map>
using namespace std;

typedef set<string> ss;
typedef pair<string, int> psi;
typedef vector<psi> vpsi;
typedef map<string, vpsi> msvs;

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

int main() {
    int stations, lines;
    while (cin >> stations >> lines) {
        if (!stations and !lines) break;

        ss nodes;
        msvs adjList;

        printf("Stations: %d\n", stations);
        for (int s = 0; s < stations; s++) {
            string name;
            cin >> name;
            nodes.insert(name);
        }

        setPrint(nodes);

        printf("Lines: %d\n", lines);
        for (int l = 0; l < lines; l++) {
            string from, to;
            int monthly_ticket;
            cin >> from >> to >> monthly_ticket;
            adjList[from].emplace_back(to, monthly_ticket);
            adjList[to].emplace_back(from, monthly_ticket);
        }

        adjListPrint(adjList);

        string start;
        cin >> start;
        if (nodes.find(start) != nodes.end())
            cout << "START @ " << start << "\n";
    }
}