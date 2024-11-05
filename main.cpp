#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<int> primeFactors(int n) {
    vector<int> factors;
    while (n % 2 == 0) {
        factors.push_back(2);
        n /= 2;
    }
    for (int i = 3; i <= sqrt(n); i+=2) {
        while (n % i == 0) {
            factors.push_back(i);
            n /= i;
        }
    }
    if (n > 2) {
        factors.push_back(n);
    }
    return factors;
}

// Function to count the occurrences of prime p in the factors of n!
int countFactorsInFactorial(int n, int p) {
    int count = 0;
    long long power = p;
    while (n / power > 0) {
        count += n / power;
        power *= p;
        if (power > n) break;  // Prevent overflow in power
    }
    return count;
}

// Function to determine if m divides n!
bool doesMDivideNFactorial(int n, int m) {
    if (m == 0) return false;  // 0 cannot divide any factorial
    if (m == 1) return true;   // 1 divides every factorial

    // Get prime factors of m
    map<int, int> factors = primeFactors(m);

    // Check if n! has enough of each prime factor in m
    for (const auto& factor : factors) {
        int p = factor.first;
        int required_count = factor.second;
        int count_in_factorial = countFactorsInFactorial(n, p);
        if (count_in_factorial < required_count) {
            return false;  // Not enough factors of p in n!
        }
    }
    return true;  // All factors of m are present in n! with sufficient count
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        if (doesMDivideNFactorial(n, m)) {
            cout << m << " divides " << n << "!" << endl;
        } else {
            cout << m << " does not divide " << n << "!" << endl;
        }
    }
    return 0;
}


