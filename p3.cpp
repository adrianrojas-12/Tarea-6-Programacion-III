#include <algorithm>
#include <iostream>
#include <stack>
#include <utility>
#include <vector>

using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    explicit Node(int v, Node* l = nullptr, Node* r = nullptr)
        : val(v), left(l), right(r) {}
};

pair<bool, vector<int>> caminoConSuma(Node* root, int K) {
    stack<Node*> camino;
    Node* cur = root;
    Node* ultimo = nullptr;
    long long suma = 0;

    while (cur != nullptr || !camino.empty()) {
        while (cur != nullptr) {
            camino.push(cur);
            suma += cur->val;
            cur = cur->left;
        }

        Node* tope = camino.top();

        if (tope->right != nullptr && ultimo != tope->right) {
            cur = tope->right;
            continue;
        }

        if (tope->left == nullptr && tope->right == nullptr && suma == K) {
            vector<int> resultado;
            stack<Node*> copia = camino;
            while (!copia.empty()) {
                resultado.push_back(copia.top()->val);
                copia.pop();
            }
            reverse(resultado.begin(), resultado.end());
            return {true, resultado};
        }

        suma -= tope->val;
        ultimo = tope;
        camino.pop();
    }
    return {false, {}};
}

void liberar(Node* root) {
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
}

void probar(Node* root, int K) {
    pair<bool, vector<int>> r = caminoConSuma(root, K);
    cout << "  K = " << K << " -> ";
    if (!r.first) {
        cout << "no existe camino" << endl;
        return;
    }
    cout << "existe: ";
    for (size_t i = 0; i < r.second.size(); i++) {
        cout << r.second[i] << (i + 1 < r.second.size() ? " -> " : "");
    }
    cout << endl;
}

int main() {
    Node* t1 = new Node(5,
                        new Node(4,
                                 new Node(11, new Node(7), new Node(2))),
                        new Node(8,
                                 new Node(13),
                                 new Node(4, nullptr, new Node(1))));

    cout << "Arbol 1 (caminos con sumas 27, 22, 26, 18) " << endl;
    probar(t1, 22);
    probar(t1, 27);
    probar(t1, 26);
    probar(t1, 18);
    probar(t1, 100);
    probar(t1, 5);
    probar(t1, 9);

    Node* t2 = new Node(1,
                        new Node(-2, new Node(4)),
                        new Node(3, new Node(-1), new Node(2)));
    cout << "\nArbol 2 (con negativos, caminos con sumas 3, 3, 6) " << endl;
    probar(t2, 3);
    probar(t2, 6);
    probar(t2, 4);

    Node* t3 = new Node(7);
    cout << "\nArbol 3 (un solo nodo) " << endl;
    probar(t3, 7);
    probar(t3, 8);

    cout << "\nArbol 4 (vacio) " << endl;
    probar(nullptr, 0);

    liberar(t1);
    liberar(t2);
    liberar(t3);
    return 0;
}