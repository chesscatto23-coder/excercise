#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <unordered_set>
using namespace std;

// ============================================================
// LAB 05 - Recursion
// ============================================================

int sumN(int n) {
    if (n <= 0) return 0;
    return n + sumN(n - 1);
}

long long factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

double power(double x, int n) {
    if (n == 0) return 1;
    if (n < 0) return 1.0 / power(x, -n);
    if (n % 2 == 0) {
        double half = power(x, n / 2);
        return half * half;
    }
    return x * power(x, n - 1);
}

int countDigits(int n) {
    if (n < 0) n = -n;
    if (n < 10) return 1;
    return 1 + countDigits(n / 10);
}

bool allDigitsEven(int n) {
    if (n < 0) n = -n;
    if (n % 2 != 0) return false;
    if (n < 10) return true;
    return allDigitsEven(n / 10);
}

int gcdHelper(int a, int b) {
    return b == 0 ? a : gcdHelper(b, a % b);
}

int countCommonDivisors(int a, int b) {
    int g = gcdHelper(a, b);
    function<int(int, int)> countDivs = [&](int num, int k) -> int {
        if (k == 0) return 0;
        return (num % k == 0 ? 1 : 0) + countDivs(num, k - 1);
    };
    return countDivs(g, g);
}

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int lcm(int a, int b) {
    return a / gcd(a, b) * b;
}

int reverseInt(int n, int acc = 0) {
    if (n == 0) return acc;
    return reverseInt(n / 10, acc * 10 + n % 10);
}

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

string toBinary(int n) {
    if (n == 0) return "0";
    if (n == 1) return "1";
    return toBinary(n / 2) + (char)('0' + n % 2);
}

