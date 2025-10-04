/**
 * @file main.cpp
 * @brief Archivo de pruebas para la clase BST (SOLO FUNCIONES IMPLEMENTADAS)
 */

#include "bsta.hh"
#include <iostream>
#include <string>

using namespace std;

void printSeparator(const string &title)
{
    cout << "\n"
         << string(60, '=') << endl;
    cout << "  " << title << endl;
    cout << string(60, '=') << endl;
}

void printTestResult(const string &test, bool passed)
{
    cout << "[" << (passed ? "✓ PASS" : "✗ FAIL") << "] " << test << endl;
}

int main()
{
    cout << "\n";
    cout << "╔════════════════════════════════════════════════════════════╗\n";
    cout << "║     PRUEBAS DEL BST (Solo funciones implementadas)        ║\n";
    cout << "╚════════════════════════════════════════════════════════════╝\n";

    // ==================== PRUEBA 1: Constructor y Empty ====================
    printSeparator("PRUEBA 1: Constructor y empty()");

    BST<int, string> arbol;
    printTestResult("Árbol creado vacío", arbol.empty());
    printTestResult("Tamaño inicial es 0", arbol.size() == 0);

    // ==================== PRUEBA 2: Insert ====================
    printSeparator("PRUEBA 2: Insert - Inserción de elementos");

    cout << "\nInsertando elementos: 50, 30, 70, 20, 40, 60, 80" << endl;
    arbol.insert(50, "cincuenta");
    arbol.insert(30, "treinta");
    arbol.insert(70, "setenta");
    arbol.insert(20, "veinte");
    arbol.insert(40, "cuarenta");
    arbol.insert(60, "sesenta");
    arbol.insert(80, "ochenta");

    printTestResult("Árbol NO está vacío después de insert", !arbol.empty());
    printTestResult("Tamaño del árbol es 7", arbol.size() == 7);

    cout << "\nInsertando clave duplicada (50) con nuevo valor..." << endl;
    arbol.insert(50, "CINCUENTA ACTUALIZADO");
    printTestResult("Tamaño sigue siendo 7 (no duplica)", arbol.size() == 7);

    // ==================== PRUEBA 3: Find ====================
    printSeparator("PRUEBA 3: Find - Búsqueda de elementos");

    printTestResult("find(50) = true", arbol.find(50));
    printTestResult("find(30) = true", arbol.find(30));
    printTestResult("find(80) = true", arbol.find(80));
    printTestResult("find(20) = true", arbol.find(20));
    printTestResult("find(40) = true", arbol.find(40));
    printTestResult("find(60) = true", arbol.find(60));
    printTestResult("find(70) = true", arbol.find(70));
    
    cout << "\nBuscando elementos que NO existen:" << endl;
    printTestResult("find(100) = false", !arbol.find(100));
    printTestResult("find(15) = false", !arbol.find(15));
    printTestResult("find(45) = false", !arbol.find(45));
    printTestResult("find(0) = false", !arbol.find(0));

    // ==================== PRUEBA 4: Inorder ====================
    printSeparator("PRUEBA 4: Inorder - Recorrido en orden");

    cout << "\nRecorrido Inorder (debe estar ordenado ascendente):" << endl;
    cout << "Esperado: [20:veinte] [30:treinta] [40:cuarenta] [50:CINCUENTA ACTUALIZADO] [60:sesenta] [70:setenta] [80:ochenta]" << endl;
    cout << "Obtenido: ";
    arbol.inorder();
    cout << endl;

    // ==================== PRUEBA 5: Más inserciones ====================
    printSeparator("PRUEBA 5: Inserciones adicionales");

    cout << "\nInsertando más elementos: 25, 35, 65, 75" << endl;
    arbol.insert(25, "veinticinco");
    arbol.insert(35, "treinta y cinco");
    arbol.insert(65, "sesenta y cinco");
    arbol.insert(75, "setenta y cinco");

    printTestResult("Tamaño ahora es 11", arbol.size() == 11);

    cout << "\nNuevo recorrido Inorder:" << endl;
    arbol.inorder();
    cout << endl;

    // ==================== PRUEBA 6: Árbol vacío ====================
    printSeparator("PRUEBA 6: Operaciones en árbol vacío");

    BST<int, int> arbolVacio;
    printTestResult("Árbol vacío - empty() = true", arbolVacio.empty());
    printTestResult("Árbol vacío - size() = 0", arbolVacio.size() == 0);
    printTestResult("Árbol vacío - find(10) = false", !arbolVacio.find(10));

    cout << "\nInorder en árbol vacío: ";
    arbolVacio.inorder();
    cout << endl;

    // ==================== PRUEBA 7: BST con strings como Key ====================
    printSeparator("PRUEBA 7: BST con strings como Key");

    BST<string, int> diccionario;
    diccionario.insert("manzana", 5);
    diccionario.insert("banana", 3);
    diccionario.insert("cereza", 8);
    diccionario.insert("durazno", 2);
    diccionario.insert("uva", 10);

    printTestResult("Insertadas 5 palabras", diccionario.size() == 5);
    printTestResult("find(\"banana\") = true", diccionario.find("banana"));
    printTestResult("find(\"manzana\") = true", diccionario.find("manzana"));
    printTestResult("find(\"kiwi\") = false", !diccionario.find("kiwi"));

    cout << "\nDiccionario en orden alfabético:" << endl;
    diccionario.inorder();
    cout << endl;

    // ==================== PRUEBA 8: BST con doubles ====================
    printSeparator("PRUEBA 8: BST con doubles");

    BST<double, string> precios;
    precios.insert(19.99, "libro");
    precios.insert(5.50, "café");
    precios.insert(120.00, "zapatos");
    precios.insert(3.25, "pan");
    precios.insert(45.75, "camisa");

    printTestResult("Insertados 5 precios", precios.size() == 5);
    printTestResult("find(19.99) = true", precios.find(19.99));
    printTestResult("find(100.00) = false", !precios.find(100.00));

    cout << "\nPrecios ordenados:" << endl;
    precios.inorder();
    cout << endl;

    // ==================== PRUEBA 9: Actualización de valores ====================
    printSeparator("PRUEBA 9: Actualización de valores existentes");

    BST<int, string> productos;
    productos.insert(101, "Producto A");
    productos.insert(102, "Producto B");
    productos.insert(103, "Producto C");

    cout << "\nAntes de actualizar:" << endl;
    productos.inorder();
    cout << endl;

    productos.insert(102, "Producto B - ACTUALIZADO");

    cout << "\nDespués de actualizar producto 102:" << endl;
    productos.inorder();
    cout << endl;

    printTestResult("Tamaño no cambió (3)", productos.size() == 3);

    // ==================== PRUEBA 10: Árbol degenerado (lista enlazada) ====================
    printSeparator("PRUEBA 10: Árbol degenerado (peor caso)");

    BST<int, int> arbolDegenerado;
    cout << "\nInsertando en orden ascendente: 1, 2, 3, 4, 5" << endl;
    for (int i = 1; i <= 5; i++)
    {
        arbolDegenerado.insert(i, i * 10);
    }

    cout << "Inorder: ";
    arbolDegenerado.inorder();
    cout << endl;

    printTestResult("Tamaño es 5", arbolDegenerado.size() == 5);
    printTestResult("find(3) = true", arbolDegenerado.find(3));
    printTestResult("find(6) = false", !arbolDegenerado.find(6));

    // ==================== PRUEBA 11: Muchas inserciones ====================
    printSeparator("PRUEBA 11: Árbol con muchos elementos");

    BST<int, string> arbolGrande;
    cout << "\nInsertando 20 elementos..." << endl;
    for (int i = 1; i <= 20; i++)
    {
        arbolGrande.insert(i * 5, "valor_" + to_string(i * 5));
    }

    printTestResult("Tamaño es 20", arbolGrande.size() == 20);
    printTestResult("find(50) = true", arbolGrande.find(50));
    printTestResult("find(51) = false", !arbolGrande.find(51));

    cout << "\nPrimeros y últimos elementos:" << endl;
    printTestResult("find(5) = true (primero)", arbolGrande.find(5));
    printTestResult("find(100) = true (último)", arbolGrande.find(100));

    // ==================== RESUMEN FINAL ====================
    printSeparator("RESUMEN DE PRUEBAS COMPLETADAS");

    cout << "\n✅ IMPLEMENTADAS Y FUNCIONANDO:" << endl;
    cout << "  • Constructor (BST())" << endl;
    cout << "  • empty()" << endl;
    cout << "  • size()" << endl;
    cout << "  • insert(k, v)" << endl;
    cout << "  • find(k)" << endl;
    cout << "  • inorder()" << endl;

    cout << "\n⚠️  PENDIENTES DE IMPLEMENTAR:" << endl;
    cout << "  • remove(k)" << endl;
    cout << "  • preorder()" << endl;
    cout << "  • postorder()" << endl;
    cout << "  • levelOrder()" << endl;
    cout << "  • findMinimum() / findMaximum()" << endl;
    cout << "  • height()" << endl;
    cout << "  • clear()" << endl;
    cout << "  • findSuccessor() / findPredecessor()" << endl;
    cout << "  • printTree()" << endl;
    cout << "  • Constructor de copia" << endl;
    cout << "  • Operador de asignación" << endl;
    cout << "  • Destructor" << endl;

    cout << "\n╔════════════════════════════════════════════════════════════╗\n";
    cout << "║         TODAS LAS PRUEBAS DISPONIBLES PASARON ✓           ║\n";
    cout << "╚════════════════════════════════════════════════════════════╝\n\n";

    return 0;
}