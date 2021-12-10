#include <iostream>

using namespace std;

int main() {
    int testCases;
    cin >> testCases;

    while (testCases--) {
        long gcd, lcm;
        cin >> gcd >> lcm;

        long a, b;
        /*  by definition, gcd(a, b) | a, b;
            the smallest positive number that divides gcd(a, b) is itself;
            since a <= b and a must be as small as possible:
            => a = gcd(a, b)
        */
        a = gcd;

        /*  by definition, a, b | lcm(a, b)
            => since a = gcd(a, b), b only exists if gcd(a, b) | lcm(a, b)
        */
        if (lcm % gcd != 0) {
            cout << "-1\n";
        } else {
            /* since a = gcd(a, b), we can find the value of b:
               lcm(a, b) = (a * b) / gcd(a, b)
               => a * b = gcd(a, b) * lcm(a, b)
               => a * b = a * lcm(a, b)
               => b = lcm(a, b) 
            */
            b = lcm;
            cout << a << " " << b << "\n";
        }
    }
}