long long fibonacci(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

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

bool wordBreak(const string& s, int start, const unordered_set<string>& dict) {
    if (start == (int)s.size()) return true;
    for (int end = start + 1; end <= (int)s.size(); end++) {
        string word = s.substr(start, end - start);
        if (dict.count(word) && wordBreak(s, end, dict))
            return true;
    }
    return false;
}

void demo_lab05() {
    cout << "=== LAB 05 - Recursion ===\n";
    cout << "1. sumN(10) = " << sumN(10) << "\n";
    cout << "2. factorial(6) = " << factorial(6) << "\n";
    cout << "3. power(2, 10) = " << power(2, 10) << "\n";
    cout << "4. countDigits(12345) = " << countDigits(12345) << "\n";
    cout << "5. allDigitsEven(2468) = " << (allDigitsEven(2468) ? "true" : "false") << "\n";
    cout << "   allDigitsEven(2461) = " << (allDigitsEven(2461) ? "true" : "false") << "\n";
    cout << "6. countCommonDivisors(12, 18) = " << countCommonDivisors(12, 18) << "\n";
    cout << "7. gcd(12, 18) = " << gcd(12, 18) << ", lcm(12, 18) = " << lcm(12, 18) << "\n";
    cout << "8. reverseInt(1234) = " << reverseInt(1234) << "\n";
    int arr[] = {1, 2, 3, 4, 5};
    reverseArray(arr, 0, 4);
    cout << "9. reversed array: ";
    for (int x : arr) cout << x << " ";
    cout << "\n";
    string str = "hello";
    reverseString(str, 0, str.size() - 1);
    cout << "   reversed string: " << str << "\n";
    cout << "10. toBinary(13) = " << toBinary(13) << "\n";
    cout << "11. fibonacci(10) = " << fibonacci(10) << "\n";
    int parr[] = {1, 2, 3, 2, 1};
    cout << "12. isPalindromeArray({1,2,3,2,1}) = "
         << (isPalindromeArray(parr, 0, 4) ? "true" : "false") << "\n";
    cout << "    isPalindromeString(\"racecar\") = "
         << (isPalindromeString("racecar", 0, 6) ? "true" : "false") << "\n";
    cout << "13. combinations(4, 2):\n";
    vector<int> cur;
    combinations(4, 2, 1, cur);
    cout << "14. permutations of \"ABCD\":\n";
    string perm = "ABCD";
    permutations(perm, 0);
    string ws = "datastructureandalgorithm";
    unordered_set<string> dict = {"algorithm", "and", "data", "structure"};
    cout << "15. wordBreak(\"" << ws << "\") = "
         << (wordBreak(ws, 0, dict) ? "true" : "false") << "\n";
}


// ============================================================
// LAB 06 - BST & AVL (Integer)
// ============================================================

namespace BST {

struct NODE {
    int key;
    NODE* pLeft;
    NODE* pRight;
};

NODE* CreateNode(int data) {
    NODE* p = new NODE;
    p->key = data;
    p->pLeft = p->pRight = nullptr;
    return p;
}

void Insert(NODE*& pRoot, int x) {
    if (!pRoot) { pRoot = CreateNode(x); return; }
    if (x < pRoot->key) Insert(pRoot->pLeft, x);
    else if (x > pRoot->key) Insert(pRoot->pRight, x);
}

void NLR(NODE* pRoot) {
    if (!pRoot) return;
    cout << pRoot->key << " ";
    NLR(pRoot->pLeft);
    NLR(pRoot->pRight);
}

void LNR(NODE* pRoot) {
    if (!pRoot) return;
    LNR(pRoot->pLeft);
    cout << pRoot->key << " ";
    LNR(pRoot->pRight);
}

void LRN(NODE* pRoot) {
    if (!pRoot) return;
    LRN(pRoot->pLeft);
    LRN(pRoot->pRight);
    cout << pRoot->key << " ";
}

void LevelOrder(NODE* pRoot) {
    if (!pRoot) return;
    queue<NODE*> q;
    q.push(pRoot);
    while (!q.empty()) {
        NODE* cur = q.front(); q.pop();
        cout << cur->key << " ";
        if (cur->pLeft)  q.push(cur->pLeft);
        if (cur->pRight) q.push(cur->pRight);
    }
}

int Height(NODE* pRoot) {
    if (!pRoot) return -1;
    return 1 + max(Height(pRoot->pLeft), Height(pRoot->pRight));
}

int CountNode(NODE* pRoot) {
    if (!pRoot) return 0;
    return 1 + CountNode(pRoot->pLeft) + CountNode(pRoot->pRight);
}

int SumNode(NODE* pRoot) {
    if (!pRoot) return 0;
    return pRoot->key + SumNode(pRoot->pLeft) + SumNode(pRoot->pRight);
}

NODE* Search(NODE* pRoot, int x) {
    if (!pRoot || pRoot->key == x) return pRoot;
    if (x < pRoot->key) return Search(pRoot->pLeft, x);
    return Search(pRoot->pRight, x);
}

void Remove(NODE*& pRoot, int x) {
    if (!pRoot) return;
    if (x < pRoot->key) {
        Remove(pRoot->pLeft, x);
    } else if (x > pRoot->key) {
        Remove(pRoot->pRight, x);
    } else {
        if (!pRoot->pLeft) {
            NODE* tmp = pRoot->pRight; delete pRoot; pRoot = tmp;
        } else if (!pRoot->pRight) {
            NODE* tmp = pRoot->pLeft; delete pRoot; pRoot = tmp;
        } else {
            NODE* successor = pRoot->pRight;
            while (successor->pLeft) successor = successor->pLeft;
            pRoot->key = successor->key;
            Remove(pRoot->pRight, successor->key);
        }
    }
}

NODE* CreateTree(int a[], int n) {
    NODE* root = nullptr;
    for (int i = 0; i < n; i++) Insert(root, a[i]);
    return root;
}

void RemoveTree(NODE*& pRoot) {
    if (!pRoot) return;
    RemoveTree(pRoot->pLeft);
    RemoveTree(pRoot->pRight);
    delete pRoot;
    pRoot = nullptr;
}

int HeightNode(NODE* pRoot, int value) {
    NODE* target = Search(pRoot, value);
    if (!target) return -1;
    return Height(target);
}

int Level(NODE* pRoot, NODE* p, int level = 0) {
    if (!pRoot) return -1;
    if (pRoot == p) return level;
    int left = Level(pRoot->pLeft, p, level + 1);
    if (left != -1) return left;
    return Level(pRoot->pRight, p, level + 1);
}

int CountLeaf(NODE* pRoot) {
    if (!pRoot) return 0;
    if (!pRoot->pLeft && !pRoot->pRight) return 1;
    return CountLeaf(pRoot->pLeft) + CountLeaf(pRoot->pRight);
}

int CountLess(NODE* pRoot, int x) {
    if (!pRoot) return 0;
    if (pRoot->key >= x) return CountLess(pRoot->pLeft, x);
    return 1 + CountLess(pRoot->pLeft, x) + CountLess(pRoot->pRight, x);
}

int CountGreater(NODE* pRoot, int x) {
    if (!pRoot) return 0;
    if (pRoot->key <= x) return CountGreater(pRoot->pRight, x);
    return 1 + CountGreater(pRoot->pLeft, x) + CountGreater(pRoot->pRight, x);
}

bool IsBST(NODE* pRoot, int minVal = INT_MIN, int maxVal = INT_MAX) {
    if (!pRoot) return true;
    if (pRoot->key <= minVal || pRoot->key >= maxVal) return false;
    return IsBST(pRoot->pLeft, minVal, pRoot->key) &&
           IsBST(pRoot->pRight, pRoot->key, maxVal);
}

bool IsFullBST(NODE* pRoot) {
    if (!pRoot) return true;
    if (!pRoot->pLeft && !pRoot->pRight) return true;
    if (pRoot->pLeft && pRoot->pRight)
        return IsFullBST(pRoot->pLeft) && IsFullBST(pRoot->pRight);
    return false;
}

} // namespace BST


namespace AVL {

struct NODE {
    int key;
    NODE* pLeft;
    NODE* pRight;
    int height;
};

int getHeight(NODE* p) { return p ? p->height : -1; }

void updateHeight(NODE* p) {
    if (p) p->height = 1 + max(getHeight(p->pLeft), getHeight(p->pRight));
}

int balanceFactor(NODE* p) {
    return p ? getHeight(p->pLeft) - getHeight(p->pRight) : 0;
}

NODE* CreateNode(int data) {
    NODE* p = new NODE;
    p->key = data;
    p->pLeft = p->pRight = nullptr;
    p->height = 0;
    return p;
}

NODE* rotateRight(NODE* y) {
    NODE* x = y->pLeft; NODE* T2 = x->pRight;
    x->pRight = y; y->pLeft = T2;
    updateHeight(y); updateHeight(x);
    return x;
}

NODE* rotateLeft(NODE* x) {
    NODE* y = x->pRight; NODE* T2 = y->pLeft;
    y->pLeft = x; x->pRight = T2;
    updateHeight(x); updateHeight(y);
    return y;
}

NODE* balance(NODE* p) {
    updateHeight(p);
    int bf = balanceFactor(p);
    if (bf > 1) {
        if (balanceFactor(p->pLeft) < 0) p->pLeft = rotateLeft(p->pLeft);
        return rotateRight(p);
    }
    if (bf < -1) {
        if (balanceFactor(p->pRight) > 0) p->pRight = rotateRight(p->pRight);
        return rotateLeft(p);
    }
    return p;
}

NODE* insertHelper(NODE* p, int x, bool& inserted) {
    if (!p) { inserted = true; return CreateNode(x); }
    if (x < p->key)      p->pLeft  = insertHelper(p->pLeft,  x, inserted);
    else if (x > p->key) p->pRight = insertHelper(p->pRight, x, inserted);
    else { inserted = false; return p; }
    return balance(p);
}

void Insert(NODE*& pRoot, int x) {
    bool inserted = false;
    pRoot = insertHelper(pRoot, x, inserted);
    if (!inserted) cout << "Value " << x << " already exists in AVL tree.\n";
}

NODE* findMin(NODE* p) {
    while (p->pLeft) p = p->pLeft;
    return p;
}

NODE* removeHelper(NODE* p, int x, bool& removed) {
    if (!p) { removed = false; return nullptr; }
    if (x < p->key)      p->pLeft  = removeHelper(p->pLeft,  x, removed);
    else if (x > p->key) p->pRight = removeHelper(p->pRight, x, removed);
    else {
        removed = true;
        if (!p->pLeft) { NODE* tmp = p->pRight; delete p; return tmp; }
        else if (!p->pRight) { NODE* tmp = p->pLeft; delete p; return tmp; }
        else {
            NODE* successor = findMin(p->pRight);
            p->key = successor->key;
            bool dummy = false;
            p->pRight = removeHelper(p->pRight, successor->key, dummy);
        }
    }
    return balance(p);
}

void Remove(NODE*& pRoot, int x) {
    bool removed = false;
    pRoot = removeHelper(pRoot, x, removed);
    if (!removed) cout << "Value " << x << " does not exist in AVL tree.\n";
}

bool IsAVL(NODE* pRoot) {
    if (!pRoot) return true;
    int bf = balanceFactor(pRoot);
    if (bf < -1 || bf > 1) return false;
    return IsAVL(pRoot->pLeft) && IsAVL(pRoot->pRight);
}

void LNR(NODE* pRoot) {
    if (!pRoot) return;
    LNR(pRoot->pLeft);
    cout << pRoot->key << " ";
    LNR(pRoot->pRight);
}

} // namespace AVL


void demo_lab06() {
    cout << "\n=== LAB 06 - BST & AVL (Integer) ===\n";
    int arr[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(arr) / sizeof(arr[0]);
    BST::NODE* bstRoot = BST::CreateTree(arr, n);

    cout << "NLR:        "; BST::NLR(bstRoot);        cout << "\n";
    cout << "LNR:        "; BST::LNR(bstRoot);        cout << "\n";
    cout << "LRN:        "; BST::LRN(bstRoot);        cout << "\n";
    cout << "LevelOrder: "; BST::LevelOrder(bstRoot); cout << "\n";
    cout << "Height:     " << BST::Height(bstRoot)     << "\n";
    cout << "CountNode:  " << BST::CountNode(bstRoot)  << "\n";
    cout << "SumNode:    " << BST::SumNode(bstRoot)    << "\n";
    cout << "Search(40): " << (BST::Search(bstRoot, 40) ? "found" : "not found") << "\n";
    cout << "Search(99): " << (BST::Search(bstRoot, 99) ? "found" : "not found") << "\n";
    cout << "HeightNode(30): " << BST::HeightNode(bstRoot, 30) << "\n";
    BST::NODE* node40 = BST::Search(bstRoot, 40);
    cout << "Level(40):  " << BST::Level(bstRoot, node40) << "\n";
    cout << "CountLeaf:  " << BST::CountLeaf(bstRoot)  << "\n";
    cout << "CountLess(50):    " << BST::CountLess(bstRoot, 50)    << "\n";
    cout << "CountGreater(50): " << BST::CountGreater(bstRoot, 50) << "\n";
    cout << "IsBST:      " << (BST::IsBST(bstRoot) ? "true" : "false") << "\n";
    cout << "IsFullBST:  " << (BST::IsFullBST(bstRoot) ? "true" : "false") << "\n";
    BST::Remove(bstRoot, 30);
    cout << "After Remove(30) LNR: "; BST::LNR(bstRoot); cout << "\n";
    BST::RemoveTree(bstRoot);

    cout << "\n--- AVL ---\n";
    AVL::NODE* avlRoot = nullptr;
    int avlArr[] = {10, 20, 30, 40, 50, 25};
    for (int x : avlArr) AVL::Insert(avlRoot, x);
    cout << "LNR (sorted): "; AVL::LNR(avlRoot); cout << "\n";
    cout << "IsAVL: " << (AVL::IsAVL(avlRoot) ? "true" : "false") << "\n";
    AVL::Insert(avlRoot, 20);
    AVL::Remove(avlRoot, 30);
    cout << "After Remove(30) LNR: "; AVL::LNR(avlRoot); cout << "\n";
}


// ============================================================
// LAB 06 CONT - BST & AVL (String)
// ============================================================

namespace StringBST {

struct NODE {
    string key;
    NODE* pLeft;
    NODE* pRight;
};

NODE* CreateNode(const string& data) {
    NODE* p = new NODE;
    p->key = data;
    p->pLeft = p->pRight = nullptr;
    return p;
}

void Insert(NODE*& pRoot, const string& x) {
    if (!pRoot) { pRoot = CreateNode(x); return; }
    if (x < pRoot->key)      Insert(pRoot->pLeft,  x);
    else if (x > pRoot->key) Insert(pRoot->pRight, x);
}

NODE* Search(NODE* pRoot, const string& x) {
    if (!pRoot || pRoot->key == x) return pRoot;
    if (x < pRoot->key) return Search(pRoot->pLeft,  x);
    return               Search(pRoot->pRight, x);
}

void Remove(NODE*& pRoot, const string& x) {
    if (!pRoot) return;
    if (x < pRoot->key) { Remove(pRoot->pLeft,  x); }
    else if (x > pRoot->key) { Remove(pRoot->pRight, x); }
    else {
        if (!pRoot->pLeft) { NODE* tmp = pRoot->pRight; delete pRoot; pRoot = tmp; }
        else if (!pRoot->pRight) { NODE* tmp = pRoot->pLeft; delete pRoot; pRoot = tmp; }
        else {
            NODE* succ = pRoot->pRight;
            while (succ->pLeft) succ = succ->pLeft;
            pRoot->key = succ->key;
            Remove(pRoot->pRight, succ->key);
        }
    }
}

void LNR(NODE* pRoot) {
    if (!pRoot) return;
    LNR(pRoot->pLeft);
    cout << "\"" << pRoot->key << "\" ";
    LNR(pRoot->pRight);
}

void LevelOrder(NODE* pRoot) {
    if (!pRoot) return;
    queue<NODE*> q;
    q.push(pRoot);
    while (!q.empty()) {
        NODE* cur = q.front(); q.pop();
        cout << "\"" << cur->key << "\" ";
        if (cur->pLeft)  q.push(cur->pLeft);
        if (cur->pRight) q.push(cur->pRight);
    }
}

int CountPrefix(NODE* pRoot, const string& prefix) {
    if (!pRoot) return 0;
    int match = (pRoot->key.substr(0, prefix.size()) == prefix) ? 1 : 0;
    return match + CountPrefix(pRoot->pLeft, prefix) + CountPrefix(pRoot->pRight, prefix);
}

string FindMin(NODE* pRoot) {
    if (!pRoot) return "";
    while (pRoot->pLeft) pRoot = pRoot->pLeft;
    return pRoot->key;
}

string FindMax(NODE* pRoot) {
    if (!pRoot) return "";
    while (pRoot->pRight) pRoot = pRoot->pRight;
    return pRoot->key;
}

int CountByLength(NODE* pRoot, int k) {
    if (!pRoot) return 0;
    int match = ((int)pRoot->key.size() == k) ? 1 : 0;
    return match + CountByLength(pRoot->pLeft, k) + CountByLength(pRoot->pRight, k);
}

void RangeQuery(NODE* pRoot, const string& lo, const string& hi, vector<string>& result) {
    if (!pRoot) return;
    if (pRoot->key > lo) RangeQuery(pRoot->pLeft,  lo, hi, result);
    if (pRoot->key >= lo && pRoot->key <= hi) result.push_back(pRoot->key);
    if (pRoot->key < hi) RangeQuery(pRoot->pRight, lo, hi, result);
}

string FindLongest(NODE* pRoot) {
    if (!pRoot) return "";
    string best = pRoot->key;
    string left  = FindLongest(pRoot->pLeft);
    string right = FindLongest(pRoot->pRight);
    if (left.size()  > best.size()) best = left;
    if (right.size() > best.size()) best = right;
    return best;
}

string FindShortest(NODE* pRoot) {
    if (!pRoot) return "";
    string best  = pRoot->key;
    string left  = FindShortest(pRoot->pLeft);
    string right = FindShortest(pRoot->pRight);
    if (!left.empty()  && left.size()  < best.size()) best = left;
    if (!right.empty() && right.size() < best.size()) best = right;
    return best;
}

void RemoveTree(NODE*& pRoot) {
    if (!pRoot) return;
    RemoveTree(pRoot->pLeft);
    RemoveTree(pRoot->pRight);
    delete pRoot;
    pRoot = nullptr;
}

} // namespace StringBST


namespace StringAVL {

struct NODE {
    string key;
    NODE* pLeft;
    NODE* pRight;
    int height;
};

int getHeight(NODE* p)  { return p ? p->height : -1; }
int balanceFactor(NODE* p) {
    return p ? getHeight(p->pLeft) - getHeight(p->pRight) : 0;
}
void updateHeight(NODE* p) {
    if (p) p->height = 1 + max(getHeight(p->pLeft), getHeight(p->pRight));
}

NODE* CreateNode(const string& data) {
    NODE* p = new NODE;
    p->key = data;
    p->pLeft = p->pRight = nullptr;
    p->height = 0;
    return p;
}

NODE* rotateRight(NODE* y) {
    NODE* x  = y->pLeft; NODE* T2 = x->pRight;
    x->pRight = y; y->pLeft = T2;
    updateHeight(y); updateHeight(x);
    return x;
}

NODE* rotateLeft(NODE* x) {
    NODE* y  = x->pRight; NODE* T2 = y->pLeft;
    y->pLeft = x; x->pRight = T2;
    updateHeight(x); updateHeight(y);
    return y;
}

NODE* balance(NODE* p) {
    updateHeight(p);
    int bf = balanceFactor(p);
    if (bf > 1) {
        if (balanceFactor(p->pLeft) < 0) p->pLeft = rotateLeft(p->pLeft);
        return rotateRight(p);
    }
    if (bf < -1) {
        if (balanceFactor(p->pRight) > 0) p->pRight = rotateRight(p->pRight);
        return rotateLeft(p);
    }
    return p;
}

NODE* insertHelper(NODE* p, const string& x, bool& inserted) {
    if (!p) { inserted = true; return CreateNode(x); }
    if      (x < p->key) p->pLeft  = insertHelper(p->pLeft,  x, inserted);
    else if (x > p->key) p->pRight = insertHelper(p->pRight, x, inserted);
    else { inserted = false; return p; }
    return balance(p);
}

void Insert(NODE*& pRoot, const string& x) {
    bool inserted = false;
    pRoot = insertHelper(pRoot, x, inserted);
    if (!inserted) cout << "\"" << x << "\" already exists in AVL tree.\n";
}

NODE* Search(NODE* pRoot, const string& x) {
    if (!pRoot || pRoot->key == x) return pRoot;
    if (x < pRoot->key) return Search(pRoot->pLeft,  x);
    return               Search(pRoot->pRight, x);
}

NODE* findMin(NODE* p) { while (p->pLeft) p = p->pLeft; return p; }

NODE* removeHelper(NODE* p, const string& x, bool& removed) {
    if (!p) { removed = false; return nullptr; }
    if      (x < p->key) p->pLeft  = removeHelper(p->pLeft,  x, removed);
    else if (x > p->key) p->pRight = removeHelper(p->pRight, x, removed);
    else {
        removed = true;
        if (!p->pLeft)  { NODE* tmp = p->pRight; delete p; return tmp; }
        if (!p->pRight) { NODE* tmp = p->pLeft;  delete p; return tmp; }
        NODE* succ = findMin(p->pRight);
        p->key = succ->key;
        bool dummy = false;
        p->pRight = removeHelper(p->pRight, succ->key, dummy);
    }
    return balance(p);
}

void Remove(NODE*& pRoot, const string& x) {
    bool removed = false;
    pRoot = removeHelper(pRoot, x, removed);
    if (!removed) cout << "\"" << x << "\" not found in AVL tree.\n";
}

void LNR(NODE* pRoot) {
    if (!pRoot) return;
    LNR(pRoot->pLeft);
    cout << "\"" << pRoot->key << "\" ";
    LNR(pRoot->pRight);
}

bool IsAVL(NODE* pRoot) {
    if (!pRoot) return true;
    if (abs(balanceFactor(pRoot)) > 1) return false;
    return IsAVL(pRoot->pLeft) && IsAVL(pRoot->pRight);
}

int CountPrefix(NODE* pRoot, const string& prefix) {
    if (!pRoot) return 0;
    int match = (pRoot->key.substr(0, prefix.size()) == prefix) ? 1 : 0;
    return match + CountPrefix(pRoot->pLeft, prefix) + CountPrefix(pRoot->pRight, prefix);
}

void ToSortedVector(NODE* pRoot, vector<string>& out) {
    if (!pRoot) return;
    ToSortedVector(pRoot->pLeft, out);
    out.push_back(pRoot->key);
    ToSortedVector(pRoot->pRight, out);
}

} // namespace StringAVL


void demo_lab06_cont() {
    cout << "\n=== LAB 06 CONT - BST & AVL (String) ===\n";
    StringBST::NODE* root = nullptr;
    vector<string> words = {"banana", "apple", "cherry", "date", "apricot",
                            "blueberry", "avocado", "coconut", "fig", "grape"};
    for (const string& w : words) StringBST::Insert(root, w);

    cout << "Sorted (LNR):      "; StringBST::LNR(root);        cout << "\n";
    cout << "Level-order:       "; StringBST::LevelOrder(root);  cout << "\n";
    cout << "Min:               \"" << StringBST::FindMin(root)  << "\"\n";
    cout << "Max:               \"" << StringBST::FindMax(root)  << "\"\n";
    cout << "Longest:           \"" << StringBST::FindLongest(root)  << "\"\n";
    cout << "Shortest:          \"" << StringBST::FindShortest(root) << "\"\n";
    cout << "Count prefix \"ap\": " << StringBST::CountPrefix(root, "ap") << "\n";
    cout << "Count length 6:    " << StringBST::CountByLength(root, 6) << "\n";
    cout << "Range [\"b\",\"d\"]:    ";
    vector<string> range;
    StringBST::RangeQuery(root, "b", "d", range);
    for (const string& s : range) cout << "\"" << s << "\" ";
    cout << "\n";
    StringBST::Remove(root, "cherry");
    cout << "After Remove \"cherry\" LNR: "; StringBST::LNR(root); cout << "\n";
    StringBST::RemoveTree(root);

    cout << "\n--- String AVL ---\n";
    StringAVL::NODE* avlRoot = nullptr;
    vector<string> avlWords = {"mango", "kiwi", "orange", "peach",
                                "pear", "plum", "lemon", "lime"};
    for (const string& w : avlWords) StringAVL::Insert(avlRoot, w);
    cout << "Sorted (LNR): "; StringAVL::LNR(avlRoot); cout << "\n";
    cout << "IsAVL: " << (StringAVL::IsAVL(avlRoot) ? "true" : "false") << "\n";
    cout << "Count prefix \"p\": " << StringAVL::CountPrefix(avlRoot, "p") << "\n";
    StringAVL::Insert(avlRoot, "kiwi");
    StringAVL::Remove(avlRoot, "peach");
    cout << "After Remove \"peach\" LNR: "; StringAVL::LNR(avlRoot); cout << "\n";
    cout << "Sorted vector: ";
    vector<string> sorted;
    StringAVL::ToSortedVector(avlRoot, sorted);
    for (const string& s : sorted) cout << "\"" << s << "\" ";
    cout << "\n";
}


// ============================================================
// SORT - Sorting Algorithms
// ============================================================

void selectionSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if (a[j] < a[minIdx]) minIdx = j;
        swap(a[i], a[minIdx]);
    }
}

