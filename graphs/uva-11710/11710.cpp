#include <iostream>
#include <vector>
using namespace std;

int main() {
    int stations, lines;
    while (cin >> stations >> lines) {
        if (!stations and !lines) break;

        printf("Stations: %d\n", stations);
        for (int s = 0; s < stations; s++) {
            string name;
            cin >> name;
            cout << s << ": " << name << "\n";
        }

        printf("Lines: %d\n", lines);
        for (int l = 0; l < lines; l++) {
            string from, to;
            int monthly_ticket;
            cin >> from >> to >> monthly_ticket;
            cout << l << ": FROM " << from << " TO " << to << " $" << monthly_ticket << ".00\n" ;
        }

        string start;
        cin >> start;
        cout << "START @ " << start << "\n";
    }
}