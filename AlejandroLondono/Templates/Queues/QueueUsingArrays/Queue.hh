#ifndef QUEUE_HH
#define QUEUE_HH
#include "Array.hh"

#include <iostream>
#include <stdexcept>

using namespace std;

/*1. Array<T> buffer

Qué es: El contenedor que almacena los datos
Por qué: Necesitas donde guardar los elementos

2. unsigned int frontIdx

Qué es: Índice del primer elemento en la queue
Por qué: Como no puedes "mover" elementos físicamente, necesitas saber dónde está el frente
Ejemplo: Si tienes [_, _, 10, 20, 30] → frontIdx = 2

3. unsigned int rearIdx

Qué es: Índice donde se insertará el próximo elemento
Por qué: Necesitas saber dónde agregar el siguiente elemento
Ejemplo: Si tienes [_, _, 10, 20, 30] → rearIdx = 5 (siguiente posición libre)

4. unsigned int sz

Qué es: Cantidad actual de elementos
Por qué: El Array siempre tiene el mismo tamaño físico, pero la queue puede tener menos elementos
Ejemplo: Array de tamaño 10, pero queue con 3 elementos → sz = 3

5. unsigned int cap

Qué es: Capacidad máxima
Por qué: Para saber cuándo la queue está llena y evitar overflow*/

/**
 * @brief A basic queue implementation using a fixed-size array.
 *
 * This class implements a FIFO (First In, First Out) queue using an underlying
 * fixed-size Array. Elements are added at the rear and removed from the front.
 * The queue has a maximum capacity determined at construction time.
 *
 * @tparam T Type of elements stored in the queue.
 */
template <typename T>
class Queue
{
private:
    Array<T> buffer;       ///< Underlying array to store queue elements.
    unsigned int frontIdx; ///< Index of the front element.
    unsigned int rearIdx;  ///< Index where the next element will be inserted.
    unsigned int sz;       ///< Current number of elements in the queue.
    unsigned int cap;      ///< Maximum capacity of the queue.

public:
    /**
     * @brief Constructor with fixed capacity.
     * @param capacity Maximum number of elements the queue can hold.
     * @throws std::invalid_argument if capacity is 0.
     */
    explicit Queue(unsigned int capacity) : buffer(capacity, T{}), cap(capacity), frontIdx(0), rearIdx(0), sz(0)
    {
        // Cuerpo vacío - todo se hace en lista de inicialización
    }

    /**
     * @brief Copy constructor. Creates a deep copy of another queue.
     * @param other Queue to copy.
     */
    Queue(const Queue<T> &other) : buffer(other.buffer), cap(other.cap), frontIdx(other.frontIdx), rearIdx(other.rearIdx), sz(other.sz)
    {
        // Cuerpo vacío - todo se hace en lista de inicialización
    }

    /**
     * @brief Assignment operator. Assigns the contents of another queue to this queue.
     * @param other Queue to copy.
     * @return Reference to this queue.
     * @throws std::invalid_argument if queues have different capacities.
     */
    Queue<T> &operator=(const Queue<T> &other)
    {
        if (this != &other)
        {
            if (cap != other.cap)
                throw invalid_argument("Queues must have the same capacity for assignment");

            buffer = other.buffer;
            frontIdx = other.frontIdx;
            rearIdx = other.rearIdx;
            sz = other.sz;
        }
        return *this;
    }

    /**
     * @brief Destructor. No explicit cleanup needed (Array handles its own memory).
     */
    ~Queue() = default;

    /**
     * @brief Add an element to the rear of the queue.
     * @param val Value to add to the queue.
     * @throws std::overflow_error if the queue is full.
     */
    void enqueue(const T &val)
    {
        if (sz == cap)
            throw std::overflow_error("Queue is full");
        buffer[rearIdx] = val;
        rearIdx++;
        sz++;
    }

    /**
     * @brief Remove the front element from the queue.
     * @throws std::underflow_error if the queue is empty.
     */
    void dequeue()
    {
        if (sz == 0)
            throw std::underflow_error("queue is empty");

        frontIdx++;
        sz--;

        if (sz == 0) // Reset cuando queda vacía
        {
            frontIdx = rearIdx = 0;
        }
    }

    /**
     * @brief Get the front element of the queue without removing it.
     * @return Reference to the front element.
     * @throws std::underflow_error if the queue is empty.
     */
    T &front()
    {
        if (sz == 0)
            throw std::underflow_error("queue is empty");

        return buffer[frontIdx];
    }

    /**
     * @brief Get the front element of the queue without removing it (const version).
     * @return Const reference to the front element.
     * @throws std::underflow_error if the queue is empty.
     */
    const T &front() const
    {
        if (sz == 0)
            throw std::underflow_error("queue is empty");

        return buffer[frontIdx];
    }

    /**
     * @brief Get the rear element of the queue without removing it.
     * @return Reference to the rear element.
     * @throws std::underflow_error if the queue is empty.
     */
    T &back()
    {
        if (sz == 0)
            throw std::underflow_error("queue is empty");

        return buffer[rearIdx - 1];
    }

    /**
     * @brief Get the rear element of the queue without removing it (const version).
     * @return Const reference to the rear element.
     * @throws std::underflow_error if the queue is empty.
     */
    const T &back() const
    {
        if (sz == 0)
            throw std::underflow_error("queue is empty");

        return buffer[rearIdx - 1];
    }

    /**
     * @brief Check if the queue is empty.
     * @return true if the queue is empty, false otherwise.
     */
    bool isEmpty() const
    {
        return sz == 0;
    }

    /**
     * @brief Check if the queue is full.
     * @return true if the queue is full, false otherwise.
     */
    bool isFull() const
    {
        return sz == cap;
    }

    /**
     * @brief Get the current number of elements in the queue.
     * @return The number of elements currently stored in the queue.
     */
    unsigned int size() const
    {
        return sz;
    }

    /**
     * @brief Get the maximum capacity of the queue.
     * @return The maximum number of elements the queue can hold.
     */
    unsigned int capacity() const
    {
        return cap;
    }

    /**
     * @brief Remove all elements from the queue.
     * @note This operation makes the queue empty but doesn't change its capacity.
     */
    void clear()
    {
        frontIdx = 0;
        rearIdx = 0;
        sz = 0;
    }

    /**
     * @brief Check if two queues are equal (same capacity, size, and elements in same order).
     * @param other Queue to compare with.
     * @return true if queues are equal, false otherwise.
     */
    bool operator==(const Queue<T> &other) const
    {
        if (cap != other.cap)
            return false;
        if (sz != other.sz)
            return false;

        for (unsigned int i = 0; i < sz; i++)
        {
            if (buffer[frontIdx + i] != other.buffer[other.frontIdx + i])
                return false;
        }
        return true;
    }

    /**
     * @brief Check if two queues are not equal.
     * @param other Queue to compare with.
     * @return true if queues are not equal, false otherwise.
     */
    bool operator!=(const Queue<T> &other) const
    {
        return !(*this == other);
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
        for (unsigned int i = 0; i < sz; i++)
        {
            unsigned int index = frontIdx + i;
            cout << buffer[index];
            if (i < sz - 1)
            {
                cout << " -> ";
            }
        }
        cout << " <- Rear" << endl;
    }
};

#endif