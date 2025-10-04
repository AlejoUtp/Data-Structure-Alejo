#ifndef __BST__
#define __BST__

#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;
/**
 * @class BST
 * @brief Árbol Binario de Búsqueda con pares Key-Value
 * @tparam Key Tipo de dato para la clave (debe ser comparable)
 * @tparam Value Tipo de dato para el valor
 *
 * Implementa todas las operaciones estándar de un BST donde:
 * - La Key es única y determina la posición en el árbol
 * - El Value puede repetirse y se asocia a cada Key
 * - Las operaciones de búsqueda y ordenamiento se basan en la Key
 */
template <typename Key, typename Value>
class BST
{
private:
    /**
     * @class Node
     * @brief Representa un nodo del árbol con par Key-Value
     *
     * Encapsula la información de cada nodo: clave única, valor asociado,
     * y punteros a los hijos izquierdo y derecho.
     */
    class Node
    {
    private:
        Key key;     ///< Clave única del nodo (usada para ordenar)
        Value value; ///< Valor asociado a la clave
        Node *left;  ///< Puntero al hijo izquierdo
        Node *right; ///< Puntero al hijo derecho

    public:
        /**
         * @brief Constructor del nodo
         * @param k Clave del nodo
         * @param v Valor asociado a la clave
         */
        Node(const Key &k, const Value &v) : key(k), value(v), left(nullptr), right(nullptr) {}

        /**
         * @brief Obtiene la clave del nodo
         * @return Referencia constante a la clave
         */
        const Key &getKey() const { return key; }

        /**
         * @brief Obtiene el valor del nodo
         * @return Referencia constante al valor
         */
        const Value &getValue() const { return value; }

        /**
         * @brief Obtiene el puntero al hijo izquierdo
         * @return Puntero al nodo izquierdo
         */
        Node *getLeft() const { return left; }

        /**
         * @brief Obtiene el puntero al hijo derecho
         * @return Puntero al nodo derecho
         */
        Node *getRight() const { return right; }

        /**
         * @brief Establece el hijo izquierdo
         * @param n Puntero al nuevo nodo izquierdo
         */
        void setLeft(Node *n) { left = n; }

        /**
         * @brief Establece el hijo derecho
         * @param n Puntero al nuevo nodo derecho
         */
        void setRight(Node *n) { right = n; }

        /**
         * @brief Actualiza el valor del nodo
         * @param v Nuevo valor
         */
        void setValue(const Value &v) { value = v; }

        /**
         * @brief Verifica si tiene hijo izquierdo
         * @return true si tiene hijo izquierdo, false en caso contrario
         */
        bool hasLeft() const { return left != nullptr; }

        /**
         * @brief Verifica si tiene hijo derecho
         * @return true si tiene hijo derecho, false en caso contrario
         */
        bool hasRight() const { return right != nullptr; }
    };

    Node *root;      ///< Raíz del árbol
    unsigned int sz; ///< Número de nodos en el árbol

    // ==================== MÉTODOS AUXILIARES PRIVADOS ====================

    /**
     * @brief Inserta un nodo recursivamente
     * @param node Nodo actual en la recursión
     * @param k Clave a insertar
     * @param v Valor asociado a la clave
     * @return Puntero al nodo actualizado
     */
    void insertHelper(Node *node, const Key &k, const Value &v)
    {
        // Si la clave a insertar es menor que la del nodo actual,
        // intentamos insertarla en el subárbol izquierdo.
        if (k < node->getKey())
        {
            // Si el nodo izquierdo existe, seguimos descendiendo por la izquierda.
            if (node->hasLeft())
            {
                insertHelper(node->getLeft(), k, v);
            }
            // Si el nodo izquierdo NO existe, creamos uno nuevo en esa posición.
            else
            {
                Node *newNode = new Node(k, v);
                node->setLeft(newNode);
                sz++; // Aumentamos el contador de nodos (solo si se crea uno nuevo).
            }
        }
        // Si la clave a insertar es mayor que la del nodo actual,
        // intentamos insertarla en el subárbol derecho.
        else if (k > node->getKey())
        {
            // Si el nodo derecho existe, seguimos descendiendo por la derecha.
            if (node->hasRight())
            {
                insertHelper(node->getRight(), k, v);
            }
            // Si el nodo derecho NO existe, creamos uno nuevo en esa posición.
            else
            {
                Node *newNode = new Node(k, v);
                node->setRight(newNode);
                sz++; // Aumentamos el contador de nodos.
            }
        }
        // Si la clave YA existe en el árbol (igual a la del nodo actual),
        // simplemente actualizamos el valor asociado.
        else
        {
            node->setValue(v);
        }
    }