void insertionSort(int a[], int n) {
    for (int i = 1; i < n; i++) {
        int key = a[i], j = i - 1;
        while (j >= 0 && a[j] > key) { a[j + 1] = a[j]; j--; }
        a[j + 1] = key;
    }
}

void shellSort(int a[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = a[i], j = i;
            while (j >= gap && a[j - gap] > temp) { a[j] = a[j - gap]; j -= gap; }
            a[j] = temp;
        }
    }
}

void bubbleSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; j++) {
            if (a[j] > a[j + 1]) { swap(a[j], a[j + 1]); swapped = true; }
        }
        if (!swapped) break;
    }
}

void heapify(int a[], int n, int i) {
    int largest = i, l = 2*i+1, r = 2*i+2;
    if (l < n && a[l] > a[largest]) largest = l;
    if (r < n && a[r] > a[largest]) largest = r;
    if (largest != i) { swap(a[i], a[largest]); heapify(a, n, largest); }
}

void heapSort(int a[], int n) {
    for (int i = n/2-1; i >= 0; i--) heapify(a, n, i);
    for (int i = n-1; i > 0; i--) { swap(a[0], a[i]); heapify(a, i, 0); }
}

void merge(int a[], int l, int m, int r) {
    int n1 = m-l+1, n2 = r-m;
    int* L = new int[n1]; int* R = new int[n2];
    for (int i = 0; i < n1; i++) L[i] = a[l+i];
    for (int i = 0; i < n2; i++) R[i] = a[m+1+i];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) a[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) a[k++] = L[i++];
    while (j < n2) a[k++] = R[j++];
    delete[] L; delete[] R;
}

