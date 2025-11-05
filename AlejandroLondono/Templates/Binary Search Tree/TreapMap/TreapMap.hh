#ifndef __TreapMap__
#define __TreapMap__

#include <iostream>
#include <stdexcept>
#include <string>
#include <queue>

using namespace std;

template <typename Key, typename Value>
class TreapMap
{
private:
    class Node
    {
    private:
        Key key;     
        Value value; 
        int priority; 
        Node *right, *left; 

    public:

        Node(const Key &k, const Value &v) : key(k), value(v), priority(rand()), left(nullptr), right(nullptr) {}
        
        Key &getKey() { return key; }
        
        const Value &getValue() const { return value; }
    
        Node *getLeft() const { return left; }
     
        Node *getRight() const { return right; }
      
        void setLeft(Node *n) { left = n; }
       
        void setRight(Node *n) { right = n; }

        void setPriority(int p) { priority = p; }

        int getPriority() const { return priority; }
       
        void setValue(const Value &v) { value = v; }
        
        bool hasLeft() const { return left != nullptr; }

        bool hasRight() const { return right != nullptr; }
    };

    Node *root;   
    unsigned int sz;

    // ==================== MÉTODOS AUXILIARES PRIVADOS ====================


    Node *rotateRight(Node *node)
    {
        Node *newRoot = node->getLeft();
        node->setLeft(newRoot->getRight());
        newRoot->setRight(node);
        return newRoot;   //antes tenia node = newRoot;  con Node *rotateRight(Node *&node) entonces pasaba por referencia y cambiaba el puntero original pero mas peligroso
    }

    Node *rotateLeft(Node *node)
    {
        Node *newRoot = node->getRight();
        node->setRight(newRoot->getLeft());
        newRoot->setLeft(node);
        return newRoot;
    }

    Node* insertHelper(Node *node, const Key &k, const Value &v)
    {
      if (node == nullptr) {
          sz++;
          return new Node(k, v);
    }

    if (k < node->getKey())
        node->setLeft(insertHelper(node->getLeft(), k, v));
    else if (k > node->getKey())
        node->setRight(insertHelper(node->getRight(), k, v));
    else {
        node->setValue(v);  // Actualizar valor si la clave existe
        return node;
    }

    if (node->getLeft() && node->getLeft()->getPriority() > node->getPriority())
        node = rotateRight(node);
    else if (node->getRight() && node->getRight()->getPriority() > node->getPriority())
        node = rotateLeft(node);

    return node;
}

    const Value* findHelper(Node *node, const Key &k) const
    {
        if (node == nullptr)
            return nullptr;

        if (k == node->getKey())
        {
            return &(node->getValue());
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

            else
            {
               if(node->getLeft()->getPriority() > node->getRight()->getPriority()) {
                   node = rotateRight(node);
                   node->setRight(removeHelper(node->getRight(), k));
               } else {
                   node = rotateLeft(node);
                   node->setLeft(removeHelper(node->getLeft(), k));
               }
            }
        }
        return node;
    }

    /**
     * @brief Encuentra el nodo con clave mínima en un subárbol
     * @param node Raíz del subárbol
     * @return Puntero al nodo con clave mínima
     */
    Node *findMinHelper(Node *node) const
    {
        if (node == nullptr)
            return nullptr;
        while (node->hasLeft())
        {
            node = node->getLeft();
        }
        return node;
    }

    /**
     * @brief Encuentra el nodo con clave máxima en un subárbol
     * @param node Raíz del subárbol
     * @return Puntero al nodo con clave máxima
     */
    Node *findMaxHelper(Node *node) const
    {
        if (node == nullptr)
            return nullptr;

        while (node->hasRight())
        {
            node = node->getRight();
        }
        return node;
    }

    /**
     * @brief Recorrido inorden recursivo (Izquierda-Raíz-Derecha)
     * @param node Nodo actual en la recursión
     *
     * Visita el subárbol izquierdo, luego el nodo actual, luego el subárbol derecho.
     * Este recorrido produce los elementos en orden ascendente por clave.
     *
     * @complexity O(n) donde n es el número de nodos en el subárbol
     */
    void inorderHelper(Node *node) const
    {
        if (node == nullptr)
        {
            return;
        }

        inorderHelper(node->getLeft());                             // 1. Visitar izquierda
        cout << node->getKey() << ": " << node->getValue() << endl; // 2. Procesar raíz
        inorderHelper(node->getRight());                            // 3. Visitar derecha
    }

