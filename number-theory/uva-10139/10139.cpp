#include <iostream>
#include <algorithm>
#include <bitset>
#include <vector>
#include <map>

using namespace std;

#define SIZE 1e7

typedef long long ll;
typedef vector<ll> vll;
typedef map<ll, int> mlli;

void sieve(bitset<(int) SIZE> *primeFlag, vll *primes) {
    ll len = (*primeFlag).size();

    (*primeFlag).set();
    (*primeFlag)[0] = (*primeFlag)[1] = false;

    for (ll n = 2; n < len; n++) {
        if ((*primeFlag)[n]) {
            (*primes).push_back(n);
            for (ll mult = n*n; mult < len; mult += n) {
                (*primeFlag)[mult] = false;
            }
        }
    }
}

bool isPrime(bitset<(int) SIZE> primeFlag, vll *primes, long n) {
    if (n <= (ll) primeFlag.size())
        return primeFlag[n];

    ll len = (*primes).size();
    for (ll i = 0; i < len and (*primes)[i]*(*primes)[i] <= n; i++) {
        if (n % (*primes)[i] == 0)
            return false;
    }

    (*primes).push_back(n);
    return true;
}

void primeFactors(mlli *factors, vll primes, long n) {
    ll i = 0;
    ll factor = primes[i];
    while (factor*factor <= n) {
        while (n % factor == 0) {
            (*factors)[factor]++;
            n /= factor;
        }
        factor = primes[++i];
    }

    if (n != 1)
        (*factors)[n]++;
}

void printFactors(mlli factors) {
    for (auto factor : factors) {
        for (int i = 0; i < factor.second; i++) {
            cout << factor.first  << " ";
        }
    }
    cout << "\n";
}

long factorialPrimeFactorPower(long n, long factor) {
    long power = 0;
    for (long p = factor; p <= n; p *= factor)
        power += n/p;
    return power;
}


bool divide(mlli divisorPrimeFactors, long n) {
    for (auto divisorFactor : divisorPrimeFactors) {
        if (divisorFactor.second > factorialPrimeFactorPower(n, divisorFactor.first))
            return false;
    }
    return true;
}

int main() {
    bitset<(int) SIZE> primeFlag;
    vll primes;
    
    bool first_test_case = true;
    long n, divisor;
    while (cin >> n >> divisor) {
        if (divisor <= n) {
            printf("%ld divides %ld!\n", divisor, n);
            continue;
        }

        if (first_test_case) {
            first_test_case = false;
            sieve(&primeFlag, &primes);
        }

        if (isPrime(primeFlag, &primes, divisor)) {
            printf("%ld does not divide %ld!\n", divisor, n);
            continue;
        }

        mlli divisorPrimeFactors;
        primeFactors(&divisorPrimeFactors, primes, divisor);
        /* printf("%ld = ", divisor);
        printFactors(divisorPrimeFactors); */

        if (divide(divisorPrimeFactors, n))
            printf("%ld divides %ld!\n", divisor, n);
        else
            printf("%ld does not divide %ld!\n", divisor, n);
    }
}