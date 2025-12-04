#ifndef BSNODE_H
#define BSNODE_H

#include <ostream>

template <typename T>
class BSNode {
public:
    T elem;               // elemento almacenado en el nodo
    BSNode<T>* left;      // puntero al hijo izquierdo
    BSNode<T>* right;     // puntero al hijo derecho

    // Constructor: elem y punteros izquierdo/derecho (por defecto nullptr)
    BSNode(T elem, BSNode<T>* left = nullptr, BSNode<T>* right = nullptr)
        : elem(elem), left(left), right(right) {}

    // Sobrecarga del operador << (imprime solo elem)
    friend std::ostream& operator<<(std::ostream& out, const BSNode<T>& bsn) {
        out << bsn.elem;
        return out;
    }
};

#endif

