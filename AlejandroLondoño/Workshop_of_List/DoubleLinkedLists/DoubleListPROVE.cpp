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

    void pop_back()
    {
        if (empty())
            return;

        Node *temp = last;
        last = last->getPrev();

        if (last == nullptr)
        {
            first = nullptr;
        }
        else
        {
            last->setNext(nullptr);
        }
        delete temp;
        sz--;
    }

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

    void pop_front()
    {
      if(empty()) return;

      Node *temp = first;
      first = first->getNext();

      if(first == nullptr){
        last = nullptr;
      }
      else {
        first->setPrev(nullptr);
      }

      delete temp;
      sz--;
    }

    
  T &front()
  {
    if (empty())
    {
      throw std::out_of_range("DoubleLinkedList Is Empty");
    }
    return first->getData();
  }

 
  const T &front() const
  {
    if (empty())
    {
      throw std::out_of_range("DoubleLinkedList Is Empty");
    }
    return first->getData();
  }

 
  T &back()
  {
    if (empty())
    {
      throw std::out_of_range("DoubleLinkedList Is Empty");
    }
    return last->getData();
  }
  

 
  const T &back() const
  {
    if (empty())
    {
      throw std::out_of_range("DoubleLinkedList Is Empty");
    }
    return last->getData();
  }
  


  unsigned int size() const { return sz; }

  void clear()
  {
    freeNodes(first);
    first = last = nullptr;
    sz = 0;
  }

  const T &at(unsigned int index) const
{
  if (index >= sz)
  {
    throw out_of_range("Index out of range");
  }

  Node *current;

      if (index <= sz / 2)
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

T &at(unsigned int index)
{
  if (index >= sz)
  {
    throw out_of_range("Index out of range");
  }

  Node *current;  // ahora con este tipo de lista podemos hacerlo un poco mas eficiente O(n/2) 

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

const T &operator[](unsigned int index) const
{
  return at(index);
}

T &operator[](unsigned int index)
{
  return at(index);
}

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
    first = temp->getPrev(); //No es un swap (temp = first; first = last; last = temp;), sino una reasignación apoyándome en la estructura enlazada de la lista.
}
    void print() const
    {
        Node *current = first;
        while (current != nullptr)
        {
            cout << current->getData() << " ";
            current = current->getNext();
        }
        cout << endl;
    }
};

int main()
{

    DoubleLinkedList<int> lista;
    lista.push_back(12);
    lista.push_back(45);
    lista.push_back(6);
    lista.push_back(2);
    lista.push_back(1);
    lista.print();

    lista.pop_back();
    lista.print();

    lista.push_front(3);
    lista.print();

    lista.pop_front();
    lista.pop_front();
    lista.print();

    lista.push_back(1);
    lista.push_back(2);
    lista.push_back(3);
    lista.print();

    lista.erase(5);
    lista.print();

    lista.insert(3,34);
    lista.print();

    lista.reverse();
    lista.print();

    lista.push_back(1);
    lista.print();

    lista.push_front(3);
    lista.print();

    cout << "First: " << lista.front() << endl;
cout << "Last: "  << lista.back()  << endl;

    return 0;
}
