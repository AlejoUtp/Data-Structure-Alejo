#ifndef DOUBLE_LINKED_LIST_HH
#define DOUBLE_LINKED_LIST_HH


#include <iostream>
#include <stdexcept>

using namespace std;

/**
 * @brief A doubly-linked list implementation.
 *
 * @tparam T Type of elements stored in the list.
 */
template <typename T>
class DoubleLinkedList
{
private:
  /**
   * @brief Node class representing an element in the doubly-linked list.
   */
  class Node
  {
  private:
    T data;     ///< Value stored in the node.
    Node *next; ///< Pointer to the next node.
    Node *prev; ///< Pointer to the previous node.

  public:
    /**
     * @brief Default constructor. Initializes data, next, and prev pointers.
     */
    Node() : data(), next(nullptr), prev(nullptr) {}

    /**
     * @brief Constructor with value.
     * @param v Value to store in the node.
     */
    Node(const T &v) : data(v), next(nullptr), prev(nullptr) {}

    /**
     * @brief Get the next node pointer.
     * @return Pointer to the next node.
     */
    Node *getNext() const { return next; }

    /**
     * @brief Get the previous node pointer.
     * @return Pointer to the previous node.
     */
    Node *getPrev() const { return prev; }

    /**
     * @brief Set the next node pointer.
     * @param n Pointer to the next node.
     */
    void setNext(Node *n) { next = n; }

    /**
     * @brief Set the previous node pointer.
     * @param p Pointer to the previous node.
     */
    void setPrev(Node *p) { prev = p; }

    /**
     * @brief Get the data stored in the node.
     * @return The data stored in the node.
     */
    T getData() const { return data; }

    /**
     * @brief Get a reference to the data stored in the node.
     * @return Reference to the data stored in the node.
     */
    T &getData() { return data; }
  };

private:
  Node *first;     ///< Pointer to the first node in the list.
  Node *last;      ///< Pointer to the last node in the list.
  unsigned int sz; ///< Number of elements in the list.

  /**
   * @brief Free all nodes starting from a given node.
   * @param node Pointer to the starting node.
   */
  void freeNodes(Node *node)
  {
    while (node != nullptr)
    {
      Node *temp = node->getNext();
      delete node;
      node = temp;
    }
  }

public:
  /**
   * @brief Default constructor. Initializes an empty list.
   */
  DoubleLinkedList() : first(nullptr), last(nullptr), sz(0) {}

  /**
   * @brief Destructor. Deletes all nodes in the list.
   */
  ~DoubleLinkedList()
  {
    freeNodes(first);
  }

  /**
   * @brief Check if the list is empty.
   * @return true if the list is empty, false otherwise.
   */
  bool empty() const
  {
    return first == nullptr && last == nullptr;
  }

  /**
   * @brief Add an element to the end of the list.
   * @param val Value to add.
   */
  void push_back(const T &val)
  {
    Node *newNode = new Node(val);
    if (empty())
    {
      last = first = newNode;
    }
    else
    {
      last->setNext(newNode);
      newNode->setPrev(last);
      last = newNode;
    }
    sz++;
  }

  /**
   * @brief Remove the last element from the list.
   *
   * This function removes the last node from the list. If the list has
   * only one node, it handles the special case by setting both `first`
   * and `last` to `nullptr`. If the list is empty, it does nothing.
   */
  void pop_back()
  {
    if (empty())
      throw std::out_of_range("list is empty");

    Node *temp = last;
    last = last->getPrev();

    if (last != nullptr)
    {
      last->setNext(nullptr);
    }
    else
    {
      first = nullptr;
    }
    delete temp;
    sz--;
  }

  /**
   * @brief Add an element to the beginning of the list.
   * @param val Value to add.
   */
  void push_front(const T &val)
  {
    Node *newNode = new Node(val);

    if (empty())
    {
      first = last = newNode;
    }
    else
    {
      newNode->setNext(first);
      first->setPrev(newNode);
      first = newNode;
    }
    sz++;
  }

  /**
   * @brief Remove the first element from the list.
   *
   * This function removes the first node from the list. If the list has
   * only one node, it handles the special case by setting both `first`
   * and `last` to `nullptr`. If the list is empty, it does nothing.
   */
  void pop_front()
  {
    if (empty())
      throw std::out_of_range("list is empty");

    Node *temp = first;
    first = first->getNext();

    if (first != nullptr)
    {
      first->setPrev(nullptr);
    }
    else
    {
      last = nullptr;
    }

    delete temp;
    sz--;
  }

  /**
   * @brief Get the first element in the list.
   *
   * This function returns a reference to the data stored in the first node.
   *
   * @return Reference to the first element.
   * @throws std::out_of_range if the list is empty.
   */
  T &front()
  {
    if (empty())
    {
      throw std::out_of_range("DoubleLinkedList Is Empty");
    }
    return first->getData();
  }