    /**
     * @brief Busca un nodo por su clave recursivamente
     * @param node Nodo actual en la recursión
     * @param k Clave a buscar
     * @return Puntero al nodo encontrado o nullptr
     */
    bool findHelper(Node *node, const Key &k) const
    {
        if (node == nullptr)
        {
            return false;
        }
        if (k == node->getKey())
        {
            return true;
        }
        else if (k < node->getKey())
        {
            return findHelper(node->getLeft(), k);
        }
        else
        {
            return findHelper(node->getRight(), k);
        }
    }

    /**
     * @brief Elimina un nodo recursivamente
     * @param node Nodo actual en la recursión
     * @param k Clave a eliminar
     * @return Puntero al nodo actualizado
     */
    Node *removeHelper(Node *node, const Key &k)
    {
        if (k < node->getKey())
        {
            node->setLeft(removeHelper(node->getLeft(), k));
        }
        else if (node->getKey() < k)
        {
            node->setRight(removeHelper(node->getRight(), k)); // una vez se encuentre el nodo == k entonces el nodo con el que trabajaremos sera ese, y el nodo anterior sera el padre (node->setRight(nodo hijo))
        }
        else
        {
            // Nodo encontrado, empezamos con verificar si es nodo hoja, un solo hijo o dos hijos y realizamos la eliminacion y reasignacion
            if (!node->hasLeft() && !node->hasRight())
            {
                // Caso 2: solo hijo izquierdo
                delete node;
                return nullptr;
            }

            else if (!node->hasLeft())
            {
                // Caso 2: solo hijo derecho
                Node *temp = node->getRight();
                delete node;
                return temp;
            }
            else if (!node->hasRight())
            {
                // Caso 2: solo hijo izquierdo
                Node *temp = node->getLeft();
                delete node;
                return temp;
            }

            else{
                // Caso 3: dos hijos
                Node *successor = findMinHelper(node->getRight()); // el sucesor inorden es el minimo del subarbol derecho
                node->setValue(successor->getValue()); // copiamos el valor del sucesor al nodo actual
                node->setKey(successor->getKey()); // copiamos la clave del sucesor al nodo actual
                node->setRight(removeHelper(node->getRight(), successor->getKey())); // eliminamos el sucesor del subarbol derecho
                return node;
            }
        }
    }

    /**
     * @brief Encuentra el nodo con clave mínima en un subárbol
     * @param node Raíz del subárbol
     * @return Puntero al nodo con clave mínima
     */
    Node *findMinHelper(Node *node) const {
        while( node->hasLeft() ){
            node = node->getLeft();
        }
        return node;
    }

    /**
     * @brief Encuentra el nodo con clave máxima en un subárbol
     * @param node Raíz del subárbol
     * @return Puntero al nodo con clave máxima
     */
    Node *findMaxHelper(Node *node) const;

    /**
     * @brief Recorrido inorden recursivo
     * @param node Nodo actual en la recursión
     */
    void inorderHelper(Node *node) const {
        if ( node == nullptr ){
            return;
        }

        inorderHelper(node->getLeft());
        cout << node->getKey() << ": " << node->getValue();
        inorderHelper(node->getRight());
    }

    /**
     * @brief Recorrido preorden recursivo
     * @param node Nodo actual en la recursión
     */
    void preorderHelper(Node *node) const;

    /**
     * @brief Recorrido postorden recursivo
     * @param node Nodo actual en la recursión
     */
    void postorderHelper(Node *node) const;

    /**
     * @brief Calcula la altura del árbol recursivamente
     * @param node Nodo actual en la recursión
     * @return Altura del subárbol
     */
    int heightHelper(Node *node) const;

    /**
     * @brief Elimina todos los nodos del árbol recursivamente
     * @param node Nodo actual en la recursión
     */
    void clearHelper(Node *node);

    /**
     * @brief Copia un árbol recursivamente
     * @param node Nodo del árbol a copiar
     * @return Puntero al nuevo nodo copiado
     */
    Node *copyHelper(Node *node);

    /**
     * @brief Imprime el árbol de forma visual
     * @param node Nodo actual
     * @param prefix Prefijo para la indentación
     * @param isLeft Indica si es hijo izquierdo
     */
    void printTreeHelper(Node *node, const std::string &prefix, bool isLeft) const;

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
    BST(const BST &other);

    /**
     * @brief Operador de asignación
     * @param other Árbol a copiar
     * @return Referencia al árbol actual
     * @complexity O(n)
     */
    BST &operator=(const BST &other);

    /**
     * @brief Destructor - Libera toda la memoria
     * @complexity O(n)
     */
    ~BST();

    /**
     * @brief Inserta un nuevo par Key-Value en el árbol
     * @param k Clave a insertar
     * @param v Valor asociado
     * @complexity O(log n) en promedio, O(n) en el peor caso
     *
     * Si la clave ya existe, actualiza su valor.
     * Mantiene la propiedad del BST basada en las claves.
     */
    void insert(const Key &k, const Value &v)
    {
        if (empty())
        {
            root = new Node(k, v);
            sz++;
        }
        else
        {
            insertHelper(root, k, v);
        }
    }
    /**
     * @brief Busca una clave en el árbol
     * @param k Clave a buscar
     * @return Puntero al valor asociado, nullptr si no existe
     * @complexity O(log n) en promedio, O(n) en el peor caso
     */
    bool find(const Key &k) const
    {
        if (empty())
        {
            return false;
        }
        return findHelper(root, k);
    }

