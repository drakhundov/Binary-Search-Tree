#ifndef BST_H
#define BST_H

#include <vector>

struct BST_node {
    int data;
    BST_node *left, *right, *parent;

    BST_node(int data);
};

class BST {
public:
    BST();

    ~BST();

    BST_node *get_root() const;

    void insert(int data, bool use_recur = false);

    void remove(int item, bool use_recur = false);

    BST_node *find(int item, BST_node *node = nullptr) const;

    void inorderTrav(std::vector<BST_node *> &trav, BST_node *node) const;

    void preorderTrav(std::vector<BST_node *> &trav, BST_node *node) const;

    void postorderTrav(std::vector<BST_node *> &trav, BST_node *node) const;

    void rotateLeft(BST_node *x);

    void rotateRight(BST_node *x);

    BST_node *findMin(BST_node *node) const;

    BST_node *findMax(BST_node *node) const;

    int height(BST_node *node) const;

private:
    BST_node *root;

    void destroy(BST_node *node);

    void insertPtrMethod(int data);

    BST_node *insertRecurMethod(BST_node *node, int data);

    void removePtrMethod(BST_node *node, int item);

    BST_node *removeRecurMethod(BST_node *node, int item);
};

#endif
