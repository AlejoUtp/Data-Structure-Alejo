#include <iostream>
#include "HashtableOpenAdrs.hh"   // Cambia al nombre real de tu archivo

using namespace std;

int main() {
    cout << "=== TEST: HashTable Linear Probing with Rehashing ===\n\n";

    // Crear tabla MUY pequeña para forzar rehashing
    HashtableLP<string, string> ht(4, 0.7);

    cout << "Inserting 4 elements...\n";
    ht.insert("Juan", "111");
    ht.insert("Maria", "222");
    ht.insert("Pedro", "333");
    ht.insert("Ana", "444");

    ht.debug_print();

    cout << "\nNow forcing rehash by inserting more elements...\n";
    ht.insert("Luis", "555");
    ht.insert("Sofia", "666");
    ht.insert("Miguel", "777");

    ht.debug_print();

    cout << "\n=== TEST GET (Existing Keys) ===\n";
    string r;
    if (ht.get("Juan", r)) cout << "Juan -> " << r << endl;
    if (ht.get("Maria", r)) cout << "Maria -> " << r << endl;
    if (ht.get("Pedro", r)) cout << "Pedro -> " << r << endl;
    if (ht.get("Ana", r)) cout << "Ana -> " << r << endl;

    cout << "\n=== TEST GET (After Rehash) ===\n";
    if (ht.get("Luis", r)) cout << "Luis -> " << r << endl;
    if (ht.get("Sofia", r)) cout << "Sofia -> " << r << endl;
    if (ht.get("Miguel", r)) cout << "Miguel -> " << r << endl;

    cout << "\n=== TEST GET (Non-existing Key) ===\n";
    if (!ht.get("Carlos", r)) {
        cout << "Carlos not found (expected)\n";
    }

    cout << "\n=== TEST UPDATE ===\n";
    ht.insert("Maria", "999");  // Update
    ht.get("Maria", r);
    cout << "Maria updated -> " << r << endl;

    ht.debug_print();

    cout << "\n=== TEST REMOVE ===\n";
    cout << "Removing Pedro...\n";
    ht.remove("Pedro");
    if (!ht.get("Pedro", r)) cout << "Pedro not found (correct)\n";

    cout << "Removing Ana...\n";
    ht.remove("Ana");
    if (!ht.get("Ana", r)) cout << "Ana not found (correct)\n";

    ht.debug_print();

    cout << "\n=== TEST INSERT AFTER DELETE (Uses DELETED slots) ===\n";
    ht.insert("Nuevo", "12345");
    ht.insert("Otro", "67890");

    ht.debug_print();

    cout << "\n=== TEST COMPLETE ===\n";
    return 0;
}