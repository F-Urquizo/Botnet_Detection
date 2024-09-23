#ifndef BST_hpp
#define BST_hpp


#include "BinaryTree.hpp"
#include <functional>
#include <iostream>
#include <queue>

template <class T>
class BST : public BinaryTree<T> {
public:
    BST() {};
    virtual ~BST() { };

    TreeNode<T>* search(const T&) const;
    bool insert(const T&);
    bool insert(TreeNode<T>*);
    bool insertPair(const std::pair<std::string, int>&);

    int whatlevelamI(const T&) const;
    int treeHeight();
    int treeHeight(TreeNode<T>* node);
    void visit(int op, std::function<void(const T&)> func);
    void preOrden(std::function<void(const T&)> func);
    void preOrden(TreeNode<T>* node, std::function<void(const T&)> func);
    void levelByLevel() const;
    void levelByLevel(TreeNode<T>*) const;
    void ancestors(TreeNode<T>* node) const;
    int whatLvl(TreeNode<T>* node) const;
    int whatLvl(TreeNode<T>* node, TreeNode<T>* current, int level) const;

    void visitTop(int n);

private:
    // Ocultar algunos métodos heredados
    using BinaryTree<T>::insert;
    void visitTop(TreeNode<T>* node, int& n, std::vector<T>& result);
};

template <class T>
void BST<T>::visitTop(int n) {
    std::vector<T> result;
    visitTop(this->root, n, result);
    for (const auto& item : result) {
        std::cout << item.first << ": " << item.second << std::endl;
    }
}

template <class T>
void BST<T>::visitTop(TreeNode<T>* node, int& n, std::vector<T>& result) {
    if (node == nullptr || n == 0) {
        return;
    }
    visitTop(node->getRight(), n, result);
    if (n > 0) {
        result.push_back(node->getInfo());
        n--;
    }
    visitTop(node->getLeft(), n, result);
}

template <class T>
bool BST<T>::insertPair(const std::pair<std::string, int>& data) {
    return insert(data);
}

template <class T>
TreeNode<T>* BST<T>::search(const T& value) const {
    TreeNode<T>* aux = this->root;
    while (aux != nullptr) {
        if (aux->getInfo() == value) {
            return aux;
        } else {
            aux = aux->getInfo() > value ? aux->getLeft() : aux->getRight();
        }
    }
    return nullptr;
}

template <class T>
bool BST<T>::insert(const T& value) {
    return insert(new TreeNode<T>(value));
}

template <class T>
bool BST<T>::insert(TreeNode<T>* node) {
    if (node == nullptr) return false;
    T value = node->getInfo();
    TreeNode<T>* aux = this->root;
    TreeNode<T>* parent = nullptr;
    while (aux != nullptr) {
        if (aux->getInfo() == value) {
            delete node;
            return false;
        } else {
            parent = aux;
            aux = aux->getInfo() > value ? aux->getLeft() : aux->getRight();
        }
    }
    node->setParent(parent);
    if (parent == nullptr) {
        this->root = node;
    } else {
        if (parent->getInfo() > value) {
            parent->setLeft(node);
        } else {
            parent->setRight(node);
        }
    }
    return true;
}

template <class T>
int BST<T>::whatlevelamI(const T& value) const {
    int level = 0;
    TreeNode<T>* aux = this->root;
    while (aux != nullptr) {
        level++;
        if (aux->getInfo() == value) {
            return level;
        } else {
            aux = aux->getInfo() > value ? aux->getLeft() : aux->getRight();
        }
    }
    return 0; // If the value is not found
}

template <class T>
int BST<T>::treeHeight() {
    return treeHeight(this->root);
}

template <class T>
int BST<T>::treeHeight(TreeNode<T>* node) {
    if (node == nullptr) {
        return 0;
    } else {
        int leftHeight = treeHeight(node->getLeft());
        int rightHeight = treeHeight(node->getRight());
        return std::max(leftHeight, rightHeight) + 1;
    }
}

template <class T>
void BST<T>::ancestors(TreeNode<T>* node) const {
    if (node == nullptr || this->root == nullptr) {
        std::cout << "Node not found or tree is empty." << std::endl;
        return;
    }
    TreeNode<T>* current = this->root;
    while (current != nullptr && current != node) {
        std::cout << current->getInfo() << " ";
        current = node->getInfo() < current->getInfo() ? current->getLeft() : current->getRight();
    }
    std::cout << std::endl;
}

template <class T>
void BST<T>::visit(int op, std::function<void(const T&)> func) {
    switch (op) {
        case 1:
            std::cout << "Pre-orden: " << std::endl;
            preOrden(func);
            break;
        case 2:
            std::cout << "In-orden: " << std::endl;
            this->inOrden(func);
            break;
        case 3:
            std::cout << "Post-orden: " << std::endl;
            this->postOrden(func);
            break;
        case 4:
            std::cout << "Level by level: " << std::endl;
            levelByLevel();
            break;
        default:
            std::cout << "Invalid option" << std::endl;
            break;
    }
}

template <class T>
void BST<T>::preOrden(std::function<void(const T&)> func) {
    preOrden(this->root, func);
}

template <class T>
void BST<T>::preOrden(TreeNode<T>* node, std::function<void(const T&)> func) {
    if (node != nullptr) {
        func(node->getInfo());
        preOrden(node->getLeft(), func);
        preOrden(node->getRight(), func);
    }
}

template <class T>
void BST<T>::levelByLevel() const {
    levelByLevel(this->root);
}

template <class T>
void BST<T>::levelByLevel(TreeNode<T>* root) const {
    if (root == nullptr) return;
    std::queue<TreeNode<T>*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode<T>* current = q.front();
        q.pop();
        std::cout << current->getInfo() << " ";
        if (current->getLeft() != nullptr) q.push(current->getLeft());
        if (current->getRight() != nullptr) q.push(current->getRight());
    }
    std::cout << std::endl;
}

template <class T>
int BST<T>::whatLvl(TreeNode<T>* node) const {
    return whatLvl(node, this->root, 0);
}

template <class T>
int BST<T>::whatLvl(TreeNode<T>* node, TreeNode<T>* current, int level) const {
    if (current == nullptr) {
        return -1; // Node not found
    }
    if (node->getInfo() == current->getInfo()) {
        return level;
    }
    if (node->getInfo() < current->getInfo()) {
        return whatLvl(node, current->getLeft(), level + 1);
    } else {
        return whatLvl(node, current->getRight(), level + 1);
    }
}


#endif /* BST_hpp */
