#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

// ============================================================
// 1. Sum S = 1 + 2 + ... + n
// ============================================================
int sumN(int n) {
    if (n <= 0) return 0;
    return n + sumN(n - 1);
}

// ============================================================
// 2. Factorial n!
// ============================================================
long long factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

// ============================================================
// 3. x^n
// ============================================================
double power(double x, int n) {
    if (n == 0) return 1;
    if (n < 0) return 1.0 / power(x, -n);
    if (n % 2 == 0) {
        double half = power(x, n / 2);
        return half * half;
    }
    return x * power(x, n - 1);
}

// ============================================================
// 4. Number of digits in an integer
// ============================================================
int countDigits(int n) {
    if (n < 0) n = -n;
    if (n < 10) return 1;
    return 1 + countDigits(n / 10);
}

// ============================================================
// 5. Check if every digit of an integer is even
// ============================================================
bool allDigitsEven(int n) {
    if (n < 0) n = -n;
    if (n % 2 != 0) return false;
    if (n < 10) return true;
    return allDigitsEven(n / 10);
}

// ============================================================
// 6. Total number of common divisors of two integers
// ============================================================
int gcdHelper(int a, int b) {
    return b == 0 ? a : gcdHelper(b, a % b);
}

int countCommonDivisors(int a, int b) {
    // Common divisors of a and b are divisors of gcd(a,b)
    int g = gcdHelper(a, b);
    // Count divisors of g recursively
    // Helper: count divisors of g from 1..k
    function<int(int, int)> countDivs = [&](int num, int k) -> int {
        if (k == 0) return 0;
        return (num % k == 0 ? 1 : 0) + countDivs(num, k - 1);
    };
    return countDivs(g, g);
}

// ============================================================
// 7. GCD and LCM
// ============================================================
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int lcm(int a, int b) {
    return a / gcd(a, b) * b;
}

// ============================================================
// 8. Reverse value of an integer (e.g. 1234 -> 4321)
// ============================================================
int reverseInt(int n, int acc = 0) {
    if (n == 0) return acc;
    return reverseInt(n / 10, acc * 10 + n % 10);
}

// ============================================================
// 9. Reverse an array or string
// ============================================================
void reverseArray(int a[], int lo, int hi) {
    if (lo >= hi) return;
    swap(a[lo], a[hi]);
    reverseArray(a, lo + 1, hi - 1);
}

void reverseString(string& s, int lo, int hi) {
    if (lo >= hi) return;
    swap(s[lo], s[hi]);
    reverseString(s, lo + 1, hi - 1);
}

// ============================================================
// 10. Binary representation of an integer (as string)
// ============================================================
string toBinary(int n) {
    if (n == 0) return "0";
    if (n == 1) return "1";
    return toBinary(n / 2) + (char)('0' + n % 2);
}

// ============================================================
// 11. i-th Fibonacci number (F0=0, F1=1)
// ============================================================
long long fibonacci(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// ============================================================
// 12. Check if array or string is a palindrome
// ============================================================
bool isPalindromeArray(int a[], int lo, int hi) {
    if (lo >= hi) return true;
    if (a[lo] != a[hi]) return false;
    return isPalindromeArray(a, lo + 1, hi - 1);
}

bool isPalindromeString(const string& s, int lo, int hi) {
    if (lo >= hi) return true;
    if (s[lo] != s[hi]) return false;
    return isPalindromeString(s, lo + 1, hi - 1);
}

// ============================================================
// 13. * Generate all combinations of k elements from {1..n}
// ============================================================
void combinations(int n, int k, int start, vector<int>& current) {
    if ((int)current.size() == k) {
        cout << "{ ";
        for (int x : current) cout << x << " ";
        cout << "}\n";
        return;
    }
    for (int i = start; i <= n; i++) {
        current.push_back(i);
        combinations(n, k, i + 1, current);
        current.pop_back();
    }
}

// ============================================================
// 14. * Generate all permutations of n characters starting from 'A'
// ============================================================
void permutations(string& s, int start) {
    if (start == (int)s.size()) {
        cout << s << "\n";
        return;
    }
    for (int i = start; i < (int)s.size(); i++) {
        swap(s[start], s[i]);
        permutations(s, start + 1);
        swap(s[start], s[i]);
    }
}

// ============================================================
// 15. * Word break: check if string can be segmented using wordDict
// ============================================================
bool wordBreak(const string& s, int start, const unordered_set<string>& dict) {
    if (start == (int)s.size()) return true;
    for (int end = start + 1; end <= (int)s.size(); end++) {
        string word = s.substr(start, end - start);
        if (dict.count(word) && wordBreak(s, end, dict))
            return true;
    }
    return false;
}

// ============================================================
// Main - demo all exercises
// ============================================================
int main() {
    // 1. Sum
    cout << "1. sumN(10) = " << sumN(10) << "\n";

    // 2. Factorial
    cout << "2. factorial(6) = " << factorial(6) << "\n";

    // 3. Power
    cout << "3. power(2, 10) = " << power(2, 10) << "\n";

    // 4. Count digits
    cout << "4. countDigits(12345) = " << countDigits(12345) << "\n";

    // 5. All digits even
    cout << "5. allDigitsEven(2468) = " << (allDigitsEven(2468) ? "true" : "false") << "\n";
    cout << "   allDigitsEven(2461) = " << (allDigitsEven(2461) ? "true" : "false") << "\n";

    // 6. Common divisors
    cout << "6. countCommonDivisors(12, 18) = " << countCommonDivisors(12, 18) << "\n";

    // 7. GCD and LCM
    cout << "7. gcd(12, 18) = " << gcd(12, 18) << ", lcm(12, 18) = " << lcm(12, 18) << "\n";

    // 8. Reverse integer
    cout << "8. reverseInt(1234) = " << reverseInt(1234) << "\n";

    // 9. Reverse array and string
    int arr[] = {1, 2, 3, 4, 5};
    reverseArray(arr, 0, 4);
    cout << "9. reversed array: ";
    for (int x : arr) cout << x << " ";
    cout << "\n";
    string str = "hello";
    reverseString(str, 0, str.size() - 1);
    cout << "   reversed string: " << str << "\n";

    // 10. Binary
    cout << "10. toBinary(13) = " << toBinary(13) << "\n";

    // 11. Fibonacci
    cout << "11. fibonacci(10) = " << fibonacci(10) << "\n";

    // 12. Palindrome
    int parr[] = {1, 2, 3, 2, 1};
    cout << "12. isPalindromeArray({1,2,3,2,1}) = "
         << (isPalindromeArray(parr, 0, 4) ? "true" : "false") << "\n";
    cout << "    isPalindromeString(\"racecar\") = "
         << (isPalindromeString("racecar", 0, 6) ? "true" : "false") << "\n";

    // 13. Combinations
    cout << "13. combinations(4, 2):\n";
    vector<int> cur;
    combinations(4, 2, 1, cur);

    // 14. Permutations of "ABCD"
    cout << "14. permutations of \"ABCD\":\n";
    string perm = "ABCD";
    permutations(perm, 0);

    // 15. Word break
    string s = "datastructureandalgorithm";
    unordered_set<string> dict = {"algorithm", "and", "data", "structure"};
    cout << "15. wordBreak(\"" << s << "\") = "
         << (wordBreak(s, 0, dict) ? "true" : "false") << "\n";

    return 0;
}