void mergeSort(int a[], int l, int r) {
    if (l < r) { int m = l+(r-l)/2; mergeSort(a,l,m); mergeSort(a,m+1,r); merge(a,l,m,r); }
}
void mergeSort(int a[], int n) { mergeSort(a, 0, n-1); }

int partition(int a[], int l, int r) {
    int pivot = a[r], i = l-1;
    for (int j = l; j < r; j++) if (a[j] <= pivot) { i++; swap(a[i], a[j]); }
    swap(a[i+1], a[r]);
    return i+1;
}
void quickSort(int a[], int l, int r) {
    if (l < r) { int p = partition(a,l,r); quickSort(a,l,p-1); quickSort(a,p+1,r); }
}
void quickSort(int a[], int n) { quickSort(a, 0, n-1); }

void countingSortByDigit(int a[], int n, int exp) {
    int* output = new int[n]; int count[10] = {0};
    for (int i = 0; i < n; i++) count[(a[i]/exp)%10]++;
    for (int i = 1; i < 10; i++) count[i] += count[i-1];
    for (int i = n-1; i >= 0; i--) { output[count[(a[i]/exp)%10]-1] = a[i]; count[(a[i]/exp)%10]--; }
    for (int i = 0; i < n; i++) a[i] = output[i];
    delete[] output;
}

