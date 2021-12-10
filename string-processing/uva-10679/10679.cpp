#include <iostream>
#include <string>

using namespace std;

void computeBorder(int border[], string pattern) {
    int patternLen = pattern.size();
    int i = 0;
    int j = -1;

    border[i] = j;

    while (i < patternLen) {
        while (j >= 0 and pattern[i] != pattern[j])
            j = border[j];
        border[++i] = ++j;
    }
}

bool isSubstring(string text, string pattern) {
    int textLen = text.size();
    int patternLen = pattern.size();

    int border[patternLen+1];
    computeBorder(border, pattern);

    int i = 0;
    int j = 0;

    while (i < textLen) {
        while (j >= 0 and text[i] != pattern[j])
            j = border[j];
        i++;
        j++;
        if (j == patternLen)
            return true;
    }

    return false;
}

int main() {
    int testCases;
    cin >> testCases;

    while (testCases--) {
        string str;
        cin.ignore(1, '\n');
        cin >> str;

        int numQueries;
        cin >> numQueries;

        while (numQueries--) {
            string query;
            cin.ignore(1, '\n');
            cin >> query;

            if (isSubstring(str, query))
                cout << "y\n";
            else
                cout << "n\n";
        }
    }
    
}