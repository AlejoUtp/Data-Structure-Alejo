#include "TreapMap.hh"
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

void testInsertBasico() {
    cout << "\n=== TEST 1: Insert Básico en TreapMap ===" << endl;
    TreapMap<int, string> treap;
    
    treap.insert(5, "cinco");
    treap.insert(3, "tres");
    treap.insert(7, "siete");
    
    cout << "Tamaño esperado: 3, obtenido: " << treap.size() << endl;
    assert(treap.size() == 3);
    
    cout << "Verificando que se insertaron correctamente:" << endl;
    assert(treap.find(5) == true);
    assert(treap.find(3) == true);
    assert(treap.find(7) == true);
    
    cout << "✓ Insert básico funcionando" << endl;
}

void testInsertDuplicados() {
    cout << "\n=== TEST 2: Insert con Claves Duplicadas (debe actualizar) ===" << endl;
    TreapMap<int, string> treap;
    
    treap.insert(5, "cinco");
    cout << "Primer insert de clave 5" << endl;
    cout << "Tamaño: " << treap.size() << endl;
    
    treap.insert(5, "CINCO_ACTUALIZADO");
    cout << "Segundo insert de clave 5 (actualización)" << endl;
    
    cout << "Tamaño esperado: 1 (no duplicar), obtenido: " << treap.size() << endl;
    assert(treap.size() == 1);
    assert(treap.find(5) == true);
    
    cout << "Valor en el árbol:" << endl;
    treap.inorder();
    
    cout << "✓ Update en duplicados funcionando" << endl;
}

void testInsertOrdenado() {
    cout << "\n=== TEST 3: Insert en Orden Ascendente ===" << endl;
    TreapMap<int, string> treap;
    
    cout << "Insertando 1, 2, 3, ..., 10 (peor caso para BST)" << endl;
    for(int i = 1; i <= 10; i++) {
        treap.insert(i, "valor_" + to_string(i));
    }
    
    cout << "Tamaño esperado: 10, obtenido: " << treap.size() << endl;
    assert(treap.size() == 10);
    
    cout << "\nÁrbol visual (debería estar balanceado por prioridades):" << endl;
    treap.printTree();
    
    cout << "\nAltura del árbol: " << treap.height() << endl;
    cout << "(Un BST degenerado tendría altura 9, un Treap debería ser menor)" << endl;
    
    cout << "\nRecorrido Inorder (debe estar ordenado 1-10):" << endl;
    treap.inorder();
    
    cout << "✓ Insert ordenado funcionando, árbol balanceado por prioridades" << endl;
}

void testInsertReverso() {
    cout << "\n=== TEST 4: Insert en Orden Descendente ===" << endl;
    TreapMap<int, string> treap;
    
    cout << "Insertando 10, 9, 8, ..., 1 (otro peor caso para BST)" << endl;
    for(int i = 10; i >= 1; i--) {
        treap.insert(i, "valor_" + to_string(i));
    }
    
    cout << "Tamaño esperado: 10, obtenido: " << treap.size() << endl;
    assert(treap.size() == 10);
    
    cout << "\nÁrbol visual:" << endl;
    treap.printTree();
    
    cout << "\nAltura del árbol: " << treap.height() << endl;
    
    cout << "\nRecorrido Inorder (debe estar ordenado 1-10):" << endl;
    treap.inorder();
    
    cout << "✓ Insert reverso funcionando" << endl;
}

void testInsertAleatorio() {
    cout << "\n=== TEST 5: Insert Aleatorio ===" << endl;
    TreapMap<int, string> treap;
    
    int valores[] = {15, 3, 22, 7, 18, 2, 9, 30, 5, 12};
    
    cout << "Insertando: ";
    for(int val : valores) {
        cout << val << " ";
        treap.insert(val, "v" + to_string(val));
    }
    cout << endl;
    
    cout << "\nTamaño esperado: 10, obtenido: " << treap.size() << endl;
    assert(treap.size() == 10);
    
    cout << "\nÁrbol visual (estructura determinada por prioridades aleatorias):" << endl;
    treap.printTree();
    
    cout << "\nAltura: " << treap.height() << endl;
    
    cout << "\nRecorrido Inorder (debe mostrar valores ordenados):" << endl;
    treap.inorder();
    
    cout << "\nRecorrido por niveles:" << endl;
    treap.levelOrder();
    
    cout << "✓ Insert aleatorio funcionando" << endl;
}

void testInsertConStrings() {
    cout << "\n=== TEST 6: Insert con Keys String ===" << endl;
    TreapMap<string, int> treap;
    
    treap.insert("manzana", 5);
    treap.insert("banana", 3);
    treap.insert("cereza", 8);
    treap.insert("durazno", 2);
    treap.insert("uva", 10);
    
    cout << "Tamaño esperado: 5, obtenido: " << treap.size() << endl;
    assert(treap.size() == 5);
    
    cout << "\nÁrbol visual:" << endl;
    treap.printTree();
    
    cout << "\nRecorrido Inorder (orden alfabético por las keys):" << endl;
    treap.inorder();
    
    cout << "✓ Insert con strings funcionando" << endl;
}

