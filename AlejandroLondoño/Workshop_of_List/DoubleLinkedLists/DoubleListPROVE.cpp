#include <iostream>
#include <stdexcept>

using namespace std;

/**
 * @brief A simple singly-linked list implementation.
 *
 * @tparam T Type of elements stored in the list.
 */
template <typename T>
class DoubleLinkedList
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
    Node *prev; ///< Pointer to the previous node.
  public:
    /**
     * @brief Default constructor. Initializes data and next pointer.
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
        last = first = nullptr;
      }
      else
      {
        last->setNext(newNode);
        newNode->setPrev(last);
        last = newNode;
      }
      sz++;
    }

    void print() const
    {
      Node *current = first;
      while (current != nullptr)
      {
        cout << current->getData << " ";
        current = current->getNext();
      }
      cout << endl;
    }
  };

int main(){
    
    DoubleLinkedList<int> lista;
    lista.push_back(2);
    lista.push_back(2);
    lista.push_back(2);
    lista.push_back(2);
    lista.push_back(2);

    lista.print();
    return 0;
}
 

