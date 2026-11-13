#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <stack>
#include <utility>

using namespace std;

struct BNode {
    int key;
    BNode* left;
    BNode* right;
    explicit BNode(int k) : key(k), left(nullptr), right(nullptr) {}
};

class BST {
private:
    BNode* root;

public:
    BST() : root(nullptr) {}
    ~BST() { clear(); }

    bool insert(int key) {
        if (root == nullptr) {
            root = new BNode(key);
            return true;
        }
        BNode* cur = root;
        BNode* parent = nullptr;
        while (cur != nullptr) {
            parent = cur;
            if (key == cur->key) return false;
            cur = (key < cur->key) ? cur->left : cur->right;
        }
        BNode* nuevo = new BNode(key);
        if (key < parent->key) parent->left = nuevo;
        else parent->right = nuevo;
        return true;
    }

    int height() const {
        if (root == nullptr) return 0;
        int maxDepth = 0;
        stack<pair<BNode*, int>> pila;
        pila.push({root, 1});
        while (!pila.empty()) {
            pair<BNode*, int> p = pila.top();
            pila.pop();
            if (p.second > maxDepth) maxDepth = p.second;
            if (p.first->left) pila.push({p.first->left, p.second + 1});
            if (p.first->right) pila.push({p.first->right, p.second + 1});
        }
        return maxDepth;
    }

    void preorder() const {
        if (root == nullptr) { cout << endl; return; }
        stack<BNode*> pila;
        pila.push(root);
        while (!pila.empty()) {
            BNode* n = pila.top();
            pila.pop();
            cout << n->key << " ";
            if (n->right) pila.push(n->right);
            if (n->left) pila.push(n->left);
        }
        cout << endl;
    }

    void clear() {
        if (root == nullptr) return;
        stack<BNode*> pila;
        pila.push(root);
        while (!pila.empty()) {
            BNode* n = pila.top();
            pila.pop();
            if (n->left) pila.push(n->left);
            if (n->right) pila.push(n->right);
            delete n;
        }
        root = nullptr;
    }
};

enum Color { RED, BLACK };

struct RNode {
    int key;
    Color color;
    RNode* left;
    RNode* right;
    RNode* parent;
    RNode(int k, Color c, RNode* nil)
        : key(k), color(c), left(nil), right(nil), parent(nil) {}
};

class RedBlackTree {
private:
    RNode* root;
    RNode* NIL;

