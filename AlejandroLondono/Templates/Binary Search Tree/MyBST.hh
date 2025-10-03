#ifndef __BST__
#define __BST__

template <typename Key, typename Value>
class BST
{

private:
    class Node
    {
    private:
        Key key;
        Value value;
        Node *left;
        Node *right;

    public:
        Node(const Key &k, const Value &v) : key(k), value(v), left(nullptr), right(nullptr) {}

        const Key &getKey() const { return key; }
        const Value &getValue() const { return value; }

        Node* getLeft() const { return left;}
        Node* getRight() const { return right;}

        void setLeft(Node *n) { left = n; }
        void setRight(Node *n) { right = n; }
        void setValue(const Value &v) { value = v; }

        bool hasLeft() const { return left != nullptr;}
        bool hasRight() const { return right != nullptr;}
    }

    private:
    Node* root;  ///< Raíz del árbol
    unsigned int sz; 

    // ==================== MÉTODOS AUXILIARES PRIVADOS ====================
    
    /**
     * @brief Inserta un nodo recursivamente
     * @param node Nodo actual en la recursión
     * @param value Valor a insertar
     * @return Puntero al nodo actualizado
     */
    Node* insertHelper(Node* node, const Key &k, const Value &v);
    
    /**
     * @brief Busca un nodo recursivamente
     * @param node Nodo actual en la recursión
     * @param value Valor a buscar
     * @return Puntero al nodo encontrado o nullptr
     */
    Node* searchHelper(Node* node, const Key &k );
    
    /**
     * @brief Elimina un nodo recursivamente
     * @param node Nodo actual en la recursión
     * @param value Valor a eliminar
     * @return Puntero al nodo actualizado
     */
    Node* deleteHelper(Node* node, int value);
    
    /**
     * @brief Encuentra el nodo con valor mínimo en un subárbol
     * @param node Raíz del subárbol
     * @return Puntero al nodo con valor mínimo
     */
    Node* findMinHelper(Node* node);
    
    /**
     * @brief Encuentra el nodo con valor máximo en un subárbol
     * @param node Raíz del subárbol
     * @return Puntero al nodo con valor máximo
     */
    Node* findMaxHelper(Node* node);
    
    /**
     * @brief Recorrido inorden recursivo
     * @param node Nodo actual en la recursión
     */
    void inorderHelper(Node* node);
    
    /**
     * @brief Recorrido preorden recursivo
     * @param node Nodo actual en la recursión
     */
    void preorderHelper(Node* node);
    
    /**
     * @brief Recorrido postorden recursivo
     * @param node Nodo actual en la recursión
     */
    void postorderHelper(Node* node);
    
    /**
     * @brief Calcula la altura del árbol recursivamente
     * @param node Nodo actual en la recursión
     * @return Altura del subárbol
     */
    int heightHelper(Node* node);
    
    /**
     * @brief Cuenta los nodos del árbol recursivamente
     * @param node Nodo actual en la recursión
     * @return Número de nodos en el subárbol
     */
    int countNodesHelper(Node* node);
    
    /**
     * @brief Elimina todos los nodos del árbol recursivamente
     * @param node Nodo actual en la recursión
     */
    void clearHelper(Node* node);
    
    /**
     * @brief Copia un árbol recursivamente
     * @param node Nodo del árbol a copiar
     * @return Puntero al nuevo nodo copiado
     */
    Node* copyHelper(Node* node);
    
    /**
     * @brief Imprime el árbol de forma visual
     * @param node Nodo actual
     * @param prefix Prefijo para la indentación
     * @param isLeft Indica si es hijo izquierdo
     */
    void printTreeHelper(Node* node, std::string prefix, bool isLeft);

public:
    // ==================== CORE OPERATIONS ====================
    
    /**
     * @brief Constructor por defecto - Crea un BST vacío
     * @complexity O(1)
     */
    BST() : root(nullptr), sz(0) {}
    
    /**
     * @brief Constructor de copia
     * @param other Árbol a copiar
     * @complexity O(n)
     */
    BST(const BST& other);
    
    /**
     * @brief Operador de asignación
     * @param other Árbol a copiar
     * @return Referencia al árbol actual
     * @complexity O(n)
     */
    BST& operator=(const BST& other);
    
    /**
     * @brief Destructor - Libera toda la memoria
     * @complexity O(n)
     */
    ~BST();
    
