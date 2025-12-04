#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <string>

#include "Dict.h"
#include "TableEntry.h"

// adapta la ruta a tu PRA_2526_P1
#include "../PRA_2526_P1/ListLinked.h"

template <typename V>
class HashTable : public Dict<V> {

private:
    int n;   // número de elementos almacenados
    int max; // número total de cubetas
    ListLinked<TableEntry<V>>* table; // array de listas de TableEntry<V>

    // Función hash: suma de ASCII % max
    int h(std::string key) {
        int suma = 0;
        for (std::size_t i = 0; i < key.length(); ++i) {
            suma += int(key.at(i));
        }
        return suma % max;
    }

public:
    // Constructor: reserva la tabla y pone contadores
    HashTable(int size) {
        if (size <= 0) {
            throw std::runtime_error("HashTable size must be > 0");
        }
        max = size;
        n = 0;
        table = new ListLinked<TableEntry<V>>[max];
    }

    // Destructor: libera la tabla
    ~HashTable() {
        delete[] table;
    }

    // Número total de cubetas
    int capacity() {
        return max;
    }

    // Número de elementos almacenados (implementa Dict<V>::entries)
    int entries() override {
        return n;
    }

    // Inserta key -> value, lanza si existe
    void insert(std::string key, V value) override {
        int idx = h(key);
        ListLinked<TableEntry<V>>& bucket = table[idx];

        // Buscar si ya existe la clave
        for (int i = 0; i < bucket.size(); ++i) {
            TableEntry<V> te = bucket.get(i);
            if (te.key == key) {
                throw std::runtime_error("Key '" + key + "' already exists!");
            }
        }

        // Insertamos al principio de la lista (posición 0)
        TableEntry<V> nuevo(key, value);
        bucket.insert(0, nuevo);
        n++;
    }

    // Busca y devuelve el valor asociado a key, lanza si no está
    V search(std::string key) override {
        int idx = h(key);
        ListLinked<TableEntry<V>>& bucket = table[idx];

        for (int i = 0; i < bucket.size(); ++i) {
            TableEntry<V> te = bucket.get(i);
            if (te.key == key) {
                return te.value;
            }
        }

        throw std::runtime_error("Key '" + key + "' not found!");
    }

    // Elimina la clave y devuelve su valor, lanza si no está
    V remove(std::string key) override {
        int idx = h(key);
        ListLinked<TableEntry<V>>& bucket = table[idx];

        for (int i = 0; i < bucket.size(); ++i) {
            TableEntry<V> te = bucket.get(i);
            if (te.key == key) {
                V res = te.value;
                bucket.remove(i);
                n--;
                return res;
            }
        }

        throw std::runtime_error("Key '" + key + "' not found!");
    }

    // Operador [] que usa search() y lanza si no está
    V operator[](std::string key) {
        return search(key);
    }

    // Imprimir la tabla hash como en el ejemplo del enunciado
    friend std::ostream& operator<<(std::ostream& out, const HashTable<V>& ht) {
        out << "HashTable [entries: " << ht.n
            << ", capacity: " << ht.max << "]\n";
        out << "==============\n\n";

        for (int i = 0; i < ht.max; ++i) {
            out << "== Cubeta " << i << " ==\n\n";
            out << ht.table[i] << "\n\n"; // usa operator<< de ListLinked
        }

        out << "==============\n";
        return out;
    }
};

#endif

