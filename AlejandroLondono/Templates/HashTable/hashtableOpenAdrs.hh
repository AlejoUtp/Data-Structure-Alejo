#ifndef __HASHGPT_HH__
#define __HASHGPT_HH__


#include <vector>
#include <string>
#include <functional>
#include <iostream>

using namespace std;

template <typename K, typename V>
class HashtableLP {
private:
    // Estados de cada posición
    enum State { EMPTY, OCCUPIED, DELETED };

    // Estructura de cada celda
    struct Slot {
        K key;
        V value;
        State state;
        Slot() : state(EMPTY) {}
    };

    vector<Slot> table;       // Vector interno
    unsigned int m;           // Capacidad actual
    unsigned int sz;          // Elementos ocupados reales
    unsigned int deleted;     // Cantidad de slots marcados como DELETED
    double load_factor_threshold;

    // Función hash genérica (usa std::hash)
    unsigned int hash_key(const K &key) const {
        return std::hash<K>{}(key) % m;
    }

    // Calcula load factor real
    double load_factor() const {
        return (double)(sz + deleted) / (double)m;
    }

    // Rehashing: duplicar capacidad y reinsertar todo
    void rehash(unsigned int new_capacity) {
        vector<Slot> old_table = table;

        table.clear();
        table.resize(new_capacity);

        m = new_capacity;
        sz = 0;
        deleted = 0;

        // Reinserción de elementos
        for (auto &slot : old_table) {
            if (slot.state == OCCUPIED) {
                insert(slot.key, slot.value);
            }
        }
    }

public:
    // Constructor
    HashtableLP(unsigned int initial_size = 8, double threshold = 0.7)
        : m(initial_size), sz(0), deleted(0), load_factor_threshold(threshold) 
    {
        table.resize(m);
    }

    // Insertar o actualizar
    bool insert(const K &key, const V &value) {
        // Check load factor and rehash
        if (load_factor() > load_factor_threshold) {
            rehash(m * 2);
        }

        unsigned int index = hash_key(key);
        int first_deleted = -1;

        for (unsigned int i = 0; i < m; i++) {
            unsigned int pos = (index + i) % m;

            if (table[pos].state == EMPTY) {
                // Usar deleted previo si existe
                if (first_deleted != -1) pos = first_deleted;

                table[pos].key = key;
                table[pos].value = value;
                table[pos].state = OCCUPIED;

                if (first_deleted != -1) deleted--;
                sz++;
                return true;
            }

            if (table[pos].state == DELETED) {
                if (first_deleted == -1) first_deleted = pos;
                continue;
            }

            if (table[pos].state == OCCUPIED && table[pos].key == key) {
                table[pos].value = value; // update
                return true;
            }
        }

        // Si el vector está realmente lleno y solo había eliminados
        if (first_deleted != -1) {
            table[first_deleted].key = key;
            table[first_deleted].value = value;
            table[first_deleted].state = OCCUPIED;
            deleted--;
            sz++;
            return true;
        }

        return false;
    }

    // Obtener un valor
    bool get(const K &key, V &out_value) const {
        unsigned int index = hash_key(key);

        for (unsigned int i = 0; i < m; i++) {
            unsigned int pos = (index + i) % m;

            if (table[pos].state == EMPTY) {
                return false; // clave no existe
            }

            if (table[pos].state == OCCUPIED && table[pos].key == key) {
                out_value = table[pos].value;
                return true;
            }
        }
        return false;
    }

    // Borrar un elemento
    bool remove(const K &key) {
        unsigned int index = hash_key(key);

        for (unsigned int i = 0; i < m; i++) {
            unsigned int pos = (index + i) % m;

            if (table[pos].state == EMPTY) return false;

            if (table[pos].state == OCCUPIED && table[pos].key == key) {
                table[pos].state = DELETED;
                sz--;
                deleted++;
                return true;
            }
        }
        return false;
    }

    // Devuelve tamaño lógico
    unsigned int size() const { return sz; }

    // Debug: imprime la tabla
    void debug_print() const {
        cout << "\n----- HASH TABLE DEBUG -----\n";
        for (unsigned int i = 0; i < m; i++) {
            cout << "[" << i << "] ";
            if (table[i].state == EMPTY) cout << "EMPTY\n";
            else if (table[i].state == DELETED) cout << "DELETED\n";
            else cout << "OCCUPIED (key=" << table[i].key 
                      << ", value=" << table[i].value << ")\n";
        }
        cout << "---------------------------\n";
    }
};

#endif // __HASHTABLE_HH__