    /**
     * @brief Inserta un nuevo valor en el árbol
     * @param value Valor a insertar
     * @complexity O(log n) en promedio, O(n) en el peor caso
     * 
     * Mantiene la propiedad del BST: valores menores a la izquierda,
     * mayores a la derecha. No permite duplicados.
     */
    void insert(int value);
    
    /**
     * @brief Busca un valor en el árbol
     * @param value Valor a buscar
     * @return true si el valor existe, false en caso contrario
     * @complexity O(log n) en promedio, O(n) en el peor caso
     */
    bool search(int value);
    
    /**
     * @brief Elimina un valor del árbol
     * @param value Valor a eliminar
     * @return true si se eliminó correctamente, false si no existía
     * @complexity O(log n) en promedio, O(n) en el peor caso
     * 
     * Esta es la operación más compleja. Maneja 3 casos:
     * 1. Nodo sin hijos (hoja)
     * 2. Nodo con un hijo
     * 3. Nodo con dos hijos (usa sucesor inorden)
     */
    bool remove(int value);
    
    // ==================== TRAVERSALS ====================
    
    /**
     * @brief Recorrido Inorden (Izquierda-Raíz-Derecha)
     * @complexity O(n)
     * 
     * Imprime los valores en orden ascendente
     */
    void inorder();
    
    /**
     * @brief Recorrido Preorden (Raíz-Izquierda-Derecha)
     * @complexity O(n)
     * 
     * Útil para copiar el árbol o serialización
     */
    void preorder();
    
    /**
     * @brief Recorrido Postorden (Izquierda-Derecha-Raíz)
     * @complexity O(n)
     * 
     * Útil para eliminar el árbol o evaluación de expresiones
     */
    void postorder();
    
    /**
     * @brief Recorrido por niveles (Breadth-First)
     * @complexity O(n)
     * 
     * Visita todos los nodos nivel por nivel
     */
    void levelOrder();
    
    // ==================== HELPER OPERATIONS ====================
    
    /**
     * @brief Encuentra el valor mínimo del árbol
     * @return Valor mínimo (nodo más a la izquierda)
     * @throw std::runtime_error si el árbol está vacío
     * @complexity O(log n) en promedio, O(n) en el peor caso
     */
    Value findMinimum();
    
    /**
     * @brief Encuentra el valor máximo del árbol
     * @return Valor máximo (nodo más a la derecha)
     * @throw std::runtime_error si el árbol está vacío
     * @complexity O(log n) en promedio, O(n) en el peor caso
     */
    Value findMaximum();
    
    /**
     * @brief Calcula la altura del árbol
     * @return Altura (número de aristas en el camino más largo)
     * @complexity O(n)
     * 
     * Un árbol vacío tiene altura -1, un árbol con solo raíz tiene altura 0
     */
    Value height();
    
    /**
     * @brief Cuenta el número total de nodos
     * @return Número de nodos en el árbol
     * @complexity O(n)
     */
    Value countNodes();
    
    /**
     * @brief Verifica si el árbol está vacío
     * @return true si está vacío, false en caso contrario
     * @complexity O(1)
     */
    bool isEmpty() const {return root == nullptr; };
    
    /**
     * @brief Elimina todos los nodos del árbol
     * @complexity O(n)
     * 
     * Libera toda la memoria y deja el árbol vacío
     */
    void clear();

    unsigned int size() const { return sz; }

    
    // ==================== ADDITIONAL USEFUL OPERATIONS ====================
    
    /**
     * @brief Encuentra el sucesor de un valor (siguiente en orden)
     * @param value Valor cuyo sucesor se busca
     * @return Valor del sucesor
     * @throw std::runtime_error si no existe sucesor
     * @complexity O(log n) en promedio
     * 
     * El sucesor es el menor valor mayor que el valor dado
     */
    int findSuccessor(int value);
    
    /**
     * @brief Encuentra el predecesor de un valor (anterior en orden)
     * @param value Valor cuyo predecesor se busca
     * @return Valor del predecesor
     * @throw std::runtime_error si no existe predecesor
     * @complexity O(log n) en promedio
     * 
     * El predecesor es el mayor valor menor que el valor dado
     */
    int findPredecessor(int value);
    
    /**
     * @brief Imprime una representación visual del árbol
     * @complexity O(n)
     * 
     * Muestra la estructura del árbol de forma jerárquica
     */
    void printTree();




}
#endif __BST__


#ifndef BST_hh
#define BST_hh

