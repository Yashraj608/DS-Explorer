#include<iostream>
#include "Trees.h"
#include <cmath>
#include<algorithm>
#include<queue>
using namespace std;

// ---------------- BinaryTree implementation ----------------

BinaryTree::BinaryTree() : root(nullptr) {}
BinaryTree::~BinaryTree() {
    // simple postorder delete to avoid leaks
    if (!root) return;
    std::queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* cur = q.front(); q.pop();
        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
        delete cur;
    }
}

void BinaryTree::insertRoot(int val) {
    Node* newNode = new Node(val);
    if (!root) { root = newNode; return; }
    // level-order insertion into first available position
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* cur = q.front(); q.pop();
        if (!cur->left) { cur->left = newNode; return; }
        else q.push(cur->left);
        if (!cur->right) { cur->right = newNode; return; }
        else q.push(cur->right);
    }
}

// recursives
void BinaryTree::inorderRec(Node* node) {
    if (!node) return;
    inorderRec(node->left);
    cout << node->data << " ";
    inorderRec(node->right);
}
void BinaryTree::preorderRec(Node* node) {
    if (!node) return;
    cout << node->data << " ";
    preorderRec(node->left);
    preorderRec(node->right);
}
void BinaryTree::postorderRec(Node* node) {
    if (!node) return;
    postorderRec(node->left);
    postorderRec(node->right);
    cout << node->data << " ";
}

void BinaryTree::inorder() { inorderRec(root); }
void BinaryTree::preorder() { preorderRec(root); }
void BinaryTree::postorder() { postorderRec(root); }

void BinaryTree::levelOrder() {
    if (!root) return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* cur = q.front(); q.pop();
        cout << cur->data << " ";
        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
}

int BinaryTree::heightRec(Node* node) {
    if (!node) return 0;
    return 1 + max(heightRec(node->left), heightRec(node->right));
}
int BinaryTree::height() { return heightRec(root); }

int BinaryTree::countNodesRec(Node* node) {
    if (!node) return 0;
    return 1 + countNodesRec(node->left) + countNodesRec(node->right);
}
int BinaryTree::countNodes() { return countNodesRec(root); }

int BinaryTree::countLeavesRec(Node* node) {
    if (!node) return 0;
    if (!node->left && !node->right) return 1;
    return countLeavesRec(node->left) + countLeavesRec(node->right);
}
int BinaryTree::countLeaves() { return countLeavesRec(root); }

void BinaryTree::mirror(Node* node) {
    if (!node) return;
    swap(node->left, node->right);
    mirror(node->left);
    mirror(node->right);
}
void BinaryTree::mirror() { mirror(root); }

// Level-order search for value in generic binary tree
bool BinaryTree::search(int val) {
    if (!root) return false;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* cur = q.front(); q.pop();
        if (cur->data == val) return true;
        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
    return false;
}

// Helper: find deepest node and its parent (used for delete)
Node* BinaryTree::getDeepestNode(Node*& parentOfDeepest) {
    parentOfDeepest = nullptr;
    if (!root) return nullptr;
    queue<Node*> q;
    q.push(root);
    Node* last = nullptr;
    Node* parent = nullptr;
    while (!q.empty()) {
        last = q.front(); q.pop();
        if (last->left) { parent = last; q.push(last->left); }
        if (last->right) { parent = last; q.push(last->right); }
    }
    parentOfDeepest = parent;
    return last;
}

Node* BinaryTree::findParent(Node* child) {
    if (!root || !child || root == child) return nullptr;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* cur = q.front(); q.pop();
        if (cur->left == child || cur->right == child) return cur;
        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
    return nullptr;
}

// delete value by replacing with deepest node (generic binary tree delete)
bool BinaryTree::deleteNode(int val) {
    if (!root) return false;
    // single node
    if (!root->left && !root->right) {
        if (root->data == val) { delete root; root = nullptr; return true; }
        return false;
    }

    queue<Node*> q;
    q.push(root);
    Node* keyNode = nullptr;
    while (!q.empty()) {
        Node* cur = q.front(); q.pop();
        if (cur->data == val) keyNode = cur;
        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }

    if (!keyNode) return false; // not found

    Node* parentOfDeepest = nullptr;
    Node* deepest = getDeepestNode(parentOfDeepest);
    if (!deepest) return false;

    // copy deepest value into keyNode then remove deepest
    keyNode->data = deepest->data;

    // remove deepest from parent
    if (parentOfDeepest) {
        if (parentOfDeepest->left == deepest) parentOfDeepest->left = nullptr;
        else if (parentOfDeepest->right == deepest) parentOfDeepest->right = nullptr;
    } else {
        // no parent => deepest was root
        root = nullptr;
    }
    delete deepest;
    return true;
}

