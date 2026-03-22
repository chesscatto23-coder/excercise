#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// ============================================================
// SECTION 1: String Binary Search Tree
// ============================================================
namespace StringBST {

struct NODE {
    string key;
    NODE* pLeft;
    NODE* pRight;
};

// 1. Create a new node
NODE* CreateNode(const string& data) {
    NODE* p = new NODE;
    p->key = data;
    p->pLeft = p->pRight = nullptr;
    return p;
}

// 2. Insert a string into BST (lexicographic order)
void Insert(NODE*& pRoot, const string& x) {
    if (!pRoot) { pRoot = CreateNode(x); return; }
    if (x < pRoot->key)      Insert(pRoot->pLeft,  x);
    else if (x > pRoot->key) Insert(pRoot->pRight, x);
    // duplicates ignored
}

// 3. Search for a string — returns node or nullptr
NODE* Search(NODE* pRoot, const string& x) {
    if (!pRoot || pRoot->key == x) return pRoot;
    if (x < pRoot->key) return Search(pRoot->pLeft,  x);
    return               Search(pRoot->pRight, x);
}

// 4. Remove a string from BST
void Remove(NODE*& pRoot, const string& x) {
    if (!pRoot) return;
    if (x < pRoot->key) {
        Remove(pRoot->pLeft,  x);
    } else if (x > pRoot->key) {
        Remove(pRoot->pRight, x);
    } else {
        if (!pRoot->pLeft) {
            NODE* tmp = pRoot->pRight; delete pRoot; pRoot = tmp;
        } else if (!pRoot->pRight) {
            NODE* tmp = pRoot->pLeft;  delete pRoot; pRoot = tmp;
        } else {
            // In-order successor: leftmost of right subtree
            NODE* succ = pRoot->pRight;
            while (succ->pLeft) succ = succ->pLeft;
            pRoot->key = succ->key;
            Remove(pRoot->pRight, succ->key);
        }
    }
}

// 5. In-order traversal (prints strings in sorted order)
void LNR(NODE* pRoot) {
    if (!pRoot) return;
    LNR(pRoot->pLeft);
    cout << "\"" << pRoot->key << "\" ";
    LNR(pRoot->pRight);
}

// 6. Level-order traversal
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

// 7. Count strings that start with a given prefix
int CountPrefix(NODE* pRoot, const string& prefix) {
    if (!pRoot) return 0;
    int match = (pRoot->key.substr(0, prefix.size()) == prefix) ? 1 : 0;
    // Prune: if prefix < node key, answer can only be in left subtree or here
    // But since prefix matching isn't monotone we search both sides
    return match + CountPrefix(pRoot->pLeft, prefix) + CountPrefix(pRoot->pRight, prefix);
}

// 8. Find the lexicographically smallest string
string FindMin(NODE* pRoot) {
    if (!pRoot) return "";
    while (pRoot->pLeft) pRoot = pRoot->pLeft;
    return pRoot->key;
}

// 9. Find the lexicographically largest string
string FindMax(NODE* pRoot) {
    if (!pRoot) return "";
    while (pRoot->pRight) pRoot = pRoot->pRight;
    return pRoot->key;
}

// 10. Count strings whose length equals k
int CountByLength(NODE* pRoot, int k) {
    if (!pRoot) return 0;
    int match = ((int)pRoot->key.size() == k) ? 1 : 0;
    return match + CountByLength(pRoot->pLeft, k) + CountByLength(pRoot->pRight, k);
}

// 11. Collect all strings in lexicographic range [lo, hi] (inclusive)
void RangeQuery(NODE* pRoot, const string& lo, const string& hi, vector<string>& result) {
    if (!pRoot) return;
    if (pRoot->key > lo) RangeQuery(pRoot->pLeft,  lo, hi, result);
    if (pRoot->key >= lo && pRoot->key <= hi) result.push_back(pRoot->key);
    if (pRoot->key < hi) RangeQuery(pRoot->pRight, lo, hi, result);
}

// 12. Find the longest string in the tree
string FindLongest(NODE* pRoot) {
    if (!pRoot) return "";
    string best = pRoot->key;
    string left  = FindLongest(pRoot->pLeft);
    string right = FindLongest(pRoot->pRight);
    if (left.size()  > best.size()) best = left;
    if (right.size() > best.size()) best = right;
    return best;
}

// 13. Find the shortest string in the tree
string FindShortest(NODE* pRoot) {
    if (!pRoot) return "";
    string best  = pRoot->key;
    string left  = FindShortest(pRoot->pLeft);
    string right = FindShortest(pRoot->pRight);
    if (!left.empty()  && left.size()  < best.size()) best = left;
    if (!right.empty() && right.size() < best.size()) best = right;
    return best;
}

// 14. Free the entire tree
void RemoveTree(NODE*& pRoot) {
    if (!pRoot) return;
    RemoveTree(pRoot->pLeft);
    RemoveTree(pRoot->pRight);
    delete pRoot;
    pRoot = nullptr;
}

} // namespace StringBST


// ============================================================
// SECTION 2: String AVL Tree
// ============================================================
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

