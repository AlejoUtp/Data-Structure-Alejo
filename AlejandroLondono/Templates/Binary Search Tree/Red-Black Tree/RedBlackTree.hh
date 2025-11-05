/**
 * @file RedBlackTree.h
 * @brief Implementación de un Árbol Rojo-Negro (Red-Black Tree) con pares Key-Value
 * @author Tu Nombre
 * @date 2025
 *
 * Este archivo contiene la estructura completa de un Red-Black Tree autobalanceado.
 * El árbol mantiene las 5 propiedades fundamentales:
 * 1. Todo nodo es ROJO o NEGRO
 * 2. La raíz es NEGRA
 * 3. Todas las hojas (nil) son NEGRAS
 * 4. Si un nodo es ROJO, ambos hijos son NEGROS (no hay dos rojos consecutivos)
 * 5. Todos los caminos desde un nodo a sus hojas tienen el mismo número de nodos NEGROS
 *
 * Garantiza operaciones en O(log n) para insert, remove y search.
 */

#ifndef __RED_BLACK_TREE__
#define __RED_BLACK_TREE__

#include <iostream>
#include <stdexcept>
#include <string>
#include <queue>

/**
 * @enum Color
 * @brief Enumeración para los colores de los nodos
 */
enum Color
{
    RED,  ///< Color rojo
    BLACK ///< Color negro
};

/**
 * @class RedBlackTree
 * @brief Árbol Rojo-Negro autobalanceado con pares Key-Value
 * @tparam Key Tipo de dato para la clave (debe ser comparable)
 * @tparam Value Tipo de dato para el valor asociado
 *
 * Implementa un árbol binario de búsqueda autobalanceado que garantiza
 * altura O(log n) mediante rotaciones y recoloreos después de inserciones
 * y eliminaciones.
 */
template <typename Key, typename Value>
class RedBlackTree
{
private:
    /**
     * @class Node
     * @brief Representa un nodo del árbol Rojo-Negro
     *
     * Cada nodo contiene:
     * - Una clave única (Key)
     * - Un valor asociado (Value)
     * - Un color (RED o BLACK)
     * - Punteros a padre, hijo izquierdo e hijo derecho
     */
    class Node
    {
    private:
        Key key;      ///< Clave única del nodo
        Value value;  ///< Valor asociado a la clave
        Color color;  ///< Color del nodo (RED o BLACK)
        Node *left;   ///< Puntero al hijo izquierdo
        Node *right;  ///< Puntero al hijo derecho
        Node *parent; ///< Puntero al padre (necesario para rotaciones)

    public:
        /**
         * @brief Constructor del nodo
         * @param k Clave del nodo
         * @param v Valor asociado
         * @param c Color inicial (por defecto RED)
         *
         * Los nodos nuevos se crean ROJOS por defecto (menos disruptivo).
         */
        Node(const Key &k, const Value &v, Color c = RED)
            : key(k), value(v), color(c), left(nil), right(nil), parent(nil) {}

        // Getters
        const Key &getKey() const { return key; }
        const Value &getValue() const { return value; }
        Color getColor() const { return color; }
        Node *getLeft() const { return left; }
        Node *getRight() const { return right; }
        Node *getParent() const { return parent; }

        // Setters
        void setValue(const Value &v) { value = v; }
        void setColor(Color c) { color = c; }
        void setLeft(Node *n) { left = n; }
        void setRight(Node *n) { right = n; }
        void setParent(Node *p) { parent = p; }

        // Verificadores
        bool hasLeft() const { return left != nil; }
        bool hasRight() const { return right != nil; }
        bool hasParent() const { return parent != nil; }
        bool isRed() const { return color == RED; }
        bool isBlack() const { return color == BLACK; }
    };

    Node *root;      ///< Raíz del árbol
    Node *nil;       ///< Nodo centinela (representa nullptr, siempre NEGRO)
    unsigned int sz; ///< Número de nodos en el árbol

    // ==================== MÉTODOS AUXILIARES DE ROTACIÓN ====================

