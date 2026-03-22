#include <iostream>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

// ============================================================
// SECTION 1: Binary Search Tree
// ============================================================
namespace BST {

struct NODE {
    int key;
    NODE* pLeft;
    NODE* pRight;
};

// 1. Create a new node
NODE* CreateNode(int data) {
    NODE* p = new NODE;
    p->key = data;
    p->pLeft = p->pRight = nullptr;
    return p;
}

// 2. Insert into BST
void Insert(NODE*& pRoot, int x) {
    if (!pRoot) { pRoot = CreateNode(x); return; }
    if (x < pRoot->key) Insert(pRoot->pLeft, x);
    else if (x > pRoot->key) Insert(pRoot->pRight, x);
    // duplicate keys are ignored
}

// 3. Pre-order (NLR)
void NLR(NODE* pRoot) {
    if (!pRoot) return;
    cout << pRoot->key << " ";
    NLR(pRoot->pLeft);
    NLR(pRoot->pRight);
}

// 4. In-order (LNR)
void LNR(NODE* pRoot) {
    if (!pRoot) return;
    LNR(pRoot->pLeft);
    cout << pRoot->key << " ";
    LNR(pRoot->pRight);
}

// 5. Post-order (LRN)
void LRN(NODE* pRoot) {
    if (!pRoot) return;
    LRN(pRoot->pLeft);
    LRN(pRoot->pRight);
    cout << pRoot->key << " ";
}

// 6. Level-order traversal
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

// 7. Height of tree
int Height(NODE* pRoot) {
    if (!pRoot) return -1;
    return 1 + max(Height(pRoot->pLeft), Height(pRoot->pRight));
}

// 8. Count nodes
int CountNode(NODE* pRoot) {
    if (!pRoot) return 0;
    return 1 + CountNode(pRoot->pLeft) + CountNode(pRoot->pRight);
}

// 9. Sum of all node values
int SumNode(NODE* pRoot) {
    if (!pRoot) return 0;
    return pRoot->key + SumNode(pRoot->pLeft) + SumNode(pRoot->pRight);
}

// 10. Search for a node
NODE* Search(NODE* pRoot, int x) {
    if (!pRoot || pRoot->key == x) return pRoot;
    if (x < pRoot->key) return Search(pRoot->pLeft, x);
    return Search(pRoot->pRight, x);
}

// 11. Remove a node from BST
void Remove(NODE*& pRoot, int x) {
    if (!pRoot) return;
    if (x < pRoot->key) {
        Remove(pRoot->pLeft, x);
    } else if (x > pRoot->key) {
        Remove(pRoot->pRight, x);
    } else {
        // Node found
        if (!pRoot->pLeft) {
            NODE* tmp = pRoot->pRight;
            delete pRoot;
            pRoot = tmp;
        } else if (!pRoot->pRight) {
            NODE* tmp = pRoot->pLeft;
            delete pRoot;
            pRoot = tmp;
        } else {
            // Find in-order successor (leftmost in right subtree)
            NODE* successor = pRoot->pRight;
            while (successor->pLeft) successor = successor->pLeft;
            pRoot->key = successor->key;
            Remove(pRoot->pRight, successor->key);
        }
    }
}

// 12. Create BST from array
NODE* CreateTree(int a[], int n) {
    NODE* root = nullptr;
    for (int i = 0; i < n; i++) Insert(root, a[i]);
    return root;
}

// 13. Remove entire tree (free memory)
void RemoveTree(NODE*& pRoot) {
    if (!pRoot) return;
    RemoveTree(pRoot->pLeft);
    RemoveTree(pRoot->pRight);
    delete pRoot;
    pRoot = nullptr;
}

// 14. Height of a specific node (return -1 if not found)
int HeightNode(NODE* pRoot, int value) {
    NODE* target = Search(pRoot, value);
    if (!target) return -1;
    return Height(target);
}

// 15. * Level of a specific node (root = 0, return -1 if not found)
int Level(NODE* pRoot, NODE* p, int level = 0) {
    if (!pRoot) return -1;
    if (pRoot == p) return level;
    int left = Level(pRoot->pLeft, p, level + 1);
    if (left != -1) return left;
    return Level(pRoot->pRight, p, level + 1);
}

// 16. * Count leaves
int CountLeaf(NODE* pRoot) {
    if (!pRoot) return 0;
    if (!pRoot->pLeft && !pRoot->pRight) return 1;
    return CountLeaf(pRoot->pLeft) + CountLeaf(pRoot->pRight);
}

// 17. * Count nodes with key < x
int CountLess(NODE* pRoot, int x) {
    if (!pRoot) return 0;
    if (pRoot->key >= x) return CountLess(pRoot->pLeft, x);
    return 1 + CountLess(pRoot->pLeft, x) + CountLess(pRoot->pRight, x);
}

// 18. * Count nodes with key > x
int CountGreater(NODE* pRoot, int x) {
    if (!pRoot) return 0;
    if (pRoot->key <= x) return CountGreater(pRoot->pRight, x);
    return 1 + CountGreater(pRoot->pLeft, x) + CountGreater(pRoot->pRight, x);
}

// 19. * Check if Binary Tree is a BST
bool IsBST(NODE* pRoot, int minVal = INT_MIN, int maxVal = INT_MAX) {
    if (!pRoot) return true;
    if (pRoot->key <= minVal || pRoot->key >= maxVal) return false;
    return IsBST(pRoot->pLeft, minVal, pRoot->key) &&
           IsBST(pRoot->pRight, pRoot->key, maxVal);
}

// 20. * Check if BST is a Full BST (every node has 0 or 2 children)
bool IsFullBST(NODE* pRoot) {
    if (!pRoot) return true;
    if (!pRoot->pLeft && !pRoot->pRight) return true;
    if (pRoot->pLeft && pRoot->pRight)
        return IsFullBST(pRoot->pLeft) && IsFullBST(pRoot->pRight);
    return false;
}

} // namespace BST


