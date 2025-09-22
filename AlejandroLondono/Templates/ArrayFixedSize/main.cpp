#include "Array.hh"
#include <iostream>

int main() {
    // Crear un Array<int> de capacidad 5, inicializado en 0
    Array<int> arr1(5,1);

    cout << "Array inicial: ";
    arr1.print();

    // Modificar elementos con operator[]
    arr1[0] = 10;
    arr1[1] = 20;
    arr1[2] = 30;

    cout << "Array modificado: ";
    arr1.print();

    // Usar at() (lanza excepción si está fuera de rango)
    try {
        cout << "Elemento en indice 2: " << arr1.at(2) << endl;
        cout << "Elemento en indice 10: " << arr1.at(10) << endl; // fuera de rango
    } catch (const out_of_range& e) {
        cout << "Excepcion: " << e.what() << endl;
    }

    // Probar constructor copia
    Array<int> arr2 = arr1;
    cout << "Array copia: ";
    arr2.print();

    // Probar comparacion
    cout << "¿arr1 == arr2? " << (arr1 == arr2 ? "SI" : "NO") << endl;

    arr2[0] = 99;
    cout << "Array arr2 modificado: ";
    arr2.print();

    cout << "¿arr1 == arr2? " << (arr1 == arr2 ? "SI" : "NO") << endl;
    
    arr1.print();
    arr2.print();

    return 0;
}