    /**
     * @brief Rotación a la izquierda
     * @param x Nodo sobre el cual rotar
     * @complexity O(1)
     *
     * Transforma:
     *      x              y
     *     / \            / \
     *    A   y    →    x   C
     *       / \       / \
     *      B   C     A   B
     *
     * Usado para rebalancear el árbol después de inserciones/eliminaciones.
     */
    void rotateLeft(Node *x)
    {
        if (!x->hasRight())
        {
            throw std::runtime_error("Cannot rotate left: no right child");
        }

        Node *y = x->right;
        x->setRight(y->getLeft());

        if (y->hasLeft())
        {
            y->getLeft()->setParent(x);
        }

        y->setParent(x->getParent());

        if (!x->hasParent())
        {
            root = y;
        }
        else if (x == x->getParent()->getLeft())
        {
            x->getParent()->setLeft(y);
        }
        else
        {
            x->getParent()->setRight(y);
        }

        y->setLeft(x);
        x->setParent(y);
    }

    /**
     * @brief Rotación a la derecha
     * @param y Nodo sobre el cual rotar
     * @complexity O(1)
     *
     * Transforma:
     *      y              x
     *     / \            / \
     *    x   C    →    A   y
     *   / \               / \
     *  A   B             B   C
     *
     * Operación simétrica a rotateLeft.
     */
    void rotateRight(Node *x)
    {

        if (!x->hasLeft())
        {
            throw std::runtime_error("Cannot rotate right: no Left child");
        }

        Node *y = x->left;
        x->setLeft(y->getRight());

        if (y->hasRight())
        {
            y->getRight()->setParent(x);
        }

        y->setParent(x->getParent());

        if (!x->hasParent())
        {
            root = y;
        }
        else if (x == x->getParent()->getRight())
        {
            x->getParent()->setRight(y);
        }
        else
        {
            x->getParent()->setLeft(y);
        }

        y->setRight(x);
        x->setParent(y);
    }

    // ==================== MÉTODOS AUXILIARES DE FIXUP ====================

    /**
     * @brief Corrige las propiedades RBT después de una inserción
     * @param z Nodo recién insertado (ROJO)
     * @complexity O(log n)
     *
     * Maneja 3 casos:
     * CASO 1: Tío es ROJO
     *   - Recolorear padre, tío y abuelo
     *   - Subir el problema al abuelo
     *
     * CASO 2: Tío es NEGRO y z es hijo derecho (triángulo)
     *   - Rotar padre a la izquierda
     *   - Convertir a CASO 3
     *
     * CASO 3: Tío es NEGRO y z es hijo izquierdo (línea)
     *   - Rotar abuelo a la derecha
     *   - Recolorear padre y abuelo
     *
     * También maneja casos simétricos (cuando padre es hijo derecho).
     */

    void insertFixup(Node *z);

    /**
     * @brief Corrige las propiedades RBT después de una eliminación
     * @param x Nodo que reemplazó al eliminado
     * @complexity O(log n)
     *
     * Maneja 4 casos cuando x es NEGRO (doble negro):
     * CASO 1: Hermano es ROJO
     *   - Rotar y recolorear para hacer hermano NEGRO
     *
     * CASO 2: Hermano es NEGRO y ambos sobrinos son NEGROS
     *   - Recolorear hermano a ROJO
     *   - Subir el problema
     *
     * CASO 3: Hermano es NEGRO, sobrino izquierdo ROJO, derecho NEGRO
     *   - Rotar hermano y recolorear
     *   - Convertir a CASO 4
     *
     * CASO 4: Hermano es NEGRO y sobrino derecho es ROJO
     *   - Rotar padre y recolorear
     *   - Problema resuelto
     *
     * También maneja casos simétricos.
     */
    void deleteFixup(Node *x);

    /**
     * @brief Transplanta un subárbol en lugar de otro
     * @param u Nodo a reemplazar
     * @param v Nodo que lo reemplazará
     * @complexity O(1)
     *
     * Actualiza el padre de u para que apunte a v.
     * Usado internamente por la función de eliminación.
     */
    void transplant(Node *u, Node *v);

    // ==================== MÉTODOS AUXILIARES DE BÚSQUEDA ====================