    /**
     * @brief Recorrido preorden recursivo (Raíz-Izquierda-Derecha)
     * @param node Nodo actual en la recursión
     *
     * Visita primero el nodo actual, luego el subárbol izquierdo, luego el derecho.
     * Útil para copiar el árbol o crear una representación serializada.
     *
     * @complexity O(n) donde n es el número de nodos en el subárbol
     */
    void preorderHelper(Node *node) const
    {
        if (node == nullptr)
        {
            return;
        }

        cout << node->getKey() << ": " << node->getValue() << endl; // 1. Procesar raíz ✅
        preorderHelper(node->getLeft());                            // 2. Visitar izquierda ✅
        preorderHelper(node->getRight());                           // 3. Visitar derecha ✅
    }

    /**
     * @brief Recorrido postorden recursivo (Izquierda-Derecha-Raíz)
     * @param node Nodo actual en la recursión
     *
     * Visita el subárbol izquierdo, luego el derecho, y finalmente el nodo actual.
     * Útil para eliminar el árbol o evaluar expresiones postfijas.
     *
     * @complexity O(n) donde n es el número de nodos en el subárbol
     */
    void postorderHelper(Node *node) const
    {
        if (node == nullptr)
        {
            return;
        }

        postorderHelper(node->getLeft());                           // 1. Visitar izquierda ✅
        postorderHelper(node->getRight());                          // 2. Visitar derecha ✅
        cout << node->getKey() << ": " << node->getValue() << endl; // 3. Procesar raíz ✅
    }

    /**
     * @brief Calcula la altura del árbol recursivamente
     * @param node Nodo actual en la recursión
     * @return Altura del subárbol
     */
    int heightHelper(Node *node) const
    {
        if (node == nullptr)
        {
            return -1; // Altura de árbol vacío es -1
        }
        int leftHeight = heightHelper(node->getLeft());
        int rightHeight = heightHelper(node->getRight());
        return 1 + max(leftHeight, rightHeight);
    }

    /**
     * @brief Elimina todos los nodos del árbol recursivamente
     * @param node Nodo actual en la recursión
     */
    void clearHelper(Node *node)
    {
        if (node == nullptr)
        {
            return;
        }
        clearHelper(node->getLeft());
        clearHelper(node->getRight());
        delete node;
    }

    /**
     * @brief Copia un árbol recursivamente
     * @param node Nodo del árbol a copiar
     * @return Puntero al nuevo nodo copiado
     */
    Node *copyHelper(Node *node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        Node *newNode = new Node(node->getKey(), node->getValue());
        newNode->setLeft(copyHelper(node->getLeft()));
        newNode->setRight(copyHelper(node->getRight()));
        return newNode;
    }

    /**
     * @brief Imprime el árbol de forma visual
     * @param node Nodo actual
     * @param prefix Prefijo para la indentación
     * @param isLeft Indica si es hijo izquierdo
     */
    void printTreeHelper(Node *node, const std::string &prefix, bool isLeft) const
    {
        if (node != nullptr)
        {
            std::cout << prefix;

            std::cout << (isLeft ? "├──" : "└──");

            // print the value of the node
            std::cout << node->getKey() << ": " << node->getValue() << std::endl;

            // enter the next tree level - left and right branch
            printTreeHelper(node->getLeft(), prefix + (isLeft ? "│   " : "    "), true);
            printTreeHelper(node->getRight(), prefix + (isLeft ? "│   " : "    "), false);
        }
    }

public:
    // ==================== CORE OPERATIONS ====================

    /**
     * @brief Constructor por defecto - Crea un BST vacío
     * @complexity O(1)
     */
    TreapMap() : root(nullptr), sz(0) {}

    /**
     * @brief Constructor de copia
     * @param other Árbol a copiar
     * @complexity O(n)
     */
    TreapMap(const TreapMap &other)
    {
        root = copyHelper(other.root); // Copiar el otro árbol
        sz = other.sz;                 // Actualizar el tamaño
    }

    /**
     * @brief Operador de asignación
     * @param other Árbol a copiar
     * @return Referencia al árbol actual
     * @complexity O(n)
     */
    TreapMap &operator=(const TreapMap &other)
    {
        if (this != &other)
        {
            clear();                       // Limpiar el árbol actual
            root = copyHelper(other.root); // Copiar el otro árbol
            sz = other.sz;                 // Actualizar el tamaño
        }
        return *this;
    }

