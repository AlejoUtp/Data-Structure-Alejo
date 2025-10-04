#ifndef __BSTa__
#define __BSTa__

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
     */
    class Node
    {
    private:
        Key key;     ///< Clave única del nodo (usada para ordenar)
        Value value; ///< Valor asociado a la clave
        Node *left;  ///< Puntero al hijo izquierdo
        Node *right; ///< Puntero al hijo derecho

    public:
        Node(const Key &k, const Value &v) : key(k), value(v), left(nullptr), right(nullptr) {}

        const Key &getKey() const { return key; }
        const Value &getValue() const { return value; }
        Node *getLeft() const { return left; }
        Node *getRight() const { return right; }
        void setLeft(Node *n) { left = n; }
        void setRight(Node *n) { right = n; }
        void setValue(const Value &v) { value = v; }
        bool hasLeft() const { return left != nullptr; }
        bool hasRight() const { return right != nullptr; }
    };

    Node *root;      ///< Raíz del árbol
    unsigned int sz; ///< Número de nodos en el árbol

    // ==================== MÉTODOS AUXILIARES PRIVADOS ====================

    /**
     * @brief Inserta un nodo recursivamente
     */
    void insertHelper(Node *node, const Key &k, const Value &v)
    {
        if (k < node->getKey())
        {
            if (node->hasLeft())
            {
                insertHelper(node->getLeft(), k, v);
            }
            else
            {
                Node *newNode = new Node(k, v);
                node->setLeft(newNode);
                sz++;
            }
        }
        else if (k > node->getKey())
        {
            if (node->hasRight())
            {
                insertHelper(node->getRight(), k, v);
            }
            else
            {
                Node *newNode = new Node(k, v);
                node->setRight(newNode);
                sz++;
            }
        }
        else
        {
            node->setValue(v);
        }
    }

    /**
     * @brief Busca un nodo por su clave recursivamente
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
     * @brief Recorrido inorden recursivo
     */
    void inorderHelper(Node *node) const
    {
        if (node == nullptr)
        {
            return;
        }

        inorderHelper(node->getLeft());
        cout << "[" << node->getKey() << ":" << node->getValue() << "] ";
        inorderHelper(node->getRight());
    }

    // ==================== MÉTODOS NO IMPLEMENTADOS AÚN ====================
    // Estos métodos están declarados pero no implementados todavía

    Node *removeHelper(Node *node, const Key &k);
    Node *findMinHelper(Node *node) const;
    Node *findMaxHelper(Node *node) const;
    void preorderHelper(Node *node) const;
    void postorderHelper(Node *node) const;
    int heightHelper(Node *node) const;
    void clearHelper(Node *node);
    Node *copyHelper(Node *node);
    void printTreeHelper(Node *node, const std::string &prefix, bool isLeft) const;

public:
    // ==================== CORE OPERATIONS ====================

    /**
     * @brief Constructor por defecto - Crea un BST vacío
     * @complexity O(1)
     */
    BST() : root(nullptr), sz(0) {}

    /**
     * @brief Constructor de copia (NO IMPLEMENTADO)
     */
    BST(const BST &other)
    {
        // TODO: Implementar
        root = nullptr;
        sz = 0;
    }

    /**
     * @brief Operador de asignación (NO IMPLEMENTADO)
     */
    BST &operator=(const BST &other)
    {
        // TODO: Implementar
        return *this;
    }

    /**
     * @brief Destructor (NO IMPLEMENTADO - MEMORY LEAK WARNING)
     */
    ~BST()
    {
        // TODO: Implementar clear()
    }

    /**
     * @brief Inserta un nuevo par Key-Value en el árbol ✅ FUNCIONA
     * @param k Clave a insertar
     * @param v Valor asociado
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
     * @brief Busca una clave en el árbol ✅ FUNCIONA
     * @param k Clave a buscar
     * @return true si existe, false en caso contrario
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
     * @brief Elimina una clave del árbol ❌ NO IMPLEMENTADO COMPLETAMENTE
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
     * @brief Recorrido Inorden ✅ FUNCIONA
     */
    void inorder() const
    {
        if (empty())
        {
            cout << "(árbol vacío)";
            return;
        }
        inorderHelper(root);
    }

    /**
     * @brief Recorrido Preorden ❌ NO IMPLEMENTADO
     */
    void preorder() const
    {
        cout << "⚠️  preorder() no implementado aún" << endl;
    }

    /**
     * @brief Recorrido Postorden ❌ NO IMPLEMENTADO
     */
    void postorder() const
    {
        cout << "⚠️  postorder() no implementado aún" << endl;
    }

    /**
     * @brief Recorrido por niveles ❌ NO IMPLEMENTADO
     */
    void levelOrder() const
    {
        cout << "⚠️  levelOrder() no implementado aún" << endl;
    }

    // ==================== HELPER OPERATIONS ====================

    /**
     * @brief Encuentra la clave mínima ❌ NO IMPLEMENTADO
     */
    const Key &findMinimum() const
    {
        throw std::runtime_error("findMinimum() no implementado aún");
    }

    /**
     * @brief Encuentra la clave máxima ❌ NO IMPLEMENTADO
     */
    const Key &findMaximum() const
    {
        throw std::runtime_error("findMaximum() no implementado aún");
    }

    /**
     * @brief Calcula la altura ❌ NO IMPLEMENTADO
     */
    int height() const
    {
        cout << "⚠️  height() no implementado aún" << endl;
        return -1;
    }

    /**
     * @brief Obtiene el tamaño ✅ FUNCIONA
     */
    unsigned int size() const
    {
        return sz;
    }

    /**
     * @brief Verifica si está vacío ✅ FUNCIONA
     */
    bool empty() const
    {
        return root == nullptr;
    }

    /**
     * @brief Elimina todos los nodos ❌ NO IMPLEMENTADO
     */
    void clear()
    {
        cout << "⚠️  clear() no implementado aún (MEMORY LEAK)" << endl;
    }

    // ==================== ADDITIONAL USEFUL OPERATIONS ====================

    /**
     * @brief Encuentra el sucesor ❌ NO IMPLEMENTADO
     */
    const Key &findSuccessor(const Key &k) const
    {
        throw std::runtime_error("findSuccessor() no implementado aún");
    }

    /**
     * @brief Encuentra el predecesor ❌ NO IMPLEMENTADO
     */
    const Key &findPredecessor(const Key &k) const
    {
        throw std::runtime_error("findPredecessor() no implementado aún");
    }

    /**
     * @brief Imprime el árbol ❌ NO IMPLEMENTADO
     */
    void printTree() const
    {
        cout << "⚠️  printTree() no implementado aún" << endl;
    }
};

#endif __BSTa__