    /**
     * @brief Busca un nodo por su clave recursivamente
     * @param node Nodo actual
     * @param k Clave a buscar
     * @return Puntero al nodo encontrado o nil
     * @complexity O(log n)
     */
    Node *searchHelper(Node *node, const Key &k) const;

    /**
     * @brief Encuentra el nodo con clave mínima en un subárbol
     * @param node Raíz del subárbol
     * @return Puntero al nodo con clave mínima
     * @complexity O(log n)
     *
     * Desciende por el camino más a la izquierda.
     */
    Node *findMinHelper(Node *node) const;

    /**
     * @brief Encuentra el nodo con clave máxima en un subárbol
     * @param node Raíz del subárbol
     * @return Puntero al nodo con clave máxima
     * @complexity O(log n)
     *
     * Desciende por el camino más a la derecha.
     */
    Node *findMaxHelper(Node *node) const;

    /**
     * @brief Encuentra el sucesor inorden de un nodo
     * @param node Nodo del cual buscar sucesor
     * @return Puntero al nodo sucesor
     * @complexity O(log n)
     *
     * Si tiene hijo derecho, el sucesor es el mínimo de ese subárbol.
     * Si no, es el ancestro más bajo cuyo hijo izquierdo es ancestro del nodo.
     */
    Node *successor(Node *node) const;

    /**
     * @brief Encuentra el predecesor inorden de un nodo
     * @param node Nodo del cual buscar predecesor
     * @return Puntero al nodo predecesor
     * @complexity O(log n)
     *
     * Si tiene hijo izquierdo, el predecesor es el máximo de ese subárbol.
     * Si no, es el ancestro más bajo cuyo hijo derecho es ancestro del nodo.
     */
    Node *predecessor(Node *node) const;

    // ==================== MÉTODOS AUXILIARES DE RECORRIDOS ====================

    /**
     * @brief Recorrido inorden (Izquierda-Raíz-Derecha)
     * @param node Nodo actual
     * @complexity O(n)
     *
     * Imprime los elementos en orden ascendente por clave.
     */
    void inorderHelper(Node *node) const;

    /**
     * @brief Recorrido preorden (Raíz-Izquierda-Derecha)
     * @param node Nodo actual
     * @complexity O(n)
     */
    void preorderHelper(Node *node) const;

    /**
     * @brief Recorrido postorden (Izquierda-Derecha-Raíz)
     * @param node Nodo actual
     * @complexity O(n)
     */
    void postorderHelper(Node *node) const;

    // ==================== MÉTODOS AUXILIARES DE UTILIDAD ====================

    /**
     * @brief Calcula la altura del árbol
     * @param node Nodo actual
     * @return Altura del subárbol
     * @complexity O(n)
     */
    int heightHelper(Node *node) const;

    /**
     * @brief Calcula la altura negra del árbol
     * @param node Nodo actual
     * @return Número de nodos negros desde node hasta una hoja
     * @complexity O(log n)
     *
     * Útil para verificar que se mantiene la propiedad 5 del RBT.
     */
    int blackHeightHelper(Node *node) const;

    /**
     * @brief Elimina todos los nodos recursivamente
     * @param node Nodo actual
     * @complexity O(n)
     */
    void clearHelper(Node *node)
    {
        if (Node == nil)
            return;
        clearHelper(Node->left);
        clearHelper(Node->right);
        delete node;
    }

    /**
     * @brief Copia un árbol recursivamente
     * @param node Nodo a copiar
     * @param parent Padre del nodo en el nuevo árbol
     * @return Puntero al nuevo nodo copiado
     * @complexity O(n)
     */
    Node *copyHelper(Node *node, Node *parent);

    /**
     * @brief Imprime el árbol de forma visual con colores
     * @param node Nodo actual
     * @param prefix Prefijo para indentación
     * @param isLeft Indica si es hijo izquierdo
     * @complexity O(n)
     */
    void printTreeHelper(Node *node, const std::string &prefix, bool isLeft) const;