// ---------------- BST implementation ----------------

BST::BST() : BinaryTree() {}
BST::~BST() { /* base destructor handles deletions */ }

void BST::insert(int val) {
    Node* newNode = new Node(val);
    if (!root) { root = newNode; return; }
    Node* cur = root;
    Node* parent = nullptr;
    while (cur) {
        parent = cur;
        if (val < cur->data) cur = cur->left;
        else cur = cur->right;
    }
    if (val < parent->data) parent->left = newNode;
    else parent->right = newNode;
}

Node* BST::search(int val) {
    Node* cur = root;
    while (cur) {
        if (cur->data == val) return cur;
        if (val < cur->data) cur = cur->left;
        else cur = cur->right;
    }
    return nullptr;
}

// BST delete: wrapper that calls recursive deleteRec
Node* BST::deleteRec(Node* node, int val) {
    if (!node) return nullptr;
    if (val < node->data) node->left = deleteRec(node->left, val);
    else if (val > node->data) node->right = deleteRec(node->right, val);
    else {
        // node to delete
        if (!node->left) {
            Node* temp = node->right; delete node; return temp;
        } else if (!node->right) {
            Node* temp = node->left; delete node; return temp;
        }
        //two children: get inorder successor
        Node* succ = node->right;
        while (succ && succ->left) succ = succ->left;
        node->data = succ->data;
        node->right = deleteRec(node->right, succ->data);
    }
    return node;
}

bool BST::deleteNode(int val) {
    if (!root) return false;
    if (!search(val)) return false;
    root = deleteRec(root, val);
    return true;
}

// ---------------- AVL implementation ----------------

AVL::AVL() : BST() {}
AVL::~AVL() { /* destructor inherited */ }

int AVL::nodeHeight(Node* n) {
    return n ? n->height : 0;
}

int AVL::getBalance(Node* n) {
    if (!n) return 0;
    return nodeHeight(n->left) - nodeHeight(n->right);
}

Node* AVL::rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = 1 + max(nodeHeight(y->left), nodeHeight(y->right));
    x->height = 1 + max(nodeHeight(x->left), nodeHeight(x->right));
    return x;
}

Node* AVL::leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = 1 + max(nodeHeight(x->left), nodeHeight(x->right));
    y->height = 1 + max(nodeHeight(y->left), nodeHeight(y->right));
    return y;
}

