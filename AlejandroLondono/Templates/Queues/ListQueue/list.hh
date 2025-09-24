#ifndef LIST_HH
#define LIST_HH

#include <iostream>
#include <stdexcept>

using namespace std;

/**
 * @brief A simple singly-linked list implementation.
 *
 * @tparam T Type of elements stored in the list.
 */
template <typename T>
class List
{
private:
  /**
   * @brief Node class representing an element in the list.
   */
  class Node
  {
  private:
    T data;     ///< Value stored in the node.
    Node *next; ///< Pointer to the next node.

  public:
    /**
     * @brief Default constructor. Initializes data and next pointer.
     */
    Node() : data(), next(nullptr) {}

    /**
     * @brief Constructor with value.
     * @param v Value to store in the node.
     */
    Node(const T &v) : data(v), next(nullptr) {}

    /**
     * @brief Get the next node pointer.
     * @return Pointer to the next node.
     */
    Node *getNext() const { return next; }

    /**
     * @brief Set the next node pointer.
     * @param n Pointer to the next node.
     */
    void setNext(Node *n) { next = n; }

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
  List() : first(nullptr), last(nullptr), sz(0) {}

  /**
   * @brief Destructor. Deletes all nodes in the list.
   */
  ~List()
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
    Node *NewNode = new Node(val);
    if (!empty())
    {
      last->setNext(NewNode);
    }
    else
    {
      first = NewNode;
    }
    last = NewNode;
    sz++;
  }

  /**
   * @brief Remove the last element from the list.
   *
   * @note If the list is empty, this function does nothing.
   */
  void pop_back()
  {
    if (empty())
    {
      return;
    }

    if (first == last)
    {
      delete first;
      first = last = nullptr;
    }
    else
    {
      Node *current = first;
      while (current->getNext() != last)
      {
        current = current->getNext();
      }
      delete last;
      last = current;
      last->setNext(nullptr);
    }
    sz--;
  }

  /**
   * @brief Add an element to the beginning of the list.
   * @param val Value to add.
   */
  void
  push_front(const T &val)
  {
    Node *NewNode = new Node(val);
    if (empty())
    {
      last = NewNode;
    }
    else
    {
      NewNode->setNext(first);
    }
    first = NewNode;
    sz++;
  }

  /**
   * @brief Remove the first element from the list.
   *
   * @note If the list is empty, this function does nothing.
   */
  void pop_front()
  {
    if (!empty())
    {
      if (first == last)
      {
        delete first;
        first = last = nullptr;
      }
      else
      {
        Node *temp = first->getNext();
        delete first;
        first = temp;
      }
      sz--;
    }
  }

  /**
   * @brief Get the first element in the list.
   * @return Reference to the first element.
   * @throws std::out_of_range if the list is empty.
   */
  T &front()
  {
    if (empty())
    {
      throw std::out_of_range("List is empty");
    }
    return first->getData();
  }

  /**
   * @brief Get the first element in the list (const version).
   * @return Const reference to the first element.
   * @throws std::out_of_range if the list is empty.
   */
  const T &front() const
  {
    if (empty())
    {
      throw std::out_of_range("List is empty");
    }
    return first->getData();
  }

  /**
   * @brief Get the last element in the list.
   * @return Reference to the last element.
   * @throws std::out_of_range if the list is empty.
   */
  T &back()
  {
    if (empty())
    {
      throw std::out_of_range("list is empty");
    }
    return last->getData();
  }

  /**
   * @brief Get the last element in the list (const version).
   * @return Const reference to the last element.
   * @throws std::out_of_range if the list is empty.
   */
  const T &back() const
  {
    if (empty())
    {
      throw std::out_of_range("list is empty");
    }
    return last->getData();
  }

  /**
   * @brief Get the number of elements in the list.
   * @return The size of the list.
   */
  unsigned int size() const { return sz; }

  /**
   * @brief Remove all elements from the list.
   */
  void clear()
  {
    freeNodes(first);
    first = last = nullptr;
    sz = 0;
  }

  /**
   * @brief Get the element at a specific index (const version).
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
    Node *current = first;
    for (unsigned int i = 0; i < index; i++)
    {
      current = current->getNext();
    }
    return current->getData();
  }

  /**
   * @brief Get the element at a specific index.
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
    Node *current = first;
    for (unsigned int i = 0; i < index; i++)
    {
      current = current->getNext();
    }
    return current->getData();
  }

  /**
   * @brief Access an element using the subscript operator (const version).
   * @param index Index of the element to access.
   * @return Const reference to the element at the specified index.
   */
  const T &operator[](unsigned int index) const { return at(index); }

