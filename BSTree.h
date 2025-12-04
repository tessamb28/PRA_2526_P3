#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T>
class BSTree {
private:
    int nelem;          // número de elementos en el ABB
    BSNode<T>* root;    // nodo raíz

    // ====== MÉTODOS PRIVADOS RECURSIVOS ======

    // Búsqueda recursiva en el subárbol con raíz n
    BSNode<T>* search(BSNode<T>* n, T e) const {
        if (n == nullptr) {
            throw std::runtime_error("Element not found!");
        } else if (n->elem < e) {
            return search(n->right, e);
        } else if (n->elem > e) {
            return search(n->left, e);
        } else {
            return n;
        }
    }

    // Inserción recursiva en el subárbol con raíz n
    BSNode<T>* insert(BSNode<T>* n, T e) {
        if (n == nullptr) {
            nelem++;
            return new BSNode<T>(e);
        } else if (n->elem == e) {
            throw std::runtime_error("Duplicated element!");
        } else if (n->elem < e) {
            n->right = insert(n->right, e);
        } else {
            n->left = insert(n->left, e);
        }
        return n;
    }

    // Recorrido inorden (simétrico)
    void print_inorder(std::ostream &out, BSNode<T>* n) const {
        if (n != nullptr) {
            print_inorder(out, n->left);
            out << n->elem << " ";
            print_inorder(out, n->right);
        }
    }

    // Eliminar e en el subárbol con raíz n
    BSNode<T>* remove(BSNode<T>* n, T e) {
        if (n == nullptr) {
            throw std::runtime_error("Element not found!");
        } else if (n->elem < e) {
            n->right = remove(n->right, e);
        } else if (n->elem > e) {
            n->left = remove(n->left, e);
        } else {
            // Encontrado n
            if (n->left != nullptr && n->right != nullptr) {
                // Dos hijos: reemplazar por máximo del subárbol izquierdo
                n->elem = max(n->left);
                n->left = remove_max(n->left);
            } else {
                // Uno o cero hijos
                BSNode<T>* child = (n->left != nullptr) ? n->left : n->right;
                delete n;
                nelem--;
                n = child;
            }
        }
        return n;
    }

    // Devuelve el máximo elemento del subárbol con raíz n
    T max(BSNode<T>* n) const {
        if (n == nullptr) {
            throw std::runtime_error("Element not found!");
        }
        if (n->right != nullptr) {
            return max(n->right);
        } else {
            return n->elem;
        }
    }

    // Elimina el nodo de máximo valor en el subárbol con raíz n
    BSNode<T>* remove_max(BSNode<T>* n) {
        if (n->right == nullptr) {
            BSNode<T>* left_child = n->left;
            delete n;
            nelem--;
            return left_child;
        } else {
            n->right = remove_max(n->right);
            return n;
        }
    }

    // Libera recursivamente todos los nodos del subárbol con raíz n
    void delete_cascade(BSNode<T>* n) {
        if (n != nullptr) {
            delete_cascade(n->left);
            delete_cascade(n->right);
            delete n;
        }
    }

public:
    // ====== MÉTODOS PÚBLICOS ======

    // Constructor: árbol vacío
    BSTree() : nelem(0), root(nullptr) {}

    // Destructor: libera todos los nodos
    ~BSTree() {
        delete_cascade(root);
        root = nullptr;
        nelem = 0;
    }

    // Número de elementos del ABB
    int size() const {
        return nelem;
    }

    // Búsqueda lanzadera: devuelve el elemento e si está (puede ajustarse si se desea devolver el almacenado)
    T search(T e) const {
        BSNode<T>* n = search(root, e);
        return n->elem;
    }

    // Sobrecarga de operador[]: delega en search
    T operator[](T e) const {
        return search(e);
    }

    // Inserción lanzadera
    void insert(T e) {
        root = insert(root, e);
    }

    // Eliminación lanzadera
    void remove(T e) {
        root = remove(root, e);
    }

    // Operador <<: imprime el árbol en inorden
    friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst) {
        bst.print_inorder(out, bst.root);
        return out;
    }
};

#endif