  /**
   * @brief Get the first element in the list (const version).
   *
   * This function returns a const reference to the data stored in the first node.
   *
   * @return Const reference to the first element.
   * @throws std::out_of_range if the list is empty.
   */
  const T &front() const
  {
    if (empty())
    {
      throw std::out_of_range("DoubleLinkedList Is Empty");
    }
    return first->getData();
  }

  /**
   * @brief Get the last element in the list.
   *
   * This function returns a reference to the data stored in the last node.
   *
   * @return Reference to the last element.
   * @throws std::out_of_range if the list is empty.
   */
  T &back()
  {
    if (empty())
    {
      throw std::out_of_range("DoubleLinkedList Is Empty");
    }
    return last->getData();
  }

  /**
   * @brief Get the last element in the list (const version).
   *
   * This function returns a const reference to the data stored in the last node.
   *
   * @return Const reference to the last element.
   * @throws std::out_of_range if the list is empty.
   */
  const T &
  back() const
  {
    if (empty())
    {
      throw std::out_of_range("DoubleLinkedList Is Empty");
    }
    return last->getData();
  }

  /**
   * @brief Get the number of elements in the list.
   *
   * This function returns the size of the list.
   *
   * @return The size of the list.
   */
  unsigned int
  size() const
  {
    return sz;
  }

  /**
   * @brief Remove all elements from the list.
   *
   * This function deletes all nodes in the list and resets the `first`, `last`, and `sz` attributes.
   */
  void clear()
  {
    freeNodes(first);
    first = last = nullptr;
    sz = 0;
  }

  /**
   * @brief Get the element at a specific index (const version).
   *
   * This function returns a const reference to the data stored in the node at the specified index.
   *
   * @param index Index of the element to retrieve.
   * @return Const reference to the element at the specified index.
   * @throws std::out_of_range if the index is out of bounds.
   */
  const T &at(unsigned int index) const
  {
    if (index >= sz)
    {
      throw out_of_range("Index out of range");
    }

    Node *current; // ahora con este tipo de lista podemos hacerlo un poco mas eficiente O(n/2)

    if (index <= sz / 2) // dependiendo en donde se encuentre el index podemos comenzar en first hasta la mitado en last hasta la mitad
    {
      current = first;
      for (unsigned int i = 0; i < index; i++)
      {
        current = current->getNext();
      }
    }
    else
    {
      current = last;
      for (unsigned int i = sz - 1; i > index; i--)
      {
        current = current->getPrev();
      }
    }
    return current->getData();
  }

  /**
   * @brief Get the element at a specific index.
   *
   * This function returns a reference to the data stored in the node at the specified index.
   *
   * @param index Index of the element to retrieve.
   * @return Reference to the element at the specified index.
   * @throws std::out_of_range if the index is out of bounds.
   */
  T &at(unsigned int index)
  {
    if (index >= sz)
    {
      throw out_of_range("Index out of range");
    }

    Node *current; // ahora con este tipo de lista podemos hacerlo un poco mas eficiente O(n/2)

    if (index <= sz / 2) // dependiendo en donde se encuentre el index podemos comenzar en first hasta la mitado en last hasta la mitad
    {
      current = first;
      for (unsigned int i = 0; i < index; i++)
      {
        current = current->getNext();
      }
    }
    else
    {
      current = last;
      for (unsigned int i = sz - 1; i > index; i--)
      {
        current = current->getPrev();
      }
    }
    return current->getData();
  }

  /**
   * @brief Access an element using the subscript operator (const version).
   *
   * This function returns a const reference to the data stored in the node at the specified index.
   *
   * @param index Index of the element to access.
   * @return Const reference to the element at the specified index.
   */
  const T &operator[](unsigned int index) const
  {
    return at(index);
  }

  /**
   * @brief Access an element using the subscript operator.
   *
   * This function returns a reference to the data stored in the node at the specified index.
   *
   * @param index Index of the element to access.
   * @return Reference to the element at the specified index.
   */
  T &operator[](unsigned int index)
  {
    return at(index);
  }

  /**
   * @brief Insert an element at a specific index.
   *
   * This function inserts a new node with the given value at the specified index.
   *
   * @param index Index where the element will be inserted.
   * @param val Value to insert.
   * @throws std::out_of_range if the index is out of bounds.
   */
  void insert(unsigned int index, const T &val)
  {
    if (index > sz)
      throw std::out_of_range("Index out of range");

    if (index == 0)
    {
      push_front(val);
    }
    else if (index == sz)
    {
      push_back(val);
    }
    else
    {
      Node *newNode = new Node(val);
      Node *current;

      if (index < sz / 2)
      {
        current = first;
        for (unsigned int i = 0; i < index - 1; i++)
        {
          current = current->getNext();
        }
      }
      else
      {
        current = last;
        for (unsigned int i = sz - 1; i > index - 1; i--)
        {
          current = current->getPrev();
        }
      }

      Node *nextNode = (current->getNext());

      newNode->setNext(nextNode);
      newNode->setPrev(current);

      nextNode->setPrev(newNode);
      current->setNext(newNode);

      sz++;
    }
  }