/**
 * @file BST.h
 * @brief Implementación de un Árbol Binario de Búsqueda (Binary Search Tree)
 * @author Tu Nombre
 * @date 2025
 * 
 * Este archivo contiene la implementación completa de un BST con todas
 * las operaciones comunes: inserción, búsqueda, eliminación, recorridos,
 * y funciones auxiliares.
 */

#ifndef BST_H
#define BST_H

#include <iostream>
#include <queue>
#include <algorithm>

/**
 * @class Node
 * @brief Representa un nodo del árbol binario de búsqueda
 * 
 * Cada nodo contiene un valor entero y punteros a sus hijos izquierdo y derecho.
 */
class Node {
public:
    int data;           ///< Valor almacenado en el nodo
    Node* left;         ///< Puntero al hijo izquierdo
    Node* right;        ///< Puntero al hijo derecho
    
    /**
     * @brief Constructor del nodo
     * @param value Valor a almacenar en el nodo
     */
    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

/**
 * @class BST
 * @brief Árbol Binario de Búsqueda con operaciones completas
 * 
 * Implementa todas las operaciones estándar de un BST incluyendo:
 * - Operaciones core: crear, insertar, buscar, eliminar, recorridos
 * - Operaciones auxiliares: mínimo, máximo, altura, contar nodos
 * - Operaciones adicionales: sucesor/predecesor, imprimir árbol
 */
class BST {
private:
    Node* root;  ///< Raíz del árbol
    
    // ==================== MÉTODOS AUXILIARES PRIVADOS ====================
    
    /**
     * @brief Inserta un nodo recursivamente
     * @param node Nodo actual en la recursión
     * @param value Valor a insertar
     * @return Puntero al nodo actualizado
     */
    Node* insertHelper(Node* node, int value);
    
    /**
     * @brief Busca un nodo recursivamente
     * @param node Nodo actual en la recursión
     * @param value Valor a buscar
     * @return Puntero al nodo encontrado o nullptr
     */
    Node* searchHelper(Node* node, int value);
    
    /**
     * @brief Elimina un nodo recursivamente
     * @param node Nodo actual en la recursión
     * @param value Valor a eliminar
     * @return Puntero al nodo actualizado
     */
    Node* deleteHelper(Node* node, int value);
    
    /**
     * @brief Encuentra el nodo con valor mínimo en un subárbol
     * @param node Raíz del subárbol
     * @return Puntero al nodo con valor mínimo
     */
    Node* findMinHelper(Node* node);
    
    /**
     * @brief Encuentra el nodo con valor máximo en un subárbol
     * @param node Raíz del subárbol
     * @return Puntero al nodo con valor máximo
     */
    Node* findMaxHelper(Node* node);
    
    /**
     * @brief Recorrido inorden recursivo
     * @param node Nodo actual en la recursión
     */
    void inorderHelper(Node* node);
    
    /**
     * @brief Recorrido preorden recursivo
     * @param node Nodo actual en la recursión
     */
    void preorderHelper(Node* node);
    
    /**
     * @brief Recorrido postorden recursivo
     * @param node Nodo actual en la recursión
     */
    void postorderHelper(Node* node);
    
    /**
     * @brief Calcula la altura del árbol recursivamente
     * @param node Nodo actual en la recursión
     * @return Altura del subárbol
     */
    int heightHelper(Node* node);
    
    /**
     * @brief Cuenta los nodos del árbol recursivamente
     * @param node Nodo actual en la recursión
     * @return Número de nodos en el subárbol
     */
    int countNodesHelper(Node* node);
    
    /**
     * @brief Elimina todos los nodos del árbol recursivamente
     * @param node Nodo actual en la recursión
     */
    void clearHelper(Node* node);
    
    /**
     * @brief Copia un árbol recursivamente
     * @param node Nodo del árbol a copiar
     * @return Puntero al nuevo nodo copiado
     */
    Node* copyHelper(Node* node);
    
    /**
     * @brief Imprime el árbol de forma visual
     * @param node Nodo actual
     * @param prefix Prefijo para la indentación
     * @param isLeft Indica si es hijo izquierdo
     */
    void printTreeHelper(Node* node, std::string prefix, bool isLeft);

public:
    // ==================== CORE OPERATIONS ====================
    
    /**
     * @brief Constructor por defecto - Crea un BST vacío
     * @complexity O(1)
     */
    BST();
    
    /**
     * @brief Constructor de copia
     * @param other Árbol a copiar
     * @complexity O(n)
     */
    BST(const BST& other);
    
    /**
     * @brief Operador de asignación
     * @param other Árbol a copiar
     * @return Referencia al árbol actual
     * @complexity O(n)
     */
    BST& operator=(const BST& other);
    