    /**
     * @brief Elimina una clave del árbol
     * @param k Clave a eliminar
     * @return true si se eliminó correctamente, false si no existía
     * @complexity O(log n) en promedio, O(n) en el peor caso
     *
     * Esta es la operación más compleja. Maneja 3 casos:
     * 1. Nodo sin hijos (hoja)
     * 2. Nodo con un hijo
     * 3. Nodo con dos hijos (usa sucesor inorden)
     */
    bool remove(const Key &k)
    {
        if (!find(k))
        {
            return false; // Key not found
        }
        root = removeHelper(root, k);
        sz--;
        return true;
    }

    // ==================== TRAVERSALS ====================

    /**
     * @brief Recorrido Inorden (Izquierda-Raíz-Derecha)
     * @complexity O(n)
     *
     * Imprime los pares Key-Value ordenados por clave ascendente
     */
    void inorder() const { 
        if( empty() ) return;
        inorderHelper(root);
    }

    /**
     * @brief Recorrido Preorden (Raíz-Izquierda-Derecha)
     * @complexity O(n)
     *
     * Útil para copiar el árbol o serialización
     */
    void preorder() const;

    /**
     * @brief Recorrido Postorden (Izquierda-Derecha-Raíz)
     * @complexity O(n)
     *
     * Útil para eliminar el árbol o evaluación de expresiones
     */
    void postorder() const;

    /**
     * @brief Recorrido por niveles (Breadth-First)
     * @complexity O(n)
     *
     * Visita todos los nodos nivel por nivel
     */
    void levelOrder() const;

    // ==================== HELPER OPERATIONS ====================

    /**
     * @brief Encuentra la clave mínima del árbol
     * @return Clave mínima (nodo más a la izquierda)
     * @throw std::runtime_error si el árbol está vacío
     * @complexity O(log n) en promedio, O(n) en el peor caso
     */
    const Key &findMinimum() const {
        if ( empty() ) throw std::runtime_error("Árbol vacío - no hay mínimo");
        Node *minNode = findMinHelper(root);
        return minNode->getKey();
    }

    /**
     * @brief Encuentra la clave máxima del árbol
     * @return Clave máxima (nodo más a la derecha)
     * @throw std::runtime_error si el árbol está vacío
     * @complexity O(log n) en promedio, O(n) en el peor caso
     */
    const Key &findMaximum() const;

    /**
     * @brief Calcula la altura del árbol
     * @return Altura (número de aristas en el camino más largo)
     * @complexity O(n)
     *
     * Un árbol vacío tiene altura -1, un árbol con solo raíz tiene altura 0
     */
    int height() const;

    /**
     * @brief Obtiene el número total de nodos
     * @return Número de nodos en el árbol
     * @complexity O(1)
     */
    unsigned int size() const;

    /**
     * @brief Verifica si el árbol está vacío
     * @return true si está vacío, false en caso contrario
     * @complexity O(1)
     */
    bool empty() const { return root == nullptr; }

    /**
     * @brief Elimina todos los nodos del árbol
     * @complexity O(n)
     *
     * Libera toda la memoria y deja el árbol vacío
     */
    void clear();

    // ==================== ADDITIONAL USEFUL OPERATIONS ====================

    /**
     * @brief Encuentra el sucesor de una clave (siguiente en orden)
     * @param k Clave cuyo sucesor se busca
     * @return Clave del sucesor
     * @throw std::runtime_error si no existe sucesor
     * @complexity O(log n) en promedio
     *
     * El sucesor es la menor clave mayor que la clave dada
     */
    const Key &findSuccessor(const Key &k) const;

    /**
     * @brief Encuentra el predecesor de una clave (anterior en orden)
     * @param k Clave cuyo predecesor se busca
     * @return Clave del predecesor
     * @throw std::runtime_error si no existe predecesor
     * @complexity O(log n) en promedio
     *
     * El predecesor es la mayor clave menor que la clave dada
     */
    const Key &findPredecessor(const Key &k) const;

    /**
     * @brief Imprime una representación visual del árbol
     * @complexity O(n)
     *
     * Muestra la estructura del árbol de forma jerárquica
     */
    void printTree() const;
};
#endif __BST__

/*  PENDIENTES DE IMPLEMENTAR:
  • remove(k)
  • preorder()
  • postorder()
  • levelOrder()
  • findMinimum() / findMaximum()
  • height()
  • clear()
  • findSuccessor() / findPredecessor()
  • printTree()
  • Constructor de copia
  • Operador de asignación
  • Destructor
*/