void radixSort(int a[], int n) {
    int maxVal = *max_element(a, a+n);
    for (int exp = 1; maxVal/exp > 0; exp *= 10) countingSortByDigit(a, n, exp);
}

void countingSort(int a[], int n) {
    int maxVal = *max_element(a, a+n), minVal = *min_element(a, a+n);
    int range = maxVal - minVal + 1;
    int* count = new int[range](); int* output = new int[n];
    for (int i = 0; i < n; i++) count[a[i]-minVal]++;
    for (int i = 1; i < range; i++) count[i] += count[i-1];
    for (int i = n-1; i >= 0; i--) { output[count[a[i]-minVal]-1] = a[i]; count[a[i]-minVal]--; }
    for (int i = 0; i < n; i++) a[i] = output[i];
    delete[] count; delete[] output;
}

void binaryInsertionSort(int a[], int n) {
    for (int i = 1; i < n; i++) {
        int key = a[i], lo = 0, hi = i-1;
        while (lo <= hi) { int mid = (lo+hi)/2; if (a[mid] > key) hi = mid-1; else lo = mid+1; }
        for (int j = i-1; j >= lo; j--) a[j+1] = a[j];
        a[lo] = key;
    }
}

void shakerSort(int a[], int n) {
    int left = 0, right = n-1;
    while (left < right) {
        for (int i = left; i < right; i++) if (a[i] > a[i+1]) swap(a[i], a[i+1]);
        right--;
        for (int i = right; i > left; i--) if (a[i] < a[i-1]) swap(a[i], a[i-1]);
        left++;
    }
}

