#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <string>
#include <ostream>

template <typename V>
class TableEntry {
public:
    // Atributos públicos
    std::string key;
    V value;

    // Constructor clave-valor
    TableEntry(std::string key, V value)
        : key(key), value(value) {}

    // Constructor solo clave (valor por defecto)
    TableEntry(std::string key)
        : key(key), value() {}

    // Constructor por defecto: clave "" y valor por defecto
    TableEntry()
        : key(""), value() {}

    // Dos TableEntry son iguales si tienen la misma clave (independientemente del valor)
    friend bool operator==(const TableEntry<V> &te1, const TableEntry<V> &te2) {
        return te1.key == te2.key;
    }

    // Distintos si las claves son distintas
    friend bool operator!=(const TableEntry<V> &te1, const TableEntry<V> &te2) {
        return !(te1 == te2);
    }

    // Imprimir ('clave' => valor)
    friend std::ostream &operator<<(std::ostream &out, const TableEntry<V> &te) {
        out << "('" << te.key << "' => " << te.value << ")";
        return out;
    }
};

#endif

