#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>
#include <algorithm>

class UnderflowException { };
class IllegalArgumentException { };
class ArrayIndexOutOfBoundsException { };
class IteratorOutOfBoundsException { };
class IteratorMismatchException { };
class IteratorUninitializedException { };

template <typename Comparable>
class BinarySearchTree {
protected:
    struct BinaryNode {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;
        int height;

        BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt)
            : element{ theElement }, left{ lt }, right{ rt }, height{ 1 } {}

        BinaryNode(Comparable &&theElement, BinaryNode *lt, BinaryNode *rt)
            : element{ std::move(theElement) }, left{ lt }, right{ rt }, height{ 1 } {}
    };

    BinaryNode *root;

    int height(BinaryNode *t) const {
        return t == nullptr ? 0 : t->height;
    }

    void updateHeight(BinaryNode *t) {
        if (t != nullptr) {
            t->height = std::max(height(t->left), height(t->right)) + 1;
        }
    }

    int getBalance(BinaryNode *t) const {
        return t == nullptr ? 0 : height(t->left) - height(t->right);
    }

    BinaryNode* rightRotate(BinaryNode *y) {
        BinaryNode *x = y->left;
        BinaryNode *T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    BinaryNode* leftRotate(BinaryNode *x) {
        BinaryNode *y = x->right;
        BinaryNode *T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    BinaryNode* balance(BinaryNode *t) {
        if (t == nullptr) return nullptr;

        updateHeight(t);
        int balance = getBalance(t);

        if (balance > 1) {
            if (getBalance(t->left) >= 0)
                return rightRotate(t);
            else {
                t->left = leftRotate(t->left);
                return rightRotate(t);
            }
        }
        if (balance < -1) {
            if (getBalance(t->right) <= 0)
                return leftRotate(t);
            else {
                t->right = rightRotate(t->right);
                return leftRotate(t);
            }
        }

        return t;
    }

    BinaryNode* findMin(BinaryNode *t) const {
        if (t == nullptr) return nullptr;
        if (t->left == nullptr) return t;
        return findMin(t->left);
    }

    BinaryNode* findMax(BinaryNode *t) const {
        if (t == nullptr) return nullptr;
        if (t->right == nullptr) return t;
        return findMax(t->right);
    }

    bool contains(const Comparable &x, BinaryNode *t) const {
        if (t == nullptr) return false;
        else if (x < t->element) return contains(x, t->left);
        else if (t->element < x) return contains(x, t->right);
        else return true;
    }

    void makeEmpty(BinaryNode *&t) {
        if (t != nullptr) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
            t = nullptr;
        }
    }

    void insert(const Comparable &x, BinaryNode *&t) {
        if (t == nullptr)
            t = new BinaryNode{x, nullptr, nullptr};
        else if (x < t->element)
            insert(x, t->left);
        else if (t->element < x)
            insert(x, t->right);

        updateHeight(t);
        t = balance(t);
    }

    void insert(Comparable &&x, BinaryNode *&t) {
        if (t == nullptr)
            t = new BinaryNode{std::move(x), nullptr, nullptr};
        else if (x < t->element)
            insert(std::move(x), t->left);
        else if (t->element < x)
            insert(std::move(x), t->right);

        updateHeight(t);
        t = balance(t);
    }

    void remove(const Comparable &x, BinaryNode *&t) {
        if (t == nullptr) return;

        if (x < t->element)
            remove(x, t->left);
        else if (t->element < x)
            remove(x, t->right);
        else {
            if (t->left != nullptr && t->right != nullptr) {
                BinaryNode *minNode = detachMin(t->right);
                minNode->left = t->left;
                minNode->right = t->right;
                delete t;
                t = minNode;
            } else {
                BinaryNode *oldNode = t;
                t = (t->left != nullptr) ? t->left : t->right;
                delete oldNode;
            }
        }

        if (t != nullptr) {
            updateHeight(t);
            t = balance(t);
        }
    }

    BinaryNode* detachMin(BinaryNode *&t) {
        if (t == nullptr)
            return nullptr;

        if (t->left == nullptr) {
            BinaryNode *minNode = t;
            t = t->right;
            return minNode;
        }

        BinaryNode* minNode = detachMin(t->left);
        updateHeight(t);
        t = balance(t);
        return minNode;
    }

    BinaryNode* clone(BinaryNode *t) const {
        if (t == nullptr) return nullptr;
        return new BinaryNode{t->element, clone(t->left), clone(t->right)};
    }

    void printTree(BinaryNode *node, std::string prefix = "", bool isLeft = true, std::ostream &out = std::cout) const {
    if (node == nullptr) return;

    out << prefix;
    out << (isLeft ? "├──" : "└──" );

    out << node->element << " (h=" << node->height << ")" << std::endl;

    std::string newPrefix = prefix + (isLeft ? "│   " : "    ");

    printTree(node->right, newPrefix, true, out);
    printTree(node->left, newPrefix, false, out);
}

public:
    BinarySearchTree() : root{ nullptr } {}
    BinarySearchTree(const BinarySearchTree &rhs) : root{ clone(rhs.root) } {}
    BinarySearchTree(BinarySearchTree &&rhs) noexcept : root{ rhs.root } { rhs.root = nullptr; }
    ~BinarySearchTree() { makeEmpty(); }

    const Comparable &findMin() const {
        if (isEmpty()) throw UnderflowException{};
        return findMin(root)->element;
    }

    const Comparable &findMax() const {
        if (isEmpty()) throw UnderflowException{};
        return findMax(root)->element;
    }

    bool contains(const Comparable &x) const { return contains(x, root); }
    bool isEmpty() const { return root == nullptr; }

    void printTree(std::ostream &out = std::cout) const {
    if (isEmpty())
        out << "Empty tree" << std::endl;
    else {
        out << "Tree Structure:" << std::endl;
        printTree(root, "", true, out);
    }
}

    void makeEmpty() { makeEmpty(root); }
    void insert(const Comparable &x) { insert(x, root); }
    void insert(Comparable &&x) { insert(std::move(x), root); }
    void remove(const Comparable &x) { remove(x, root); }
};

#endif // BINARY_SEARCH_TREE_H