    /**
     * @brief Destructor - Libera toda la memoria
     * @complexity O(n)
     */
    ~BST();
    
    /**
     * @brief Inserta un nuevo valor en el árbol
     * @param value Valor a insertar
     * @complexity O(log n) en promedio, O(n) en el peor caso
     * 
     * Mantiene la propiedad del BST: valores menores a la izquierda,
     * mayores a la derecha. No permite duplicados.
     */
    void insert(int value);
    
    /**
     * @brief Busca un valor en el árbol
     * @param value Valor a buscar
     * @return true si el valor existe, false en caso contrario
     * @complexity O(log n) en promedio, O(n) en el peor caso
     */
    bool search(int value);
    
    /**
     * @brief Elimina un valor del árbol
     * @param value Valor a eliminar
     * @return true si se eliminó correctamente, false si no existía
     * @complexity O(log n) en promedio, O(n) en el peor caso
     * 
     * Esta es la operación más compleja. Maneja 3 casos:
     * 1. Nodo sin hijos (hoja)
     * 2. Nodo con un hijo
     * 3. Nodo con dos hijos (usa sucesor inorden)
     */
    bool remove(int value);
    
    // ==================== TRAVERSALS ====================
    
    /**
     * @brief Recorrido Inorden (Izquierda-Raíz-Derecha)
     * @complexity O(n)
     * 
     * Imprime los valores en orden ascendente
     */
    void inorder();
    
    /**
     * @brief Recorrido Preorden (Raíz-Izquierda-Derecha)
     * @complexity O(n)
     * 
     * Útil para copiar el árbol o serialización
     */
    void preorder();
    
    /**
     * @brief Recorrido Postorden (Izquierda-Derecha-Raíz)
     * @complexity O(n)
     * 
     * Útil para eliminar el árbol o evaluación de expresiones
     */
    void postorder();
    
    /**
     * @brief Recorrido por niveles (Breadth-First)
     * @complexity O(n)
     * 
     * Visita todos los nodos nivel por nivel
     */
    void levelOrder();
    
    // ==================== HELPER OPERATIONS ====================
    
    /**
     * @brief Encuentra el valor mínimo del árbol
     * @return Valor mínimo (nodo más a la izquierda)
     * @throw std::runtime_error si el árbol está vacío
     * @complexity O(log n) en promedio, O(n) en el peor caso
     */
    int findMinimum();
    
    /**
     * @brief Encuentra el valor máximo del árbol
     * @return Valor máximo (nodo más a la derecha)
     * @throw std::runtime_error si el árbol está vacío
     * @complexity O(log n) en promedio, O(n) en el peor caso
     */
    int findMaximum();
    
    /**
     * @brief Calcula la altura del árbol
     * @return Altura (número de aristas en el camino más largo)
     * @complexity O(n)
     * 
     * Un árbol vacío tiene altura -1, un árbol con solo raíz tiene altura 0
     */
    int height();
    
    /**
     * @brief Cuenta el número total de nodos
     * @return Número de nodos en el árbol
     * @complexity O(n)
     */
    int countNodes();
    
    /**
     * @brief Verifica si el árbol está vacío
     * @return true si está vacío, false en caso contrario
     * @complexity O(1)
     */
    bool isEmpty();
    
    /**
     * @brief Elimina todos los nodos del árbol
     * @complexity O(n)
     * 
     * Libera toda la memoria y deja el árbol vacío
     */
    void clear();
    
    // ==================== ADDITIONAL USEFUL OPERATIONS ====================
    
    /**
     * @brief Encuentra el sucesor de un valor (siguiente en orden)
     * @param value Valor cuyo sucesor se busca
     * @return Valor del sucesor
     * @throw std::runtime_error si no existe sucesor
     * @complexity O(log n) en promedio
     * 
     * El sucesor es el menor valor mayor que el valor dado
     */
    int findSuccessor(int value);
    
    /**
     * @brief Encuentra el predecesor de un valor (anterior en orden)
     * @param value Valor cuyo predecesor se busca
     * @return Valor del predecesor
     * @throw std::runtime_error si no existe predecesor
     * @complexity O(log n) en promedio
     * 
     * El predecesor es el mayor valor menor que el valor dado
     */
    int findPredecessor(int value);
    
    /**
     * @brief Imprime una representación visual del árbol
     * @complexity O(n)
     * 
     * Muestra la estructura del árbol de forma jerárquica
     */
    void printTree();
};

#endif __BST__