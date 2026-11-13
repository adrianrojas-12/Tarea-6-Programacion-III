#include <iostream>
#include <stack>
#include <utility>

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    explicit Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root;

public:
    long long comparaciones;

    BST() : root(nullptr), comparaciones(0) {}

    ~BST() { clear(); }

    bool insert(int key) {
        if (root == nullptr) {
            root = new Node(key);
            return true;
        }
        Node* cur = root;
        Node* parent = nullptr;
        while (cur != nullptr) {
            parent = cur;
            comparaciones++;
            if (key == cur->key) return false;
            cur = (key < cur->key) ? cur->left : cur->right;
        }
        Node* nuevo = new Node(key);
        if (key < parent->key) parent->left = nuevo;
        else parent->right = nuevo;
        return true;
    }

    bool remove(int key) {
        Node* parent = nullptr;
        Node* cur = root;
        while (cur != nullptr && cur->key != key) {
            parent = cur;
            cur = (key < cur->key) ? cur->left : cur->right;
        }
        if (cur == nullptr) return false;

        if (cur->left != nullptr && cur->right != nullptr) {
            Node* succParent = cur;
            Node* succ = cur->right;
            while (succ->left != nullptr) {
                succParent = succ;
                succ = succ->left;
            }
            cur->key = succ->key;
            parent = succParent;
            cur = succ;
        }

        Node* child = (cur->left != nullptr) ? cur->left : cur->right;
        if (parent == nullptr) root = child;
        else if (parent->left == cur) parent->left = child;
        else parent->right = child;

        delete cur;
        return true;
    }

    void inorder() const {
        stack<Node*> pila;
        Node* cur = root;
        while (cur != nullptr || !pila.empty()) {
            while (cur != nullptr) {
                pila.push(cur);
                cur = cur->left;
            }
            cur = pila.top();
            pila.pop();
            cout << cur->key << " ";
            cur = cur->right;
        }
        cout << endl;
    }

    void preorder() const {
        if (root == nullptr) { cout << endl; return; }
        stack<Node*> pila;
        pila.push(root);
        while (!pila.empty()) {
            Node* n = pila.top();
            pila.pop();
            cout << n->key << " ";
            if (n->right) pila.push(n->right);
            if (n->left) pila.push(n->left);
        }
        cout << endl;
    }

    int height() const {
        if (root == nullptr) return 0;
        int maxDepth = 0;
        stack<pair<Node*, int>> pila;
        pila.push({root, 1});
        while (!pila.empty()) {
            pair<Node*, int> p = pila.top();
            pila.pop();
            if (p.second > maxDepth) maxDepth = p.second;
            if (p.first->left) pila.push({p.first->left, p.second + 1});
            if (p.first->right) pila.push({p.first->right, p.second + 1});
        }
        return maxDepth;
    }

    void clear() {
        if (root == nullptr) return;
        stack<Node*> pila;
        pila.push(root);
        while (!pila.empty()) {
            Node* n = pila.top();
            pila.pop();
            if (n->left) pila.push(n->left);
            if (n->right) pila.push(n->right);
            delete n;
        }
        root = nullptr;
    }
};

int main() {
    cout << "Parte A: 20 elementos insertados en orden ascendente " << endl;
    BST arbol;
    for (int i = 1; i <= 20; i++) arbol.insert(i * 10);

    cout << "Insercion de 20 elementos (10, 20, ..., 200)" << endl;
    cout << "Comparaciones totales al insertar: " << arbol.comparaciones
         << "  (n(n-1)/2 = " << 20 * 19 / 2 << ")" << endl;
    cout << "Altura tras insertar: " << arbol.height() << endl;

    cout << "\nEliminando 50 (un hijo) y 200 (hoja)..." << endl;
    cout << "remove(50):  " << (arbol.remove(50) ? "ok" : "no existe") << endl;
    cout << "remove(200): " << (arbol.remove(200) ? "ok" : "no existe") << endl;
    cout << "remove(999): " << (arbol.remove(999) ? "ok" : "no existe") << endl;

    cout << "\nRecorrido in-order: ";
    arbol.inorder();
    cout << "Altura final: " << arbol.height() << endl;

    cout << "\nParte B: prueba con un arbol no degenerado " << endl;
    BST prueba;
    int datos[] = {50, 30, 70, 20, 40, 60, 80, 35, 45};
    for (int d : datos) prueba.insert(d);

    cout << "Pre-orden inicial: ";
    prueba.preorder();
    cout << "In-order inicial:  ";
    prueba.inorder();
    cout << "Altura: " << prueba.height() << endl;

    cout << "\nremove(30) (dos hijos): " << (prueba.remove(30) ? "ok" : "no existe") << endl;
    cout << "remove(50) (raiz, dos hijos): " << (prueba.remove(50) ? "ok" : "no existe") << endl;
    cout << "Pre-orden: ";
    prueba.preorder();
    cout << "In-order:  ";
    prueba.inorder();
    cout << "Altura: " << prueba.height() << endl;

    return 0;
}