    /**
     * @brief Verifica si el árbol cumple las propiedades RBT
     * @param node Nodo actual
     * @param blackCount Contador de nodos negros en el camino actual
     * @param pathBlackCount Referencia al número esperado de nodos negros
     * @return true si cumple propiedades, false en caso contrario
     * @complexity O(n)
     *
     * Verifica:
     * - No hay dos rojos consecutivos
     * - Todos los caminos tienen el mismo black-height
     */
    bool verifyPropertiesHelper(Node *node, int blackCount, int &pathBlackCount) const;

public:
    // ==================== CONSTRUCTORES Y DESTRUCTOR ====================

    /**
     * @brief Constructor por defecto
     * @complexity O(1)
     *
     * Crea un árbol vacío con nodo centinela nil.
     */
    RedBlackTree()
    {
        nil = new Node(k, v, BLACK);
        nil->left = nil->right = nil->parent = nil;
        root = nil;
    }

    /**
     * @brief Constructor de copia
     * @param other Árbol a copiar
     * @complexity O(n)
     */
    RedBlackTree(const RedBlackTree &other);

    /**
     * @brief Operador de asignación
     * @param other Árbol a copiar
     * @return Referencia al árbol actual
     * @complexity O(n)
     */
    RedBlackTree &operator=(const RedBlackTree &other);

    /**
     * @brief Destructor
     * @complexity O(n)
     *
     * Libera toda la memoria del árbol.
     */
    ~RedBlackTree()
    {
        clear();
        delete nil;
    }

    // ==================== OPERACIONES PRINCIPALES ====================

    /**
     * @brief Inserta un nuevo par Key-Value
     * @param k Clave a insertar
     * @param v Valor asociado
     * @complexity O(log n) garantizado
     *
     * Pasos:
     * 1. Insertar como en BST normal
     * 2. Colorear el nuevo nodo de ROJO
     * 3. Llamar a insertFixup para restaurar propiedades
     * 4. Asegurar que la raíz sea NEGRA
     *
     * Si la clave existe, actualiza el valor.
     */
    void insert(const Key &k, const Value &v)
    {
        Node *z = new Node(k, v);
        z->setLeft(nil);
        z->setRight(nil);

        Node *y = nil;
        Node *x = root;

        while (x != nil)
        {
            y = x;
            if (k < x->getKey())
                x = x->getLeft();
            else if (k > x->getKey())
                x = x->getRight();
            else
            {
                x->setValue(v);
                delete z;
                return;
            }
        }

        z->setParent(y);
        if(y == nil)
            root = z;
        else if (k < y->getKey())
            y->setLeft(z);
        else
            y->setRight(z);

        sz++;
        insertFixup(z);
        root->setColor(BLACK);
    }

    /**
     * @brief Elimina una clave del árbol
     * @param k Clave a eliminar
     * @return true si se eliminó, false si no existía
     * @complexity O(log n) garantizado
     *
     * Pasos:
     * 1. Buscar el nodo a eliminar
     * 2. Eliminar como en BST (considerar casos)
     * 3. Si se eliminó un nodo NEGRO, llamar deleteFixup
     * 4. Asegurar que la raíz sea NEGRA
     */
    bool remove(const Key &k);

    /**
     * @brief Busca una clave en el árbol
     * @param k Clave a buscar
     * @return true si existe, false en caso contrario
     * @complexity O(log n) garantizado
     */
    bool find(const Key &k) const;

    /**
     * @brief Obtiene el valor asociado a una clave
     * @param k Clave a buscar
     * @return Puntero constante al valor, nullptr si no existe
     * @complexity O(log n) garantizado
     */
    const Value *getValue(const Key &k) const;

    /**
     * @brief Obtiene el valor asociado a una clave (versión no const)
     * @param k Clave a buscar
     * @return Puntero al valor, nullptr si no existe
     * @complexity O(log n) garantizado
     */
    Value *getValue(const Key &k);

    // ==================== RECORRIDOS ====================

    /**
     * @brief Recorrido inorden
     * @complexity O(n)
     *
     * Imprime los elementos en orden ascendente por clave.
     */
    void inorder() const;

    /**
     * @brief Recorrido preorden
     * @complexity O(n)
     */
    void preorder() const;

    /**
     * @brief Recorrido postorden
     * @complexity O(n)
     */
    void postorder() const;