// ============================================================
// SECTION 2: AVL Tree
// ============================================================
namespace AVL {

struct NODE {
    int key;
    NODE* pLeft;
    NODE* pRight;
    int height;
};

// Helper: get height of a node
int getHeight(NODE* p) { return p ? p->height : -1; }

// Helper: update height
void updateHeight(NODE* p) {
    if (p) p->height = 1 + max(getHeight(p->pLeft), getHeight(p->pRight));
}

// Helper: balance factor
int balanceFactor(NODE* p) {
    return p ? getHeight(p->pLeft) - getHeight(p->pRight) : 0;
}

// 1. Create a new node
NODE* CreateNode(int data) {
    NODE* p = new NODE;
    p->key = data;
    p->pLeft = p->pRight = nullptr;
    p->height = 0;
    return p;
}

// Rotations
NODE* rotateRight(NODE* y) {
    NODE* x = y->pLeft;
    NODE* T2 = x->pRight;
    x->pRight = y;
    y->pLeft = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}

NODE* rotateLeft(NODE* x) {
    NODE* y = x->pRight;
    NODE* T2 = y->pLeft;
    y->pLeft = x;
    x->pRight = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}

NODE* balance(NODE* p) {
    updateHeight(p);
    int bf = balanceFactor(p);

    // Left heavy
    if (bf > 1) {
        if (balanceFactor(p->pLeft) < 0)
            p->pLeft = rotateLeft(p->pLeft); // Left-Right
        return rotateRight(p);
    }
    // Right heavy
    if (bf < -1) {
        if (balanceFactor(p->pRight) > 0)
            p->pRight = rotateRight(p->pRight); // Right-Left
        return rotateLeft(p);
    }
    return p;
}

// 2. Insert into AVL tree
NODE* insertHelper(NODE* p, int x, bool& inserted) {
    if (!p) { inserted = true; return CreateNode(x); }
    if (x < p->key)      p->pLeft  = insertHelper(p->pLeft,  x, inserted);
    else if (x > p->key) p->pRight = insertHelper(p->pRight, x, inserted);
    else { inserted = false; return p; } // duplicate
    return balance(p);
}

void Insert(NODE*& pRoot, int x) {
    bool inserted = false;
    pRoot = insertHelper(pRoot, x, inserted);
    if (!inserted) cout << "Value " << x << " already exists in AVL tree.\n";
}

// Helper for Remove: find minimum in subtree
NODE* findMin(NODE* p) {
    while (p->pLeft) p = p->pLeft;
    return p;
}

// 3. Remove from AVL tree
NODE* removeHelper(NODE* p, int x, bool& removed) {
    if (!p) { removed = false; return nullptr; }
    if (x < p->key)      p->pLeft  = removeHelper(p->pLeft,  x, removed);
    else if (x > p->key) p->pRight = removeHelper(p->pRight, x, removed);
    else {
        removed = true;
        if (!p->pLeft) {
            NODE* tmp = p->pRight;
            delete p;
            return tmp;
        } else if (!p->pRight) {
            NODE* tmp = p->pLeft;
            delete p;
            return tmp;
        } else {
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

// 4. * Check if a Binary Tree is a valid AVL Tree
bool IsAVL(NODE* pRoot) {
    if (!pRoot) return true;
    int bf = balanceFactor(pRoot);
    if (bf < -1 || bf > 1) return false;
    return IsAVL(pRoot->pLeft) && IsAVL(pRoot->pRight);
}

// Helper: in-order print for demo
void LNR(NODE* pRoot) {
    if (!pRoot) return;
    LNR(pRoot->pLeft);
    cout << pRoot->key << " ";
    LNR(pRoot->pRight);
}

} // namespace AVL


// ============================================================
// Main - demo
// ============================================================
int main() {
    // --- BST Demo ---
    cout << "=== BST ===\n";
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
    cout << "HeightNode(99): " << BST::HeightNode(bstRoot, 99) << "\n";

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
    cout << "After RemoveTree, root is " << (bstRoot ? "not null" : "null") << "\n";

    // --- AVL Demo ---
    cout << "\n=== AVL ===\n";
    AVL::NODE* avlRoot = nullptr;
    int avlArr[] = {10, 20, 30, 40, 50, 25};
    for (int x : avlArr) AVL::Insert(avlRoot, x);
    cout << "LNR (sorted): "; AVL::LNR(avlRoot); cout << "\n";
    cout << "IsAVL: " << (AVL::IsAVL(avlRoot) ? "true" : "false") << "\n";

    AVL::Insert(avlRoot, 20); // duplicate test
    AVL::Remove(avlRoot, 30);
    cout << "After Remove(30) LNR: "; AVL::LNR(avlRoot); cout << "\n";
    AVL::Remove(avlRoot, 99); // not found test

    return 0;
}
