#ifndef BSTConexiones_hpp
#define BSTConexiones_hpp

#include <iostream>
#include <map>
#include <vector>
#include <queue>

template<class K, class V>
class BSTConexiones{
private:
    std::vector<std::string> top5diario;
    std::vector<int> totalConexionesDiario;

public:
    std::pair<K, V> data;
    BSTConexiones<K, V>* left;
    BSTConexiones<K, V>* right;
    BSTConexiones<K, V>* root;

    BSTConexiones() : root(nullptr) {}
    BSTConexiones(std::pair<K, V> data) : data(data), left(nullptr), right(nullptr) {}


    void insertValue(std::pair<K, V> data);
    BSTConexiones<K, V> * insertNode(BSTConexiones<K, V>* node, std::pair<K, V> data);
    void printTopN(int n);
    void printTopNfull(BSTConexiones<K, V>* node, int n, int& count);
    std::vector<std::string> getTop5diario();
    std::vector<int> getTotalConexionesDiario();

    void fillTopN(int n);
    void fillTop5diario(BSTConexiones<K, V>* node, int n, int& count);

    void fillTotalD(int n);
    void fillTotalDiario(BSTConexiones<K, V>* node, int n, int& count);

    void fillTopNfull(BSTConexiones<K, V>* node, int n, int& count);


};

template <class K, class V>
std::vector<std::string> BSTConexiones<K,V>::getTop5diario() {
    return top5diario;
}

template <class K, class V>
std::vector<int> BSTConexiones<K,V>::getTotalConexionesDiario() {
    return totalConexionesDiario;
}

template<class K, class V>
void BSTConexiones<K, V>::insertValue(std::pair<K, V> data) {
    root = insertNode(root, data);
}

template<class K, class V>
BSTConexiones<K, V> * BSTConexiones<K, V>::insertNode(BSTConexiones<K, V>* node, std::pair<K, V> data) {
    if (node == nullptr) {
        return new BSTConexiones<K, V>(data);
    }


    if (data.second > node->data.second) {
        node->right = insertNode(node->right, data);
    }
    else if (data.second < node->data.second) {
        node->left = insertNode(node->left, data);
    }

    else {
        node->left = insertNode(node->left, data);
    }

    return node;
}


template< class K, class V>
void BSTConexiones<K, V>::printTopN(int n) {
        int count = 0;
        printTopNfull(this->root, n, count);
    }
template< class K, class V>
void BSTConexiones<K, V>::fillTopN(int n) {
        int count = 0;
          fillTop5diario(this->root, n, count);
    }

template< class K, class V>
void BSTConexiones<K, V>::fillTotalD(int n) {
        int count = 0;
          fillTotalDiario(this->root, n, count);
    }

template<class K, class V>
void BSTConexiones<K, V>::printTopNfull(BSTConexiones<K, V>* node, int n, int& count) {
        if (node == nullptr || count >= n) {
            return;
        }

        printTopNfull(node->right, n, count);

        if (count < n) {
            std::cout << node->data.first << ": " << node->data.second << std::endl;
            count++;
        }

        printTopNfull(node->left, n, count);
    }


template<class K, class V>
void BSTConexiones<K, V>::fillTopNfull(BSTConexiones<K, V>* node, int n, int& count) {
        if (node == nullptr || count >= n) {
            return;
        }

        fillTopNfull(node->right, n, count);

        if (count < n) {
            top5diario.push_back(node->data.first);
            totalConexionesDiario.push_back(node->data.second);
            count++;
        }

        fillTopNfull(node->left, n, count);
    }

template<class K, class V>
void BSTConexiones<K, V>::fillTop5diario(BSTConexiones<K, V>* node, int n, int& count) {
    if (node == nullptr || count >= n) {
        return;
    }

    fillTopNfull(node->right, n, count);

    if (count < n) {
        top5diario.push_back(node->data.first);
        count++;
    }

    fillTopNfull(node->left, n, count);
}

template<class K, class V>
void BSTConexiones<K, V>::fillTotalDiario(BSTConexiones<K, V>* node, int n, int& count) {
    if (node == nullptr || count >= n) {
        return;
    }

    fillTopNfull(node->right, n, count);

    if (count < n) {
        totalConexionesDiario.push_back(node->data.second);
        count++;
    }

    fillTopNfull(node->left, n, count);
}




#endif /* BSTConexiones_hpp */