// 1. Create a new node
NODE* CreateNode(const string& data) {
    NODE* p = new NODE;
    p->key = data;
    p->pLeft = p->pRight = nullptr;
    p->height = 0;
    return p;
}

NODE* rotateRight(NODE* y) {
    NODE* x  = y->pLeft;
    NODE* T2 = x->pRight;
    x->pRight = y; y->pLeft = T2;
    updateHeight(y); updateHeight(x);
    return x;
}

NODE* rotateLeft(NODE* x) {
    NODE* y  = x->pRight;
    NODE* T2 = y->pLeft;
    y->pLeft = x; x->pRight = T2;
    updateHeight(x); updateHeight(y);
    return y;
}

NODE* balance(NODE* p) {
    updateHeight(p);
    int bf = balanceFactor(p);
    if (bf > 1) {
        if (balanceFactor(p->pLeft) < 0)
            p->pLeft = rotateLeft(p->pLeft);
        return rotateRight(p);
    }
    if (bf < -1) {
        if (balanceFactor(p->pRight) > 0)
            p->pRight = rotateRight(p->pRight);
        return rotateLeft(p);
    }
    return p;
}

// 2. Insert a string (notify on duplicate)
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

// 3. Search for a string
NODE* Search(NODE* pRoot, const string& x) {
    if (!pRoot || pRoot->key == x) return pRoot;
    if (x < pRoot->key) return Search(pRoot->pLeft,  x);
    return               Search(pRoot->pRight, x);
}

// 4. Remove a string (notify if not found)
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

// 5. In-order traversal
void LNR(NODE* pRoot) {
    if (!pRoot) return;
    LNR(pRoot->pLeft);
    cout << "\"" << pRoot->key << "\" ";
    LNR(pRoot->pRight);
}

// 6. Check if tree is a valid AVL tree
bool IsAVL(NODE* pRoot) {
    if (!pRoot) return true;
    if (abs(balanceFactor(pRoot)) > 1) return false;
    return IsAVL(pRoot->pLeft) && IsAVL(pRoot->pRight);
}

// 7. Count strings starting with a prefix
int CountPrefix(NODE* pRoot, const string& prefix) {
    if (!pRoot) return 0;
    int match = (pRoot->key.substr(0, prefix.size()) == prefix) ? 1 : 0;
    return match + CountPrefix(pRoot->pLeft, prefix) + CountPrefix(pRoot->pRight, prefix);
}

// 8. Collect all strings sorted (in-order into vector)
void ToSortedVector(NODE* pRoot, vector<string>& out) {
    if (!pRoot) return;
    ToSortedVector(pRoot->pLeft, out);
    out.push_back(pRoot->key);
    ToSortedVector(pRoot->pRight, out);
}

} // namespace StringAVL


// ============================================================
// Main - demo
// ============================================================
int main() {
    // --- String BST ---
    cout << "=== String BST ===\n";
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
    cout << "Search \"cherry\":   "
         << (StringBST::Search(root, "cherry") ? "found" : "not found") << "\n";
    cout << "Search \"mango\":    "
         << (StringBST::Search(root, "mango")  ? "found" : "not found") << "\n";

    cout << "Range [\"b\",\"d\"]:    ";
    vector<string> range;
    StringBST::RangeQuery(root, "b", "d", range);
    for (const string& s : range) cout << "\"" << s << "\" ";
    cout << "\n";

    StringBST::Remove(root, "cherry");
    cout << "After Remove \"cherry\" LNR: "; StringBST::LNR(root); cout << "\n";

    StringBST::RemoveTree(root);
    cout << "After RemoveTree, root is " << (root ? "not null" : "null") << "\n";

    // --- String AVL ---
    cout << "\n=== String AVL ===\n";
    StringAVL::NODE* avlRoot = nullptr;
    vector<string> avlWords = {"mango", "kiwi", "orange", "peach",
                                "pear", "plum", "lemon", "lime"};
    for (const string& w : avlWords) StringAVL::Insert(avlRoot, w);

    cout << "Sorted (LNR): "; StringAVL::LNR(avlRoot); cout << "\n";
    cout << "IsAVL: " << (StringAVL::IsAVL(avlRoot) ? "true" : "false") << "\n";
    cout << "Count prefix \"p\": " << StringAVL::CountPrefix(avlRoot, "p") << "\n";
    cout << "Search \"lime\":  "
         << (StringAVL::Search(avlRoot, "lime")  ? "found" : "not found") << "\n";
    cout << "Search \"grape\": "
         << (StringAVL::Search(avlRoot, "grape") ? "found" : "not found") << "\n";

    StringAVL::Insert(avlRoot, "kiwi");   // duplicate
    StringAVL::Remove(avlRoot, "peach");
    cout << "After Remove \"peach\" LNR: "; StringAVL::LNR(avlRoot); cout << "\n";
    cout << "IsAVL after remove: " << (StringAVL::IsAVL(avlRoot) ? "true" : "false") << "\n";
    StringAVL::Remove(avlRoot, "durian"); // not found

    cout << "\nSorted vector from AVL: ";
    vector<string> sorted;
    StringAVL::ToSortedVector(avlRoot, sorted);
    for (const string& s : sorted) cout << "\"" << s << "\" ";
    cout << "\n";

    return 0;
}
