#include <iostream>
#include <map>

using namespace std;

typedef long long ll;
typedef map<ll, int> mlli;

bool oneDigitFactors(mlli *factors, ll n) {
    if (n < 10) {
        (*factors)[n]++;
        return true;
    }

    for (int i = 9; i > 1; i--) {
        while (n % i == 0) {
            (*factors)[i]++;
            n /= i;
        }
    }

    return (n == 1) ? true : false;
}

void printFactors(mlli factors) {
    for (auto factor : factors) {
        for (int i = 0; i < factor.second; i++) {
            cout << factor.first;
        }
    }
    cout << "\n";
}

int main() {
    int test_cases;
    cin >> test_cases;

    while (test_cases--) {
        ll n;
        cin >> n;
        
        mlli q;
        if (oneDigitFactors(&q, n))
            printFactors(q); 
        else
            cout << "-1\n";
    }
}