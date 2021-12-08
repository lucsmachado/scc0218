#include <iostream>
#include <string>

using namespace std;

#define PRIME_NUMBER 131071

// Calculates x^y % p
long powMod(long x, long y, long p) {
    if (y == 0)
        return 1;

    if (y % 2 == 0)
        return powMod((x*x) % p, y >> 1, p) % p;

    return x * powMod(x, y-1, p) % p;
}

bool isDivisibleByPrime(string binaryNumber) {
    int numBits = binaryNumber.size();
    long remainder = 0;
    for (int i = 0; i < numBits; i++) {
        int bit = binaryNumber[i] - '0';
        if (bit)
            remainder += powMod(2, numBits-i-1, PRIME_NUMBER);
    }
    return (remainder % PRIME_NUMBER == 0) ? true : false;
}

int main() {
    string binaryNumber;
    char bit;
    while (cin >> bit) {
        if (bit == '#') {
            if (isDivisibleByPrime(binaryNumber))
                cout << "YES\n";
            else
                cout << "NO\n";
                
            binaryNumber = "";
            continue;
        }

        binaryNumber += bit;
    }
}