    /**
     * @brief Destructor - Libera toda la memoria
     * @complexity O(n)
     */
    ~TreapMap()
    {
        clear(); // Usar el método clear para liberar memoria
    }

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
           root = insertHelper(root, k, v);
        }
    }
    /**
     * @brief Busca una clave en el árbol
     * @param k Clave a buscar
     * @return Puntero al valor asociado, nullptr si no existe
     * @complexity O(log n) en promedio, O(n) en el peor caso
     */
    const Value* find(const Key &k) const
    {
        if (empty())
        {
            return nullptr;
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
        if (find(k) == nullptr)
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
    void inorder() const
    {
        if (empty())
            return;
        inorderHelper(root);
    }

    /**
     * @brief Recorrido Preorden (Raíz-Izquierda-Derecha)
     * @complexity O(n)
     *
     * Útil para copiar el árbol o serialización
     */
    void preorder() const
    {
        if (empty())
            return;
        preorderHelper(root);
    }

    /**
     * @brief Recorrido Postorden (Izquierda-Derecha-Raíz)
     * @complexity O(n)
     *
     * Útil para eliminar el árbol o evaluación de expresiones
     */
    void postorder() const
    {
        if (empty())
            return;
        postorderHelper(root);
    }

    /**
     * @brief Recorrido por niveles (Breadth-First)
     * @complexity O(n)
     *
     * Visita todos los nodos nivel por nivel
     */
    void levelOrder() const
    {
        if (empty())
            return;

        std::queue<Node *> q;
        q.push(root);

        while (!q.empty())
        {
            Node *current = q.front();
            q.pop();

            std::cout << current->getKey() << ": " << current->getValue() << std::endl;

            if (current->hasLeft())
            {
                q.push(current->getLeft());
            }
            if (current->hasRight())
            {
                q.push(current->getRight());
            }
        }
    }

    // ==================== HELPER OPERATIONS ====================

    /**
     * @brief Encuentra la clave mínima del árbol
     * @return Clave mínima (nodo más a la izquierda)
     * @throw std::runtime_error si el árbol está vacío
     * @complexity O(log n) en promedio, O(n) en el peor caso
     */
    const Key &findMin() const
    {
        if (root == nullptr)
        {
            throw runtime_error("El árbol está vacío");
        }
        return findMinHelper(root)->getKey();
    }

    /**
     * @brief Encuentra la clave máxima del árbol
     * @return Clave máxima (nodo más a la derecha)
     * @throw std::runtime_error si el árbol está vacío
     * @complexity O(log n) en promedio, O(n) en el peor caso
     */
    const Key &findMaximum() const
    {
        if (root == nullptr)
        {
            throw runtime_error("El árbol está vacío");
        }
        return findMaxHelper(root)->getKey();
    }

    /**
     * @brief Calcula la altura del árbol
     * @return Altura (número de aristas en el camino más largo)
     * @complexity O(n)
     *
     * Un árbol vacío tiene altura -1, un árbol con solo raíz tiene altura 0
     */
    int height() const
    {
        return heightHelper(root);
    }

    /**
     * @brief Obtiene el número total de nodos
     * @return Número de nodos en el árbol
     * @complexity O(1)
     */
    unsigned int size() const { return sz; }

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
    void clear()
    {
        clearHelper(root);
        root = nullptr;
        sz = 0;
    }

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
    const Key &findSuccessor(const Key &k) const
    {
        Node *current = root;
        Node *successor = nullptr;

        while (current != nullptr)
        {
            if (k < current->getKey())
            {
                successor = current; // Posible sucesor
                current = current->getLeft();
            }
            else if (k > current->getKey())
            {
                current = current->getRight();
            }
            else
            {
                // Nodo encontrado
                if (current->hasRight())
                {
                    // El sucesor es el mínimo del subárbol derecho
                    return findMinHelper(current->getRight())->getKey();
                }
                break;
            }
        }

        if (successor == nullptr)
        {
            throw runtime_error("No existe sucesor para la clave dada");
        }
        return successor->getKey();
    }

    /**
     * @brief Encuentra el predecesor de una clave (anterior en orden)
     * @param k Clave cuyo predecesor se busca
     * @return Clave del predecesor
     * @throw std::runtime_error si no existe predecesor
     * @complexity O(log n) en promedio
     *
     * El predecesor es la mayor clave menor que la clave dada
     */
    const Key &findPredecessor(const Key &k) const
    {
        Node *current = root;
        Node *predecessor = nullptr;

        while (current != nullptr)
        {
            if (k > current->getKey())
            {
                predecessor = current; // Posible predecesor
                current = current->getRight();
            }
            else if (k < current->getKey())
            {
                current = current->getLeft();
            }
            else
            {
                // Nodo encontrado
                if (current->hasLeft())
                {
                    // El predecesor es el máximo del subárbol izquierdo
                    return findMaxHelper(current->getLeft())->getKey();
                }
                break;
            }
        }

        if (predecessor == nullptr)
        {
            throw runtime_error("No existe predecesor para la clave dada");
        }
        return predecessor->getKey();
    }

    /**
     * @brief Imprime una representación visual del árbol
     * @complexity O(n)
     *
     * Muestra la estructura del árbol de forma jerárquica
     */
    void printTree() const
    {
        printTreeHelper(root, "", false);
    }
};
#endif _TreapMap_