void flashSort(int a[], int n) {
    if (n <= 1) return;
    int minVal = a[0], maxIdx = 0;
    for (int i = 1; i < n; i++) {
        if (a[i] < minVal) minVal = a[i];
        if (a[i] > a[maxIdx]) maxIdx = i;
    }
    if (a[maxIdx] == minVal) return;
    int m = max(1, (int)(0.45 * n));
    int* L = new int[m]();
    double c = (double)(m-1) / (a[maxIdx] - minVal);
    for (int i = 0; i < n; i++) L[(int)(c*(a[i]-minVal))]++;
    for (int k = 1; k < m; k++) L[k] += L[k-1];
    swap(a[maxIdx], a[0]);
    int j = 0, k = m-1, nmove = 0;
    while (nmove < n-1) {
        while (j > L[k]-1) { j++; k = (int)(c*(a[j]-minVal)); }
        int flash = a[j];
        while (j != L[k]) {
            k = (int)(c*(flash-minVal));
            int hold = a[L[k]-1]; a[L[k]-1] = flash; flash = hold;
            L[k]--; nmove++;
        }
    }
    delete[] L;
    for (int i = 1; i < n; i++) {
        int key = a[i], jj = i-1;
        while (jj >= 0 && a[jj] > key) { a[jj+1] = a[jj]; jj--; }
        a[jj+1] = key;
    }
}