  /**
   * @brief Remove an element at a specific index.
   *
   * This function removes the node at the specified index.
   *
   * @param index Index of the element to remove.
   * @throws std::out_of_range if the index is out of bounds.
   */
  void erase(unsigned int index)
  {
    if (index >= sz)
      throw std::out_of_range("Index out of range");

    if (index == 0)
    {
      pop_front();
    }
    else if (index == sz - 1)
    {
      pop_back();
    }
    else
    {
      Node *current;

      if (index < sz / 2)
      {
        current = first;
        for (unsigned int i = 0; i < index - 1; i++)
        {
          current = current->getNext();
        }
      }
      else
      {
        current = last;
        for (unsigned int i = sz - 1; i > index - 1; i--)
        {
          current = current->getPrev();
        }
      }

      Node *temp = current->getNext();

      current->setNext(temp->getNext());
      temp->getNext()->setPrev(current);

      delete temp;

      sz--;
    }
  }

  /**
   * @brief Reverse the order of elements in the list.
   *
   * This function reverses the order of the nodes in the list. It updates
   * the `first` and `last` pointers accordingly.
   *
   * @note The function does nothing if the list is empty or has only one node.
   */
  void reverse()
  {
    if (!first || first == last)
    {
      return;
    }

    Node *current = first;
    Node *temp = nullptr;

    while (current != nullptr)
    {
      temp = current->getPrev();
      current->setPrev(current->getNext());
      current->setNext(temp);
      current = current->getPrev();
    }

    last = first;
    first = temp->getPrev(); // No es un swap (temp = first; first = last; last = temp;), sino una reasignación apoyándome en la estructura enlazada de la lista.
  }

  /**
   * @brief Copy constructor. Creates a deep copy of another list.
   *
   * This function creates a new list that is a deep copy of the given list.
   *
   * @param other List to copy.
   */
  DoubleLinkedList(const DoubleLinkedList<T> &other)
  {
    first = last = nullptr;
    sz = 0;

    Node *current = other.first; // el codigo queda igual a el de list, existe una forma de intentar optimizar, pero es una mejora muy pequeña a comparacion de los bugs que puede ocacionar
    while (current != nullptr)
    {
      push_back(current->getData());
      current = current->getNext();
    }
  }

  /**
   * @brief Append the elements of another list to the end of this list.
   *
   * This function appends all elements of the given list to the end of the current list.
   *
   * @param other List whose elements will be appended.
   */
  void push_back(const DoubleLinkedList<T> &other)
  {
    if (other.empty())
      return;

    Node *current = other.first;
    while (current != nullptr)
    {
      push_back(current->getData()); // ← Esta función YA maneja los prev
      current = current->getNext();
    }
  }

  /**
   * @brief Prepend the elements of another list to the beginning of this list.
   *
   * This function prepends all elements of the given list to the beginning of the current list.
   *
   * @param other List whose elements will be prepended.
   */
  void push_front(const DoubleLinkedList<T> &other)
  {
    if (other.empty())
      return;

    Node *current = other.last; // a comparacion de la lista simplemente enlazada ahora no es necesario hacer una copia de la lista other y cambiar a donde apuntan sus nodos
    while (current != nullptr) // ahora simplemente se hace lo mismo que el push_back de agregar elementeo por elemento pero al revez desde last hasta nullptr osea terminar la lista
    {
      push_front(current->getData());  
      current = current->getPrev();
    }
  }

/**
 * @brief Assignment operator. Assigns the contents of another list to this list.
 * 
 * This function clears the current list and performs a deep copy of the given list.
 * 
 * @param other List to copy.
 * @return Reference to this list.
 */
DoubleLinkedList& operator=(const DoubleLinkedList &other) {  //operador de asignacion
    if (this != &other) { // Evitar autoasignación
        clear(); // Limpiar la lista actual
        Node* current = other.first;
        while (current != nullptr) {
            push_back(current->getData());
            current = current->getNext();
        }
    }
    return *this;
}


  void print() const
  {
    Node *temp = first;
    while (temp != nullptr)
    {
      cout << temp->getData() << " ";
      temp = temp->getNext();
    }
    cout << endl;
  }
};

#endif // DOUBLE_LINKED_LIST_HH