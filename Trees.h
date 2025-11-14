#ifndef TREES_H
#define TREES_H

#include <vector>
#include <queue>

struct Node {
    int data;
    Node* left;
    Node* right;
    int height;
    Node(int val) : data(val), left(nullptr), right(nullptr), height(1) {}
};

// ---------------- Binary Tree ----------------
class BinaryTree {
public:
    Node* root;
    BinaryTree();
    virtual ~BinaryTree();

    // insert first available position (level-order)
    void insertRoot(int val);

    // traversals (public simple wrappers)
    void inorder();
    void preorder();
    void postorder();
    void levelOrder();

    // utilities
    int height();
    int countNodes();
    int countLeaves();
    void mirror();

    // operations
    bool search(int val);
    bool deleteNode(int val);

protected:
    // recursive helpers (protected so derived classes can use)
    void inorderRec(Node* node);
    void preorderRec(Node* node);
    void postorderRec(Node* node);
    int heightRec(Node* node);
    int countNodesRec(Node* node);
    int countLeavesRec(Node* node);
    void mirror(Node* node);

    // helpers for delete
    Node* getDeepestNode(Node*& parentOfDeepest);
    Node* findParent(Node* child);
};

// ---------------- BST ----------------
class BST : public BinaryTree {
public:
    BST();
    virtual ~BST();

    // BST-style insert/search/delete
    void insert(int val);
    Node* search(int val);
    bool deleteNode(int val);         // public wrapper
protected:
    Node* deleteRec(Node* node, int val); // recursive helper for deletion
};

// ---------------- AVL ----------------
class AVL : public BST {
public:
    AVL();
    virtual ~AVL();

    // AVL insert/delete that maintain balance
    void insert(int val);
    bool deleteNode(int val);

protected:
    int nodeHeight(Node* n);
    int getBalance(Node* n);
    Node* rightRotate(Node* y);
    Node* leftRotate(Node* x);
    Node* insertRec(Node* node, int val);
    Node* deleteRec(Node* node, int val);
};

// ---------------- Max Heap ----------------
class MaxHeap {
public:
    MaxHeap();
    explicit MaxHeap(int reserveSize);
    ~MaxHeap();

    void insert(int val);
    void deleteMax();
    bool deleteValue(int val);
    void levelOrder(); // print stored array as level-order

    int height();
    int countNodes();
    int countLeaves();

private:
    std::vector<int> a;
    void heapifyUp(int idx);
    void heapifyDown(int idx);
};

/// Menu function exported for main program
void treeMenu();

#endif // TREES_H
