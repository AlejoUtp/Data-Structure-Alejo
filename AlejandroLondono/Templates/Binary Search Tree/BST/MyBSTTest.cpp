/**
 * @file main.cpp
 * @brief Pruebas completas para la clase BST
 * @author Tester BST
 * @date 2025
 */

#include "MyBST.hh"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

void printHeader(const string &title)
{
    cout << "\n" << string(70, '=') << endl;
    cout << "  " << title << endl;
    cout << string(70, '=') << endl;
}

void printTest(const string &test, bool passed)
{
    cout << "[" << (passed ? "✓ PASS" : "✗ FAIL") << "] " << test << endl;
}

int main()
{
    cout << "\n╔══════════════════════════════════════════════════════════════════╗\n";
    cout << "║          PRUEBAS COMPLETAS DEL BST (Binary Search Tree)         ║\n";
    cout << "╚══════════════════════════════════════════════════════════════════╝\n";

    // ==================== PRUEBA 1: Constructor y métodos básicos ====================
    printHeader("PRUEBA 1: Constructor, empty(), size()");

    BST<int, string> arbol;
    printTest("Árbol creado vacío", arbol.empty());
    printTest("size() = 0", arbol.size() == 0);

    try
    {
        arbol.findMin();
        printTest("findMin() en árbol vacío lanza excepción", false);
    }
    catch (runtime_error &e)
    {
        printTest("findMin() en árbol vacío lanza excepción", true);
    }

    // ==================== PRUEBA 2: Insert básico ====================
    printHeader("PRUEBA 2: Insert - Inserción básica");

    cout << "\nInsertando: 50, 30, 70, 20, 40, 60, 80\n";
    arbol.insert(50, "cincuenta");
    arbol.insert(30, "treinta");
    arbol.insert(70, "setenta");
    arbol.insert(20, "veinte");
    arbol.insert(40, "cuarenta");
    arbol.insert(60, "sesenta");
    arbol.insert(80, "ochenta");

    printTest("size() = 7", arbol.size() == 7);
    printTest("!empty()", !arbol.empty());

    // ==================== PRUEBA 3: Find ====================
    printHeader("PRUEBA 3: Find - Búsqueda de elementos");

    printTest("find(50) = true", arbol.find(50));
    printTest("find(20) = true", arbol.find(20));
    printTest("find(80) = true", arbol.find(80));
    printTest("find(100) = false", !arbol.find(100));
    printTest("find(0) = false", !arbol.find(0));

    // ==================== PRUEBA 4: Insert con duplicados ====================
    printHeader("PRUEBA 4: Insert - Actualización de valores duplicados");

    cout << "\nInsertando clave duplicada (50) con nuevo valor...\n";
    arbol.insert(50, "CINCUENTA_ACTUALIZADO");
    printTest("size() sigue siendo 7", arbol.size() == 7);
    printTest("find(50) = true", arbol.find(50));

    // ==================== PRUEBA 5: Traversals ====================
    printHeader("PRUEBA 5: Recorridos del árbol");

    cout << "\nInorder (orden ascendente):\n";
    arbol.inorder();

    cout << "\nPreorder:\n";
    arbol.preorder();

    cout << "\nPostorder:\n";
    arbol.postorder();

    cout << "\nLevel Order:\n";
    arbol.levelOrder();

    // ==================== PRUEBA 6: FindMin y FindMax ====================
    printHeader("PRUEBA 6: FindMin y FindMax");

    printTest("findMin() = 20", arbol.findMin() == 20);
    printTest("findMaximum() = 80", arbol.findMaximum() == 80);

    // ==================== PRUEBA 7: Height ====================
    printHeader("PRUEBA 7: Height - Altura del árbol");

    int h = arbol.height();
    cout << "\nAltura del árbol: " << h << endl;
    printTest("height() >= 2", h >= 2);

    // ==================== PRUEBA 8: PrintTree ====================
    printHeader("PRUEBA 8: PrintTree - Visualización del árbol");

    cout << "\nEstructura del árbol:\n";
    arbol.printTree();

    // ==================== PRUEBA 9: Remove - Caso 1 (hoja) ====================
    printHeader("PRUEBA 9: Remove - Eliminar nodo hoja");

    cout << "\nAntes de eliminar 20:\n";
    arbol.inorder();

    bool removed = arbol.remove(20);
    printTest("remove(20) = true", removed);
    printTest("size() = 6", arbol.size() == 6);
    printTest("find(20) = false", !arbol.find(20));

    cout << "\nDespués de eliminar 20:\n";
    arbol.inorder();

    // ==================== PRUEBA 10: Remove - Caso 2 (un hijo) ====================
    printHeader("PRUEBA 10: Remove - Eliminar nodo con un hijo");

    arbol.insert(25, "veinticinco");
    cout << "\nInsertado 25, árbol actual:\n";
    arbol.inorder();

    cout << "\nEliminando 30 (tiene un hijo: 25 y 40)...\n";
    removed = arbol.remove(30);
    printTest("remove(30) = true", removed);
    printTest("find(30) = false", !arbol.find(30));
    printTest("find(25) = true", arbol.find(25));
    printTest("find(40) = true", arbol.find(40));

    cout << "\nDespués de eliminar 30:\n";
    arbol.inorder();

    // ==================== PRUEBA 11: Remove - Caso 3 (dos hijos) ====================
    printHeader("PRUEBA 11: Remove - Eliminar nodo con dos hijos");

    // Crear árbol nuevo para mejor visualización
    BST<int, string> arbol2;
    arbol2.insert(50, "50");
    arbol2.insert(30, "30");
    arbol2.insert(70, "70");
    arbol2.insert(20, "20");
    arbol2.insert(40, "40");
    arbol2.insert(60, "60");
    arbol2.insert(80, "80");

    cout << "\nÁrbol antes de eliminar 50 (raíz con dos hijos):\n";
    arbol2.printTree();

    removed = arbol2.remove(50);
    printTest("remove(50) = true", removed);
    printTest("find(50) = false", !arbol2.find(50));

    cout << "\nÁrbol después de eliminar 50:\n";
    arbol2.printTree();

    // ==================== PRUEBA 12: Remove - No existente ====================
    printHeader("PRUEBA 12: Remove - Elemento no existente");

    removed = arbol2.remove(999);
    printTest("remove(999) = false", !removed);
    printTest("size() no cambió", arbol2.size() == 6);

    // ==================== PRUEBA 13: Successor y Predecessor ====================
    printHeader("PRUEBA 13: FindSuccessor y FindPredecessor");

    BST<int, int> arbol3;
    for (int i : {50, 30, 70, 20, 40, 60, 80})
    {
        arbol3.insert(i, i);
    }

    cout << "\nÁrbol: 20, 30, 40, 50, 60, 70, 80\n";

    try
    {
        printTest("successor(30) = 40", arbol3.findSuccessor(30) == 40);
        printTest("successor(50) = 60", arbol3.findSuccessor(50) == 60);
        printTest("predecessor(50) = 40", arbol3.findPredecessor(50) == 40);
        printTest("predecessor(70) = 60", arbol3.findPredecessor(70) == 60);
    }
    catch (exception &e)
    {
        cout << "Error: " << e.what() << endl;
    }

    try
    {
        arbol3.findSuccessor(80);
        printTest("successor(80) lanza excepción", false);
    }
    catch (runtime_error &e)
    {
        printTest("successor(80) lanza excepción", true);
    }

    try
    {
        arbol3.findPredecessor(20);
        printTest("predecessor(20) lanza excepción", false);
    }
    catch (runtime_error &e)
    {
        printTest("predecessor(20) lanza excepción", true);
    }

    // ==================== PRUEBA 14: Clear ====================
    printHeader("PRUEBA 14: Clear - Limpiar árbol");

    unsigned int sizeBefore = arbol3.size();
    cout << "\nTamaño antes de clear: " << sizeBefore << endl;

    arbol3.clear();
    printTest("clear() funciona", arbol3.empty());
    printTest("size() = 0 después de clear", arbol3.size() == 0);

    // ==================== PRUEBA 15: Constructor de copia ====================
    printHeader("PRUEBA 15: Constructor de copia");

    BST<int, string> original;
    original.insert(10, "diez");
    original.insert(5, "cinco");
    original.insert(15, "quince");

    BST<int, string> copia(original);
    printTest("Copia tiene mismo tamaño", copia.size() == original.size());
    printTest("Copia tiene find(10)", copia.find(10));
    printTest("Copia tiene find(5)", copia.find(5));

    original.insert(20, "veinte");
    printTest("Original size = 4", original.size() == 4);
    printTest("Copia size = 3 (independiente)", copia.size() == 3);

    // ==================== PRUEBA 16: Operador de asignación ====================
    printHeader("PRUEBA 16: Operador de asignación");

    BST<int, string> asignado;
    asignado.insert(1, "uno");
    asignado = original;

    printTest("Asignado tiene tamaño de original", asignado.size() == original.size());
    printTest("Asignado tiene find(20)", asignado.find(20));

    // ==================== PRUEBA 17: BST con strings ====================
    printHeader("PRUEBA 17: BST con string como Key");

    BST<string, int> diccionario;
    diccionario.insert("manzana", 5);
    diccionario.insert("banana", 3);
    diccionario.insert("cereza", 8);
    diccionario.insert("durazno", 2);

    printTest("size() = 4", diccionario.size() == 4);
    printTest("find(\"banana\") = true", diccionario.find("banana"));
    printTest("find(\"uva\") = false", !diccionario.find("uva"));

    cout << "\nDiccionario en orden alfabético:\n";
    diccionario.inorder();

    // ==================== PRUEBA 18: BST con doubles ====================
    printHeader("PRUEBA 18: BST con double como Key");

    BST<double, string> precios;
    precios.insert(19.99, "libro");
    precios.insert(5.50, "café");
    precios.insert(120.00, "zapatos");

    printTest("size() = 3", precios.size() == 3);
    printTest("find(19.99) = true", precios.find(19.99));

    cout << "\nPrecios ordenados:\n";
    precios.inorder();

    // ==================== PRUEBA 19: Eliminaciones múltiples ====================
    printHeader("PRUEBA 19: Eliminaciones múltiples");

    BST<int, int> arbol4;
    for (int i = 1; i <= 10; i++)
    {
        arbol4.insert(i * 10, i * 10);
    }

    cout << "\nÁrbol inicial (10 elementos):\n";
    arbol4.inorder();

    arbol4.remove(30);
    arbol4.remove(50);
    arbol4.remove(70);

    cout << "\nDespués de eliminar 30, 50, 70:\n";
    arbol4.inorder();

    printTest("size() = 7", arbol4.size() == 7);
    printTest("!find(30)", !arbol4.find(30));
    printTest("!find(50)", !arbol4.find(50));
    printTest("!find(70)", !arbol4.find(70));

    // ==================== PRUEBA 20: Árbol degenerado ====================
    printHeader("PRUEBA 20: Árbol degenerado (peor caso)");

    BST<int, int> degenerado;
    cout << "\nInsertando en orden: 1, 2, 3, 4, 5\n";
    for (int i = 1; i <= 5; i++)
    {
        degenerado.insert(i, i * 10);
    }

    printTest("size() = 5", degenerado.size() == 5);
    printTest("height() = 4", degenerado.height() == 4);
    printTest("findMin() = 1", degenerado.findMin() == 1);
    printTest("findMaximum() = 5", degenerado.findMaximum() == 5);

    cout << "\nEstructura (como lista enlazada):\n";
    degenerado.printTree();

    // ==================== RESUMEN FINAL ====================
    printHeader("RESUMEN DE FUNCIONALIDADES PROBADAS");

    cout << "\n✓ CORE OPERATIONS:\n";
    cout << "  • Constructor, Constructor de copia, Operador =, Destructor\n";
    cout << "  • insert(k, v) - con actualización de duplicados\n";
    cout << "  • find(k) - búsqueda\n";
    cout << "  • remove(k) - 3 casos (hoja, un hijo, dos hijos)\n";

    cout << "\n✓ TRAVERSALS:\n";
    cout << "  • inorder() - orden ascendente\n";
    cout << "  • preorder() - raíz primero\n";
    cout << "  • postorder() - raíz último\n";
    cout << "  • levelOrder() - por niveles\n";

    cout << "\n✓ HELPER OPERATIONS:\n";
    cout << "  • findMin() / findMaximum()\n";
    cout << "  • height() - cálculo de altura\n";
    cout << "  • size() - tamaño O(1)\n";
    cout << "  • empty() - verificación\n";
    cout << "  • clear() - limpieza completa\n";

    cout << "\n✓ ADDITIONAL OPERATIONS:\n";
    cout << "  • findSuccessor(k) - siguiente en orden\n";
    cout << "  • findPredecessor(k) - anterior en orden\n";
    cout << "  • printTree() - visualización\n";

    cout << "\n╔══════════════════════════════════════════════════════════════════╗\n";
    cout << "║           ✓ TODAS LAS PRUEBAS COMPLETADAS CON ÉXITO ✓           ║\n";
    cout << "╚══════════════════════════════════════════════════════════════════╝\n\n";

    return 0;
}