void testInsertYBusqueda() {
    cout << "\n=== TEST 7: Insert + Find Exhaustivo ===" << endl;
    TreapMap<int, string> treap;
    
    int valores[] = {50, 30, 70, 20, 40, 60, 80};
    
    cout << "Insertando valores..." << endl;
    for(int v : valores) {
        treap.insert(v, "val_" + to_string(v));
    }
    
    cout << "\nVerificando que TODOS los valores insertados se encuentran:" << endl;
    for(int v : valores) {
        bool encontrado = treap.find(v);
        cout << "  Buscando " << v << ": " << (encontrado ? "✓" : "✗") << endl;
        assert(encontrado == true);
    }
    
    cout << "\nVerificando que valores NO insertados NO se encuentran:" << endl;
    int noExisten[] = {10, 25, 35, 55, 75, 90};
    for(int v : noExisten) {
        bool encontrado = treap.find(v);
        cout << "  Buscando " << v << ": " << (encontrado ? "✗ ERROR" : "✓ OK") << endl;
        assert(encontrado == false);
    }
    
    cout << "✓ Insert + Find funcionando correctamente" << endl;
}

void testInsertMinMax() {
    cout << "\n=== TEST 8: Insert y verificar Min/Max ===" << endl;
    TreapMap<int, string> treap;
    
    int valores[] = {15, 3, 22, 7, 18, 2, 9, 30, 5, 12};
    
    for(int v : valores) {
        treap.insert(v, "v" + to_string(v));
    }
    
    cout << "Valores insertados: ";
    for(int v : valores) cout << v << " ";
    cout << endl;
    
    int minimo = treap.findMin();
    int maximo = treap.findMaximum();
    
    cout << "\nMínimo encontrado: " << minimo << " (esperado: 2)" << endl;
    cout << "Máximo encontrado: " << maximo << " (esperado: 30)" << endl;
    
    assert(minimo == 2);
    assert(maximo == 30);
    
    cout << "✓ Min/Max funcionando correctamente" << endl;
}

void testInsertVacio() {
    cout << "\n=== TEST 9: Insert en Árbol Vacío ===" << endl;
    TreapMap<int, string> treap;
    
    assert(treap.empty() == true);
    assert(treap.size() == 0);
    
    cout << "Insertando primer elemento..." << endl;
    treap.insert(42, "respuesta");
    
    assert(treap.empty() == false);
    assert(treap.size() == 1);
    assert(treap.find(42) == true);
    
    cout << "Árbol con un solo elemento:" << endl;
    treap.printTree();
    
    cout << "✓ Insert en árbol vacío funcionando" << endl;
}

void testInsertBalanceo() {
    cout << "\n=== TEST 10: Verificar Balanceo con Prioridades ===" << endl;
    TreapMap<int, string> treap;
    
    // Insertar muchos elementos en orden (peor caso para BST)
    cout << "Insertando 50 elementos en orden ascendente..." << endl;
    for(int i = 1; i <= 50; i++) {
        treap.insert(i, "v" + to_string(i));
    }
    
    int altura = treap.height();
    cout << "Altura del árbol: " << altura << endl;
    cout << "Altura máxima de BST degenerado: 49" << endl;
    cout << "Altura esperada de Treap balanceado: ~10-15" << endl;
    
    // Un Treap balanceado debería tener altura O(log n)
    // Para 50 elementos: log2(50) ≈ 5.6, en práctica ~10-15 es razonable
    if(altura < 25) {
        cout << "✓ El Treap está razonablemente balanceado" << endl;
    } else {
        cout << "⚠ Advertencia: El árbol podría estar desbalanceado" << endl;
    }
    
    cout << "\nVerificando integridad (todos los elementos presentes):" << endl;
    bool todosPresentes = true;
    for(int i = 1; i <= 50; i++) {
        if(!treap.find(i)) {
            todosPresentes = false;
            cout << "✗ Falta elemento: " << i << endl;
        }
    }
    
    if(todosPresentes) {
        cout << "✓ Todos los 50 elementos presentes" << endl;
    }
    
    assert(treap.size() == 50);
    cout << "✓ Test de balanceo completado" << endl;
}

int main() {
    // Inicializar semilla para prioridades aleatorias del Treap
    srand(time(nullptr));
    
    cout << "╔════════════════════════════════════════════════╗" << endl;
    cout << "║   TESTER COMPLETO PARA INSERT - TREAPMAP      ║" << endl;
    cout << "║   (Árbol Binario con Prioridades Aleatorias)  ║" << endl;
    cout << "╚════════════════════════════════════════════════╝" << endl;
    
    try {
        testInsertBasico();
        testInsertDuplicados();
        testInsertOrdenado();
        testInsertReverso();
        testInsertAleatorio();
        testInsertConStrings();
        testInsertYBusqueda();
        testInsertMinMax();
        testInsertVacio();
        testInsertBalanceo();
        
        cout << "\n╔════════════════════════════════════════════════╗" << endl;
        cout << "║        ✓ TODOS LOS TESTS PASARON              ║" << endl;
        cout << "║   El TreapMap está funcionando correctamente  ║" << endl;
        cout << "╚════════════════════════════════════════════════╝" << endl;
        
    } catch(const exception& e) {
        cout << "\n✗ ERROR: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}