  /**
   * @brief Access an element using the subscript operator.
   * @param index Index of the element to access.
   * @return Reference to the element at the specified index.
   */
  T &operator[](unsigned int index) { return at(index); }

  /**
   * @brief Insert an element at a specific index.
   * @param index Index where the element will be inserted.
   * @param val Value to insert.
   * @throws std::out_of_range if the index is out of bounds.
   */
  void insert(unsigned int index, const T &val)
  {
    if (index > sz)
    {
      throw out_of_range("Index out of range");
    }
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
      Node *current = first;
      for (unsigned int i = 0; i < index - 1; i++)
      {
        current = current->getNext();
      }
      newNode->setNext(current->getNext());
      current->setNext(newNode);
      sz++;
    }
  }

  /**
   * @brief Remove an element at a specific index.
   * @param index Index of the element to remove.
   * @throws std::out_of_range if the index is out of bounds.
   */
  void erase(unsigned int index)
  {
    if (index >= sz)
    {
      throw out_of_range("index out of range");
    }
    if (index == 0)
    {
      pop_front();
      return;
    }
    else if (index == sz - 1)
    {
      pop_back();
      return;
    }
    Node *current = first;
    for (unsigned int i = 0; i < index - 1; i++)
    {
      current = current->getNext();
    }
    Node *temp = current->getNext();
    current->setNext(temp->getNext());
    delete temp;
    sz--;
  }

  /**
   * @brief Print the elements of the list.
   */
  void print() const
  {
    Node *temp = first;
    while (temp != nullptr)
    {
      cout << temp->getData() << " -> ";
      temp = temp->getNext();
    }
    cout << endl;
  }

  /**
   * @brief Reverse the order of elements in the list.
   */
  void reverse()
  {
    if (empty() || first == last)
    {
      return;
    }
    Node *prev = nullptr;
    Node *current = first;
    Node *next = nullptr;
    last = first;
    while (current != nullptr)
    {
      next = current->getNext();
      current->setNext(prev);
      prev = current;
      current = next;
    }
    first = prev;
  }

  /**
   * @brief Copy constructor. Creates a deep copy of another list.
   * @param other List to copy.
   */
  List(const List<T> &other)
  {
    first = last = nullptr;
    sz = 0;
    Node *current = other.first;
    while (current != nullptr)
    {
      push_back(current->getData());
      current = current->getNext();
    }
  }

  /**
   * @brief Append the elements of another list to the end of this list.
   * @param other List whose elements will be appended.
   */
  void push_back(const List<T> &other)
  {
    if (other.empty())
      return;

    Node *current = other.first;
    while (current != nullptr)
    {
      push_back(current->getData());
      current = current->getNext();
    }
  }

  /**
   * @brief Prepend the elements of another list to the beginning of this list.
   * @param other List whose elements will be prepended.
   */
  void push_front(const List<T> &other)
  {
    if (other.empty())
      return;

    if (empty())
    {
      Node *current = other.first;
      while (current != nullptr)
      {
        push_back(current->getData());
        current = current->getNext();
      }

      List *templist = new List(other);
      templist->last->setNext(first);
      first = templist->first;
      if (last == nullptr)
      {
        last = templist->last;
      }
      sz += templist->sz;
      templist->first = templist->last = nullptr;
      templist->sz = 0;
      delete templist;
    }
  }

  List<T> &operator=(const List<T> &other)
  { // operador de asignacion
    if (this != &other)
    {          // Evitar autoasignación
      clear(); // Limpiar la lista actual
      Node *current = other.first;
      while (current != nullptr)
      {
        push_back(current->getData());
        current = current->getNext();
      }
    }
    return *this;
  }

  /**
   * @brief Check if two lists are equal.
   * @param other List to compare with.
   * @return true if lists are equal, false otherwise.
   */
  bool operator==(const List<T> &other) const
  {
    if (sz != other.sz)
    {
      return false;
    }

    Node *current = first;
    Node *otherCurrent = other.first;

    while (current != nullptr)
    {
      if (current->getData() != otherCurrent->getData())
      {
        return false;
      }
      current = current->getNext();
      otherCurrent = otherCurrent->getNext();
    }

    return true;
  }
};

#endif // LIST_HH