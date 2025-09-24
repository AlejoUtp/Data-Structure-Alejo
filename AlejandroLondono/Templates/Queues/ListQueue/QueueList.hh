#ifndef ListQueue_hh
#define ListQueue_hh

#include "list.hh"
#include <iostream>

#include <iostream>
#include <stdexcept>
#include "List.hh" // Include your List implementation

using namespace std;

/**
 * @brief A queue implementation using a singly-linked list.
 *
 * This class implements a FIFO (First In, First Out) queue using an underlying
 * List data structure. Unlike array-based queues, this implementation has no
 * fixed capacity limit and can grow dynamically as needed.
 *
 * @tparam T Type of elements stored in the queue.
 */
template <typename T>
class QueueList
{
private:
    List<T> storage; ///< Underlying list to store queue elements.

public:
    /**
     * @brief Default constructor. Initializes an empty queue.
     */
    QueueList() : storage() {}

    /**
     * @brief Copy constructor. Creates a deep copy of another queue.
     * @param other Queue to copy.
     */
    QueueList(const QueueList<T> &other) : storage(other.storage) {}

    /**
     * @brief Assignment operator. Assigns the contents of another queue to this queue.
     * @param other Queue to copy.
     * @return Reference to this queue.
     */
    QueueList<T> &operator=(const QueueList<T> &other)
    {
        if (this != &other)
        {
            storage = other.storage;
        }
        return *this;
    }

    /**
     * @brief Destructor. No explicit cleanup needed (List handles its own memory).
     */
    ~QueueList() = default;

    /**
     * @brief Add an element to the rear of the queue.
     * @param val Value to add to the queue.
     * @note This operation never fails due to capacity limits (only memory limits).
     */
    void enqueue(const T &val)
    {
        storage.push_back(val);
    }

    /**
     * @brief Remove the front element from the queue.
     * @throws std::underflow_error if the queue is empty.
     */
    void dequeue()
    {
        if (isEmpty())
            throw std::underflow_error("Cannot dequeue from an empty queue.");
        storage.pop_front();
    }

    /**
     * @brief Get the front element of the queue without removing it.
     * @return Reference to the front element.
     * @throws std::underflow_error if the queue is empty.
     */
    T &front()
    {
        if (isEmpty())
            throw std::underflow_error("Cannot dequeue from an empty queue.");
        return storage.front();
    }

    /**
     * @brief Get the front element of the queue without removing it (const version).
     * @return Const reference to the front element.
     * @throws std::underflow_error if the queue is empty.
     */
    const T &front() const
    {
        if (isEmpty())
            throw std::underflow_error("Cannot dequeue from an empty queue.");
        return storage.front();
    }

    /**
     * @brief Get the rear element of the queue without removing it.
     * @return Reference to the rear element.
     * @throws std::underflow_error if the queue is empty.
     */
    T &back()
    {
        if (isEmpty())
            throw std::underflow_error("Cannot dequeue from an empty queue.");
        return storage.back();
    }

    /**
     * @brief Get the rear element of the queue without removing it (const version).
     * @return Const reference to the rear element.
     * @throws std::underflow_error if the queue is empty.
     */
    const T &back() const
    {
        if (isEmpty())
            throw std::underflow_error("Cannot dequeue from an empty queue.");
        return storage.back();
    }

    /**
     * @brief Check if the queue is empty.
     * @return true if the queue is empty, false otherwise.
     */
    bool isEmpty() const
    {
        return storage.empty();
    }

    /**
     * @brief Get the current number of elements in the queue.
     * @return The number of elements currently stored in the queue.
     */
    unsigned int size() const
    {
        return storage.size();
        
    }

    /**
     * @brief Remove all elements from the queue.
     * @note This operation makes the queue empty and frees all allocated memory.
     */
    void clear()
    {
        storage.clear();
    }

    /**
     * @brief Check if two queues are equal (same size and elements in same order).
     * @param other Queue to compare with.
     * @return true if queues are equal, false otherwise.
     * @note Unlike array-based queues, capacity is not compared since it's dynamic.
     */
    bool operator==(const QueueList<T> &other) const
    {
        return storage == other.storage;
    }

    /**
     * @brief Check if two queues are not equal.
     * @param other Queue to compare with.
     * @return true if queues are not equal, false otherwise.
     */
    bool operator!=(const QueueList<T> &other) const
    {
        return !(storage == other.storage);
    }

    /**
     * @brief Print all elements in the queue from front to rear.
     * @note This is for debugging purposes. Shows elements in the order they would be dequeued.
     */
    void print() const
    {
        if (isEmpty())
        {
            cout << "Queue is empty" << endl;
            return;
        }

        cout << "Front -> ";
        storage.print();
        cout << " <- Rear" << endl;
    }

    /**
     * @brief Get the maximum theoretical capacity of the queue.
     * @return Always returns a very large number since list-based queues are only limited by available memory.
     * @note This method is provided for interface compatibility with array-based queues.
     */
    unsigned int capacity() const
    {
        return -1;
    }

    /**
     * @brief Check if the queue is full.
     * @return Always returns false since list-based queues grow dynamically.
     * @note This method is provided for interface compatibility with array-based queues.
     */
    bool isFull() const
    {
        return false;
    }

    /**
     * @brief Append the elements of another queue to the end of this queue.
     * @param other Queue whose elements will be appended.
     * @note This leverages the underlying List's ability to append efficiently.
     */
    void append(const QueueList<T> &other)
    {
        storage.push_back(other.storage);
    }

    /**
     * @brief Prepend the elements of another queue to the beginning of this queue.
     * @param other Queue whose elements will be prepended.
     * @note This operation reverses the normal FIFO order and should be used carefully.
     * @warning This breaks FIFO semantics and is provided only for special use cases.
     */
    void prepend(const QueueList<T> &other)
    {
        storage.push_front(other.storage);
    }

    /**
     * @brief Reverse the order of all elements in the queue.
     * @warning This breaks FIFO semantics and should be used carefully.
     * @note After reversal, the original front becomes the rear and vice versa.
     */
    void reverse()
    {
        storage.reverse();
    }
};


#endif