    void rotateLeft(RNode* x) {
        RNode* y = x->right;
        x->right = y->left;
        if (y->left != NIL) y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == NIL) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rotateRight(RNode* x) {
        RNode* y = x->left;
        x->left = y->right;
        if (y->right != NIL) y->right->parent = x;
        y->parent = x->parent;
        if (x->parent == NIL) root = y;
        else if (x == x->parent->right) x->parent->right = y;
        else x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

    void fixInsert(RNode* z) {
        while (z->parent->color == RED) {
            RNode* padre = z->parent;
            RNode* abuelo = padre->parent;
            bool izq = (padre == abuelo->left);
            RNode* tio = izq ? abuelo->right : abuelo->left;
            if (tio->color == RED) {
                padre->color = BLACK;
                tio->color = BLACK;
                abuelo->color = RED;
                recoloraciones += 3;
                z = abuelo;
            } else {
                if (izq) {
                    if (z == padre->right) {
                        z = padre;
                        rotateLeft(z);
                        rotaciones++;
                        padre = z->parent;
                    }
                    padre->color = BLACK;
                    abuelo->color = RED;
                    rotateRight(abuelo);
                } else {
                    if (z == padre->left) {
                        z = padre;
                        rotateRight(z);
                        rotaciones++;
                        padre = z->parent;
                    }
                    padre->color = BLACK;
                    abuelo->color = RED;
                    rotateLeft(abuelo);
                }
                recoloraciones += 2;
                rotaciones++;
            }
        }
        if (root->color != BLACK) {
            root->color = BLACK;
            recoloraciones++;
        }
    }

public:
    int rotaciones;
    int recoloraciones;

    RedBlackTree() : rotaciones(0), recoloraciones(0) {
        NIL = new RNode(0, BLACK, nullptr);
        NIL->left = NIL->right = NIL->parent = NIL;
        root = NIL;
    }

    ~RedBlackTree() {
        if (root != NIL) {
            stack<RNode*> pila;
            pila.push(root);
            while (!pila.empty()) {
                RNode* n = pila.top();
                pila.pop();
                if (n->left != NIL) pila.push(n->left);
                if (n->right != NIL) pila.push(n->right);
                delete n;
            }
        }
        delete NIL;
    }

    bool insert(int key) {
        RNode* y = NIL;
        RNode* x = root;
        while (x != NIL) {
            y = x;
            if (key == x->key) return false;
            x = (key < x->key) ? x->left : x->right;
        }
        RNode* z = new RNode(key, RED, NIL);
        z->parent = y;
        if (y == NIL) root = z;
        else if (key < y->key) y->left = z;
        else y->right = z;

        fixInsert(z);
        return true;
    }

    int height() const {
        if (root == NIL) return 0;
        int maxDepth = 0;
        stack<pair<RNode*, int>> pila;
        pila.push({root, 1});
        while (!pila.empty()) {
            pair<RNode*, int> p = pila.top();
            pila.pop();
            if (p.second > maxDepth) maxDepth = p.second;
            if (p.first->left != NIL) pila.push({p.first->left, p.second + 1});
            if (p.first->right != NIL) pila.push({p.first->right, p.second + 1});
        }
        return maxDepth;
    }

    void preorder() const {
        if (root == NIL) { cout << endl; return; }
        stack<RNode*> pila;
        pila.push(root);
        while (!pila.empty()) {
            RNode* n = pila.top();
            pila.pop();
            cout << n->key << (n->color == RED ? "R" : "B") << " ";
            if (n->right != NIL) pila.push(n->right);
            if (n->left != NIL) pila.push(n->left);
        }
        cout << endl;
    }

    bool verificar(bool verbose = false) const {
        bool ok = true;

        if (NIL->color != BLACK) {
            if (verbose) cout << "  [FALLA] P5: las hojas nulas no son negras\n";
            ok = false;
        }
        if (root == NIL) return ok;

        if (root->color != BLACK) {
            if (verbose) cout << "  [FALLA] P2: la raiz no es negra\n";
            ok = false;
        }

        struct Frame {
            RNode* n;
            int negros;
            long long lo, hi;
        };
        stack<Frame> pila;
        pila.push({root, 0, -(1LL << 40), (1LL << 40)});
        int negrosEsperados = -1;

        while (!pila.empty()) {
            Frame f = pila.top();
            pila.pop();
            RNode* n = f.n;
            int negros = f.negros + (n->color == BLACK ? 1 : 0);


            if (n->key <= f.lo || n->key >= f.hi) {
                if (verbose) cout << "  [FALLA] BST: orden invalido en la clave " << n->key << "\n";
                ok = false;
            }

            if (n->color == RED &&
                (n->left->color == RED || n->right->color == RED)) {
                if (verbose) cout << "  [FALLA] P3: nodo rojo " << n->key << " con hijo rojo\n";
                ok = false;
            }

            RNode* hijos[2] = {n->left, n->right};
            long long los[2] = {f.lo, n->key};
            long long his[2] = {n->key, f.hi};
            for (int i = 0; i < 2; i++) {
                RNode* h = hijos[i];
                if (h == NIL) {
                    if (negrosEsperados == -1) negrosEsperados = negros;
                    else if (negros != negrosEsperados) {
                        if (verbose) cout << "  [FALLA] P4: caminos con distinta cantidad de negros (en " << n->key << ")\n";
                        ok = false;
                    }
                } else {
                    if (h->parent != n) {
                        if (verbose) cout << "  [FALLA] puntero padre incoherente en " << h->key << "\n";
                        ok = false;
                    }
                    pila.push({h, negros, los[i], his[i]});
                }
            }
        }
        return ok;
    }

    int blackHeight() const {
        int bh = 0;
        for (RNode* n = root; n != NIL; n = n->left)
            if (n->color == BLACK) bh++;
        return bh;
    }
};

int main() {
    cout << "Parte 1: 20 elementos en orden ascendente " << endl;
    BST bst;
    RedBlackTree rbt;
    for (int i = 1; i <= 20; i++) {
        bst.insert(i * 10);
        rbt.insert(i * 10);
    }

    cout << "\nBST (Problema 1)" << endl;
    cout << "  Altura: " << bst.height() << endl;
    cout << "  Pre-orden: ";
    bst.preorder();

    cout << "\nRed-Black Tree" << endl;
    cout << "  Altura: " << rbt.height() << endl;
    cout << "  Altura negra: " << rbt.blackHeight() << endl;
    cout << "  Rotaciones: " << rbt.rotaciones
         << " | Recoloraciones: " << rbt.recoloraciones << endl;
    cout << "  Pre-orden (clave + color R/B): ";
    rbt.preorder();

    cout << "\nVerificacion de propiedades del RBT: ";
    cout << (rbt.verificar(true) ? "TODAS SE CUMPLEN" : "HAY VIOLACIONES") << endl;

    cout << "\nCota teorica: h <= 2*log2(n+1) = " << fixed << setprecision(2)
         << 2 * log2(20 + 1) << endl;

    cout << "\nParte 2: altura con n claves ascendentes " << endl;
    cout << left << setw(8) << "n" << setw(12) << "BST" << setw(12) << "RBT"
         << setw(18) << "2*log2(n+1)" << setw(10) << "RBT ok?" << endl;
    int tamanos[] = {20, 100, 1000, 10000};
    for (int n : tamanos) {
        BST b;
        RedBlackTree r;
        for (int i = 1; i <= n; i++) {
            b.insert(i);
            r.insert(i);
        }
        cout << left << setw(8) << n << setw(12) << b.height() << setw(12) << r.height()
             << setw(18) << 2 * log2(n + 1) << setw(10) << (r.verificar() ? "si" : "NO") << endl;
    }

    cout << "\nParte 3: 2000 inserciones aleatorias, verificando tras cada una " << endl;
    srand(12345);
    RedBlackTree aleatorio;
    bool todoOk = true;
    for (int i = 0; i < 2000; i++) {
        aleatorio.insert(rand() % 100000);
        if (!aleatorio.verificar()) {
            todoOk = false;
            cout << "Violacion detectada tras la insercion #" << i << endl;
            aleatorio.verificar(true);
            break;
        }
    }
    cout << (todoOk ? "Las 5 propiedades se cumplieron tras cada insercion." : "FALLO") << endl;
    cout << "Altura final: " << aleatorio.height() << endl;

    return 0;
}