void demo_sort() {
    cout << "\n=== SORT - Sorting Algorithms ===\n";
    auto printArr = [](int a[], int n) {
        for (int i = 0; i < n; i++) cout << a[i] << " "; cout << "\n";
    };
    int data[] = {64, 25, 12, 22, 11, 90, 3, 47};
    int n = sizeof(data) / sizeof(data[0]);
    int a[8];
    auto reset = [&]() { for (int i = 0; i < n; i++) a[i] = data[i]; };

    reset(); selectionSort(a, n);      cout << "Selection:        "; printArr(a, n);
    reset(); insertionSort(a, n);      cout << "Insertion:        "; printArr(a, n);
    reset(); shellSort(a, n);          cout << "Shell:            "; printArr(a, n);
    reset(); bubbleSort(a, n);         cout << "Bubble:           "; printArr(a, n);
    reset(); heapSort(a, n);           cout << "Heap:             "; printArr(a, n);
    reset(); mergeSort(a, n);          cout << "Merge:            "; printArr(a, n);
    reset(); quickSort(a, n);          cout << "Quick:            "; printArr(a, n);
    reset(); radixSort(a, n);          cout << "Radix:            "; printArr(a, n);
    reset(); countingSort(a, n);       cout << "Counting:         "; printArr(a, n);
    reset(); binaryInsertionSort(a,n); cout << "BinaryInsertion:  "; printArr(a, n);
    reset(); shakerSort(a, n);         cout << "Shaker:           "; printArr(a, n);
    reset(); flashSort(a, n);          cout << "Flash:            "; printArr(a, n);
}


// ============================================================
// Main
// ============================================================
int main() {
    demo_lab05();
    demo_lab06();
    demo_lab06_cont();
    demo_sort();
    return 0;
}