Node* AVL::insertRec(Node* node, int val) {
    if (!node) return new Node(val);
    if (val < node->data) node->left = insertRec(node->left, val);
    else if (val > node->data) node->right = insertRec(node->right, val);
    else return node; // duplicates ignored

    node->height = 1 + max(nodeHeight(node->left), nodeHeight(node->right));
    int balance = getBalance(node);

    // LL
    if (balance > 1 && val < node->left->data) return rightRotate(node);
    // RR
    if (balance < -1 && val > node->right->data) return leftRotate(node);
    // LR
    if (balance > 1 && val > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // RL
    if (balance < -1 && val < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

void AVL::insert(int val) {
    root = insertRec(root, val);
}

// AVL delete with balancing (recursive)
Node* AVL::deleteRec(Node* node, int val) {
    if (!node) return nullptr;
    if (val < node->data) node->left = deleteRec(node->left, val);
    else if (val > node->data) node->right = deleteRec(node->right, val);
    else {
        if (!node->left) { Node* tmp = node->right; delete node; return tmp; }
        else if (!node->right) { Node* tmp = node->left; delete node; return tmp; }
        Node* succ = node->right;
        while (succ->left) succ = succ->left;
        node->data = succ->data;
        node->right = deleteRec(node->right, succ->data);
    }
    if (!node) return node;

    node->height = 1 + max(nodeHeight(node->left), nodeHeight(node->right));
    int balance = getBalance(node);

    // balancing
    if (balance > 1 && getBalance(node->left) >= 0) return rightRotate(node);
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && getBalance(node->right) <= 0) return leftRotate(node);
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

bool AVL::deleteNode(int val) {
    if (!root) return false;
    if (!search(val)) return false;
    root = deleteRec(root, val);
    return true;
}

// ---------------- MaxHeap implementation ----------------

MaxHeap::MaxHeap() { a.clear(); }
MaxHeap::MaxHeap(int reserveSize) { a.clear(); a.reserve(reserveSize); }
MaxHeap::~MaxHeap() { /* vector cleans up */ }

void MaxHeap::heapifyUp(int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (a[parent] < a[idx]) { swap(a[parent], a[idx]); idx = parent; }
        else break;
    }
}
void MaxHeap::heapifyDown(int idx) {
    int n = (int)a.size();
    while (true) {
        int l = 2*idx + 1;
        int r = 2*idx + 2;
        int largest = idx;
        if (l < n && a[l] > a[largest]) largest = l;
        if (r < n && a[r] > a[largest]) largest = r;
        if (largest != idx) { swap(a[idx], a[largest]); idx = largest; }
        else break;
    }
}

void MaxHeap::insert(int val) {
    a.push_back(val);
    heapifyUp((int)a.size() - 1);
    cout << val << " inserted.\n";
}

void MaxHeap::deleteMax() {
    if (a.empty()) { cout << "Heap empty!\n"; return; }
    cout << "Deleted max: " << a.front() << "\n";
    a[0] = a.back(); a.pop_back();
    if (!a.empty()) heapifyDown(0);
}

bool MaxHeap::deleteValue(int val) {
    if (a.empty()) return false;
    int idx = -1;
    for (size_t i = 0; i < a.size(); ++i) if (a[i] == val) { idx = (int)i; break; }
    if (idx == -1) return false;
    a[idx] = a.back(); a.pop_back();
    if (idx < (int)a.size()) { heapifyDown(idx); heapifyUp(idx); }
    return true;
}

void MaxHeap::levelOrder() {
    for (int v : a) cout << v << " ";
}

int MaxHeap::height() {
    if (a.empty()) return 0;
    return (int)floor(log2((double)a.size())) + 1;
}
int MaxHeap::countNodes() { return (int)a.size(); }
int MaxHeap::countLeaves() {
    int n = (int)a.size();
    if (n == 0) return 0;
    int firstLeaf = n / 2;
    return n - firstLeaf;
}
// ------------------- Tree Menu -------------------

void treeMenu() {
    BinaryTree bt;
    BST bst;
    AVL avl;
    MaxHeap heap(100);

    int mainChoice = -1;
    int val;

    while (true) {
        cout << "\n========== TREE MENU ==========\n";
        cout << "1. Binary Tree\n";
        cout << "2. Binary Search Tree (BST)\n";
        cout << "3. AVL Tree\n";
        cout << "4. Max Heap\n";
        cout << "0. Back to Main Menu\n";
        cout << "================================\n";
        cout << "Enter your choice: ";
        cin >> mainChoice;

        if (mainChoice == 0) break;

        switch (mainChoice) {
            // ---------------- Binary Tree ----------------
            case 1: {
                int choice;
                while (true) {
                    cout << "\n--- Binary Tree ---\n";
                    cout << "1. Insert\n";
                    cout << "2. Delete Node\n";
                    cout << "3. Search Node\n";
                    cout << "4. Inorder Traversal\n";
                    cout << "5. Preorder Traversal\n";
                    cout << "6. Postorder Traversal\n";
                    cout << "7. Level Order Traversal\n";
                    cout << "8. Height / Count / Leaves\n";
                    cout << "9. Mirror Tree\n";
                    cout << "0. Back\n";
                    cout << "Choice: ";
                    cin >> choice;

                    if (choice == 0) break;

                    switch (choice) {
                        case 1:
                            cout << "Enter value: ";
                            cin >> val;
                            bt.insertRoot(val);
                            cout << "Inserted successfully.\n";
                            break;
                        case 2:
                            cout << "Enter value to delete: ";
                            cin >> val;
                            if (bt.deleteNode(val)) cout << "Deleted successfully.\n";
                            else cout << "Value not found.\n";
                            break;
                        case 3:
                            cout << "Enter value to search: ";
                            cin >> val;
                            cout << (bt.search(val) ? "Found.\n" : "Not Found.\n");
                            break;
                        case 4:
                            cout << "Inorder: "; bt.inorder(); cout << endl;
                            break;
                        case 5:
                            cout << "Preorder: "; bt.preorder(); cout << endl;
                            break;
                        case 6:
                            cout << "Postorder: "; bt.postorder(); cout << endl;
                            break;
                        case 7:
                            cout << "Level Order: "; bt.levelOrder(); cout << endl;
                            break;
                        case 8:
                            cout << "Height: " << bt.height() << endl;
                            cout << "Nodes: " << bt.countNodes() << endl;
                            cout << "Leaves: " << bt.countLeaves() << endl;
                            break;
                        case 9:
                            bt.mirror();
                            cout << "Tree mirrored.\n";
                            break;
                        default:
                            cout << "Invalid choice.\n";
                    }
                }
                break;
            }

            // ---------------- BST ----------------
            case 2: {
                int choice;
                while (true) {
                    cout << "\n--- Binary Search Tree ---\n";
                    cout << "1. Insert\n";
                    cout << "2. Delete\n";
                    cout << "3. Search\n";
                    cout << "4. Inorder\n";
                    cout << "5. Preorder\n";
                    cout << "6. Postorder\n";
                    cout << "7. Level Order\n";
                    cout << "0. Back\n";
                    cout << "Choice: ";
                    cin >> choice;

                    if (choice == 0) break;

                    switch (choice) {
                        case 1:
                            cout << "Enter value: ";
                            cin >> val;
                            bst.insert(val);
                            cout << "Inserted.\n";
                            break;
                        case 2:
                            cout << "Enter value to delete: ";
                            cin >> val;
                            if (bst.deleteNode(val)) cout << "Deleted.\n";
                            else cout << "Value not found.\n";
                            break;
                        case 3:
                            cout << "Enter value: ";
                            cin >> val;
                            cout << (bst.search(val) ? "Found.\n" : "Not Found.\n");
                            break;
                        case 4:
                            cout << "Inorder: "; bst.inorder(); cout << endl;
                            break;
                        case 5:
                            cout << "Preorder: "; bst.preorder(); cout << endl;
                            break;
                        case 6:
                            cout << "Postorder: "; bst.postorder(); cout << endl;
                            break;
                        case 7:
                            cout << "Level Order: "; bst.levelOrder(); cout << endl;
                            break;
                        default:
                            cout << "Invalid choice.\n";
                    }
                }
                break;
            }

            // ---------------- AVL ----------------
            case 3: {
                int choice;
                while (true) {
                    cout << "\n--- AVL Tree ---\n";
                    cout << "1. Insert\n";
                    cout << "2. Delete\n";
                    cout << "3. Search\n";
                    cout << "4. Inorder\n";
                    cout << "5. Preorder\n";
                    cout << "6. Postorder\n";
                    cout << "7. Level Order\n";
                    cout << "0. Back\n";
                    cout << "Choice: ";
                    cin >> choice;

                    if (choice == 0) break;

                    switch (choice) {
                        case 1:
                            cout << "Enter value: ";
                            cin >> val;
                            avl.insert(val);
                            cout << "Inserted.\n";
                            break;
                        case 2:
                            cout << "Enter value to delete: ";
                            cin >> val;
                            if (avl.deleteNode(val)) cout << "Deleted.\n";
                            else cout << "Value not found.\n";
                            break;
                        case 3:
                            cout << "Enter value: ";
                            cin >> val;
                            cout << (avl.search(val) ? "Found.\n" : "Not Found.\n");
                            break;
                        case 4:
                            cout << "Inorder: "; avl.inorder(); cout << endl;
                            break;
                        case 5:
                            cout << "Preorder: "; avl.preorder(); cout << endl;
                            break;
                        case 6:
                            cout << "Postorder: "; avl.postorder(); cout << endl;
                            break;
                        case 7:
                            cout << "Level Order: "; avl.levelOrder(); cout << endl;
                            break;
                        default:
                            cout << "Invalid choice.\n";
                    }
                }
                break;
            }

            // ---------------- Max Heap ----------------
            case 4: {
                int choice;
                while (true) {
                    cout << "\n--- Max Heap ---\n";
                    cout << "1. Insert\n";
                    cout << "2. Delete Max\n";
                    cout << "3. Delete Specific Value\n";
                    cout << "4. Display (Level Order)\n";
                    cout << "5. Height / Node Count / Leaf Count\n";
                    cout << "0. Back\n";
                    cout << "Choice: ";
                    cin >> choice;

                    if (choice == 0) break;

                    switch (choice) {
                        case 1:
                            cout << "Enter value: ";
                            cin >> val;
                            heap.insert(val);
                            break;
                        case 2:
                            heap.deleteMax();
                            break;
                        case 3:
                            cout << "Enter value to delete: ";
                            cin >> val;
                            if (heap.deleteValue(val)) cout << "Deleted.\n";
                            else cout << "Value not found.\n";
                            break;
                        case 4:
                            cout << "Heap elements: "; heap.levelOrder(); cout << endl;
                            break;
                        case 5:
                            cout << "Height: " << heap.height() << endl;
                            cout << "Nodes: " << heap.countNodes() << endl;
                            cout << "Leaves: " << heap.countLeaves() << endl;
                            break;
                        default:
                            cout << "Invalid choice.\n";
                    }
                }
                break;
            }

            default:
                cout << "Invalid main choice!\n";
        }
    }
}
