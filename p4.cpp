#include <iostream>
#include <queue>

using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    explicit Node(int v, Node* l = nullptr, Node* r = nullptr)
        : val(v), left(l), right(r) {}
};

bool esCompleto(Node* root) {
    if (root == nullptr) return true;
    queue<Node*> q;
    q.push(root);
    bool vioNulo = false;
    while (!q.empty()) {
        Node* n = q.front();
        q.pop();
        if (n == nullptr) {
            vioNulo = true;
        } else {
            if (vioNulo) return false;
            q.push(n->left);
            q.push(n->right);
        }
    }
    return true;
}

int anchoMaximo(Node* root) {
    if (root == nullptr) return 0;
    queue<Node*> q;
    q.push(root);
    int ancho = 0;
    while (!q.empty()) {
        int tamNivel = (int)q.size();
        if (tamNivel > ancho) ancho = tamNivel;
        for (int i = 0; i < tamNivel; i++) {
            Node* n = q.front();
            q.pop();
            if (n->left) q.push(n->left);
            if (n->right) q.push(n->right);
        }
    }
    return ancho;
}

int profundidadMinima(Node* root) {
    if (root == nullptr) return 0;
    queue<Node*> q;
    q.push(root);
    int profundidad = 0;
    while (!q.empty()) {
        profundidad++;
        int tamNivel = (int)q.size();
        for (int i = 0; i < tamNivel; i++) {
            Node* n = q.front();
            q.pop();
            if (n->left == nullptr && n->right == nullptr) return profundidad;
            if (n->left) q.push(n->left);
            if (n->right) q.push(n->right);
        }
    }
    return profundidad;
}

void liberar(Node* root) {
    if (root == nullptr) return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* n = q.front();
        q.pop();
        if (n->left) q.push(n->left);
        if (n->right) q.push(n->right);
        delete n;
    }
}

void probar(const char* nombre, Node* root, bool esperadoCompleto, int esperadoAncho,
            int esperadaProf) {
    bool c = esCompleto(root);
    int a = anchoMaximo(root);
    int p = profundidadMinima(root);
    bool ok = (c == esperadoCompleto) && (a == esperadoAncho) && (p == esperadaProf);
    cout << nombre << endl;
    cout << "  Completo:           " << (c ? "si" : "no") << endl;
    cout << "  Ancho maximo:       " << a << endl;
    cout << "  Profundidad minima: " << p << endl;
    cout << "  Coincide con lo esperado a mano: " << (ok ? "si" : "NO") << endl << endl;
}

int main() {

    Node* t1 = new Node(1,
                        new Node(2, new Node(4), new Node(5)),
                        new Node(3, new Node(6), new Node(7)));
    probar("Arbol 1: perfecto de 7 nodos", t1, true, 4, 3);

    Node* t2 = new Node(1,
                        new Node(2, new Node(4), new Node(5)),
                        new Node(3, new Node(6), nullptr));
    probar("Arbol 2: completo (ultimo nivel incompleto, a la izquierda)", t2, true, 3, 3);

    Node* t3 = new Node(1,
                        new Node(2, new Node(4), nullptr),
                        new Node(3, nullptr, new Node(7)));
    probar("Arbol 3: NO completo (3 tiene solo hijo derecho)", t3, false, 2, 3);

    Node* t4 = new Node(1,
                        new Node(2, nullptr, new Node(5)),
                        new Node(3));
    probar("Arbol 4: NO completo (2 tiene solo hijo derecho)", t4, false, 2, 2);

    Node* t5 = new Node(1,
                        new Node(2, new Node(4, new Node(8), new Node(9)), new Node(5)),
                        new Node(3));
    probar("Arbol 5: NO completo (3 es hoja pero el nivel 4 tiene nodos)", t5, false, 2, 2);

    Node* t6 = new Node(10);
    probar("Arbol 6: un solo nodo", t6, true, 1, 1);

    probar("Arbol 7: vacio", nullptr, true, 0, 0);

    Node* t8 = new Node(1, nullptr,
                        new Node(2, nullptr,
                                 new Node(3, nullptr, new Node(4))));
    probar("Arbol 8: cadena de 4 nodos", t8, false, 1, 4);

    liberar(t1);
    liberar(t2);
    liberar(t3);
    liberar(t4);
    liberar(t5);
    liberar(t6);
    liberar(t8);
    return 0;
}