    /**
     * @brief Recorrido por niveles (BFS)
     * @complexity O(n)
     */
    void levelOrder() const;

    // ==================== OPERACIONES DE CONSULTA ====================

    /**
     * @brief Encuentra la clave mínima
     * @return Clave mínima
     * @throw std::runtime_error si el árbol está vacío
     * @complexity O(log n) garantizado
     */
    const Key &findMin() const;

    /**
     * @brief Encuentra la clave máxima
     * @return Clave máxima
     * @throw std::runtime_error si el árbol está vacío
     * @complexity O(log n) garantizado
     */
    const Key &findMax() const;

    /**
     * @brief Encuentra el sucesor de una clave
     * @param k Clave de referencia
     * @return Clave del sucesor
     * @throw std::runtime_error si no existe sucesor
     * @complexity O(log n) garantizado
     */
    const Key &findSuccessor(const Key &k) const;

    /**
     * @brief Encuentra el predecesor de una clave
     * @param k Clave de referencia
     * @return Clave del predecesor
     * @throw std::runtime_error si no existe predecesor
     * @complexity O(log n) garantizado
     */
    const Key &findPredecessor(const Key &k) const;

    /**
     * @brief Calcula la altura del árbol
     * @return Altura (número de aristas en el camino más largo)
     * @complexity O(n)
     *
     * En un RBT bien balanceado, altura ≤ 2 * log₂(n+1)
     */
    int height() const;

    /**
     * @brief Calcula la altura negra del árbol
     * @return Número de nodos negros desde la raíz hasta una hoja
     * @complexity O(log n)
     *
     * Todos los caminos deben tener la misma altura negra.
     */
    int blackHeight() const;

    /**
     * @brief Obtiene el número de nodos
     * @return Tamaño del árbol
     * @complexity O(1)
     */
    unsigned int size() const;

    /**
     * @brief Verifica si el árbol está vacío
     * @return true si está vacío, false en caso contrario
     * @complexity O(1)
     */
    bool empty() const;

    /**
     * @brief Elimina todos los nodos
     * @complexity O(n)
     */
    void clear()
    {
        clearHelper(root);
        root = nil;
    }

    // ==================== OPERACIONES DE VERIFICACIÓN ====================

    /**
     * @brief Verifica si el árbol cumple todas las propiedades RBT
     * @return true si es válido, false en caso contrario
     * @complexity O(n)
     *
     * Verifica:
     * 1. Raíz es NEGRA
     * 2. No hay dos rojos consecutivos
     * 3. Todos los caminos tienen el mismo black-height
     * 4. Propiedades BST se mantienen
     */
    bool verifyProperties() const;

    /**
     * @brief Imprime el árbol con colores
     * @complexity O(n)
     *
     * Muestra la estructura con (R) para rojo y (B) para negro.
     */
    void printTree() const;

    /**
     * @brief Imprime estadísticas del árbol
     * @complexity O(n)
     *
     * Muestra: tamaño, altura, altura negra, si es válido.
     */
    void printStats() const;
};

// ==================== NOTA PARA IMPLEMENTACIÓN ====================
/*
 * ORDEN SUGERIDO PARA IMPLEMENTAR:
 *
 * 1. Constructor, destructor, clear, copyHelper
 * 2. Rotaciones (rotateLeft, rotateRight)
 * 3. insert básico (sin fixup primero)
 * 4. insertFixup (los 3 casos)
 * 5. find, searchHelper, findMin, findMax
 * 6. Recorridos (inorder, preorder, postorder, levelOrder)
 * 7. remove básico (sin fixup)
 * 8. deleteFixup (los 4 casos) - ¡El más complejo!
 * 9. successor, predecessor
 * 10. verifyProperties (para debugging)
 * 11. printTree con colores
 *
 * TIPS:
 * - Usa el nodo nil en lugar de nullptr para simplificar verificaciones
 * - Siempre verifica nullptr antes de acceder a propiedades
 * - Dibuja en papel cada caso de fixup antes de codear
 * - Prueba insert primero, remove después (es más complejo)
 * - verifyProperties() es tu mejor amigo para debugging
 */

#endif // __RED_BLACK_TREE__