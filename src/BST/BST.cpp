#include "BST.h"

#include <iostream>

BST::BST() : root{nullptr} {
}

BST::~BST() {
    if (root != nullptr) {
        destroy(root);
    }
}

void BST::destroy(BST_node *node) {
    if (node->left != nullptr) {
        destroy(node->left);
    }
    if (node->right != nullptr) {
        destroy(node->right);
    }
    delete node;
}

BST_node *BST::get_root() const { return root; }

void BST::insert(int data, bool use_recur) {
    if (use_recur) {
        root = insertRecurMethod(root, data);
    } else {
        insertPtrMethod(data);
    }
}

void BST::insertPtrMethod(int data) {
    if (root == nullptr) {
        root = new BST_node{data};
        return;
    }
    BST_node *cur, *parent;
    bool leftChild;
    cur = root;
    while (cur != nullptr) {
        if (data > cur->data) {
            parent = cur;
            cur = cur->right;
            leftChild = false;
        } else if (data < cur->data) {
            parent = cur;
            cur = cur->left;
            leftChild = true;
        } else if (data == cur->data) {
            // ! This condition should be kept
            // ! since cur is not nullptr.
            throw std::runtime_error(
                "[BST::insertPtrMethod] value already in the binary tree");
        }
    }
    BST_node *new_leaf = new BST_node{data};
    new_leaf->parent = parent;
    if (leftChild) {
        parent->left = new_leaf;
    } else {
        parent->right = new_leaf;
    }
}

BST_node *BST::insertRecurMethod(BST_node *node, int data) {
    if (node == nullptr) {
        return new BST_node{data};
    }
    if (data > node->data) {
        node->right = insertRecurMethod(node->right, data);
        node->right->parent = node;
    } else if (data < node->data) {
        node->left = insertRecurMethod(node->left, data);
        node->left->parent = node;
    } else {
        //! data == node->data
        throw std::runtime_error(
            "[BST::insertRecurMethod] value already in the binary tree");
    }
    return node;
}

void BST::remove(int item, bool use_recur) {
    if (use_recur) {
        root = removeRecurMethod(root, item);
    } else {
        removePtrMethod(root, item);
    }
}

void BST::removePtrMethod(BST_node *node, int item) {
    BST_node *parent = nullptr, *cur = node;
    bool isLeftChild = false;
    while (cur != nullptr && cur->data != item) {
        parent = cur;
        if (item > cur->data) {
            cur = cur->right;
            isLeftChild = false;
        } else if (item < cur->data) {
            cur = cur->left;
            isLeftChild = true;
        }
    }
    if (cur == nullptr) {
        std::cerr << "Item not in the binary tree: " << item << std::endl;
    }
    // ! It works even if both left and right
    // ! nodes are NULL.
    BST_node *tmp;
    if (cur->left == nullptr) {
        tmp = cur->right;
    } else if (cur->right == nullptr) {
        tmp = cur->left;
    } else {
        tmp = findMin(cur->right);
        cur->data = tmp->data;
        removePtrMethod(cur->right, tmp->data);
    }
    delete cur;
    if (isLeftChild) {
        parent->left = tmp;
    } else {
        parent->right = tmp;
    }
    // ! If the item is in the BST,
    // ! it will be successfully
    // ! removed until here.
    return;
}

BST_node *BST::removeRecurMethod(BST_node *node, int data) {
    if (node == nullptr) {
        return node;
    }
    if (data > node->data) {
        node->right = removeRecurMethod(node->right, data);
    } else if (data < node->data) {
        node->left = removeRecurMethod(node->left, data);
    } else {
        BST_node *tmp = node;
        if (node->left == nullptr) {
            node = node->right;
            delete tmp;
        } else if (node->right == nullptr) {
            node = node->left;
            delete tmp;
        } else {
            // Both not NULL.
            tmp = findMin(node->right);
            node->data = tmp->data;
            node->right = removeRecurMethod(node->right, tmp->data);
        }
    }
    return node;
}

BST_node *BST::find(int item, BST_node *node) const {
    if (node == nullptr) {
        // Default value.
        node = root;
    }
    if (item > node->data) {
        return find(item, node->right);
    } else if (item < node->data) {
        return find(item, node->left);
    } else {
        return node;
    }
}

void BST::inorderTrav(std::vector<BST_node *> &trav, BST_node *node) const {
    if (node->left != nullptr) {
        inorderTrav(trav, node->left);
    }
    trav.push_back(node);
    if (node->right != nullptr) {
        inorderTrav(trav, node->right);
    }
}

void BST::preorderTrav(std::vector<BST_node *> &trav, BST_node *node) const {
    trav.push_back(node);
    if (node->left != nullptr) {
        preorderTrav(trav, node->left);
    }
    if (node->right != nullptr) {
        preorderTrav(trav, node->right);
    }
}

void BST::postorderTrav(std::vector<BST_node *> &trav, BST_node *node) const {
    if (node->left != nullptr) {
        postorderTrav(trav, node->left);
    }
    if (node->right != nullptr) {
        postorderTrav(trav, node->right);
    }
    trav.push_back(node);
}

BST_node *BST::findMin(BST_node *node) const {
    if (node == nullptr) {
        return nullptr;
    }
    if (node->left == nullptr) {
        return node;
    }
    return findMin(node->left);
}

BST_node *BST::findMax(BST_node *node) const {
    if (node == nullptr) {
        return nullptr;
    }
    if (node->right == nullptr) {
        return node;
    }
    return findMax(node->right);
}

int BST::height(BST_node *node) const {
    if (node == nullptr) {
        return 0;
    }
    return 1 + std::max(height(node->left), height(node->right));
}

void BST::rotateLeft(BST_node *x) {
    BST_node *y = x->right, *p = x->parent;
    if (y == nullptr) {
        std::invalid_argument("[BST::rotateLeft] cannot rotate left: right child is null");
    }
    x->right = y->left;
    if (y->left) y->left->parent = x;
    y->left = x;
    x->parent = y;
    if (root == x) {
        this->root = y;
        return;
    }
    if (x == p->left) {
        p->left = y;
    } else {
        // x == p->right
        p->right = y;
    }
    y->parent = p;
}

void BST::rotateRight(BST_node *x) {
    BST_node *y = x->left, *p = x->parent;
    if (y == nullptr) {
        std::invalid_argument("[BST::rotateRight] cannot rotate right: left child is null");
    }
    x->left = y->right;
    if (y->right) y->right->parent = x;
    y->right = x;
    x->parent = y;
    if (root == x) {
        this->root = y;
        return;
    }
    if (x == p->left) {
        p->left = y;
    } else {
        // x == p->right
        p->right = y;
    }
    y->parent = p;
}
