#ifndef BETTERVECTOR_HH
#define BETTERVECTOR_HH

#include <iostream>
#include <stdexcept>
#include <initializer_list>

using namespace std;

/**
 * @brief A dynamic vector implementation with automatic resizing.
 *
 * This class provides a dynamic array that can grow automatically as needed.
 * It maintains elements in contiguous memory and supports various operations
 * including automatic resizing based on a growth policy.
 *
 * @tparam T Type of elements stored in the vector.
 */
template <typename T>
class Vector
{
private:
    T *storage;       ///< Pointer to the array storing elements.
    unsigned int sz;  ///< Current number of elements in the vector.
    unsigned int cap; ///< Maximum number of elements that storage can hold.
    double policy;    ///< Growth factor for resizing the vector.

    /**
     * @brief Resize the vector's capacity using the growth policy.
     */
    void resize()
    {
        cap *= policy;
        T *NewStorage = new T[cap];
        for (unsigned int i = 0; i < sz; i++)
        {
            NewStorage[i] = storage[i];
        }
        delete[] storage;
        storage = NewStorage;
    }

    /**
     * @brief Reserve space for at least the specified capacity.
     * @param new_capacity The minimum capacity to reserve.
     */
    void reserve(unsigned int new_capacity)
    {
        if (new_capacity > cap)
        {
            cap = new_capacity;
            T *NewStorage = new T[new_capacity];
            for (unsigned int i = 0; i < sz; i++)
            {
                NewStorage[i] = storage[i];
            }
            delete[] storage;
            storage = NewStorage;
        }
    }

public:
    /**
     * @brief Default constructor. Creates vector with capacity 5 and growth policy 1.5.
     */
    Vector()
    {
        storage = new T[5];
        sz = 0;
        cap = 5;
        policy = 1.5;
    }

    /**
     * @brief Constructor with initial capacity and optional growth policy.
     * @param c Initial capacity for the vector.
     * @param p Growth policy factor (default 1.5).
     */
    Vector(unsigned int c, double p = 1.5)
    {
        storage = new T[c];
        sz = 0;
        cap = c;
        policy = p;
    }

    /**
     * @brief Copy constructor. Creates a deep copy of another vector.
     * @param other Vector to copy.
     */
    Vector(const Vector<T> &other)
    {
        sz = other.sz;
        cap = other.cap;
        policy = other.policy;
        storage = new T[cap];
        for (unsigned int i = 0; i < sz; i++)
        {
            storage[i] = other.storage[i];
        }
    }

    /**
     * @brief Constructor from initializer list.
     * @param init Initializer list with elements to insert.
     */
    Vector(std::initializer_list<T> init)
    {
        cap = (init.size() > 0 ? static_cast<unsigned int>(init.size()) : 5);
        storage = new T[cap];
        sz = 0;
        policy = 1.5;
        for (const auto &val : init)
        {
            storage[sz++] = val;
        }
    }

    /**
     * @brief Destructor. Frees allocated memory.
     */
    ~Vector()
    {
        delete[] storage;
    }

    /**
     * @brief Assignment operator. Assigns contents of another vector.
     * @param other Vector to copy from.
     * @return Reference to this vector.
     */
    Vector<T> &operator=(const Vector<T> &other)
    {
        if (this != &other)
        {
            delete[] storage;
            sz = other.sz;
            cap = other.cap;
            policy = other.policy;
            storage = new T[cap];
            for (unsigned int i = 0; i < sz; i++)
            {
                storage[i] = other.storage[i];
            }
        }
        return *this;
    }

    /**
     * @brief Get the current number of elements.
     * @return Number of elements in the vector.
     */
    unsigned int getSize() const { return sz; }

    /**
     * @brief Get the current capacity.
     * @return Current capacity of the vector.
     */
    unsigned int getCapacity() const { return cap; }

    /**
     * @brief Get the growth policy factor.
     * @return The growth policy factor.
     */
    double getPolicy() const { return policy; }

    /**
     * @brief Add element to the end of the vector.
     * @param elem Element to add.
     */
    void push_back(const T &elem)
    {
        if (sz == cap)
        {
            resize();
        }
        storage[sz] = elem;
        sz++;
    }

    /**
     * @brief Append another vector to this vector.
     * @param other Vector to append.
     */
    void append(const Vector<T> &other)
    {
        if (sz + other.sz >= cap)
        {
            reserve(sz + other.sz);
        }
        for (unsigned int i = 0; i < other.sz; i++)
        {
            storage[sz + i] = other.storage[i];
        }
        sz += other.sz;
    }

    /**
     * @brief Access element with bounds checking.
     * @param index Index of element to access.
     * @return Reference to element at index.
     * @throws std::out_of_range if index is out of bounds.
     */
    T &at(unsigned int index)
    {
        if (index >= sz)
        {
            throw std::out_of_range("Index out of range");
        }
        return storage[index];
    }

    /**
     * @brief Access element with bounds checking (const version).
     * @param index Index of element to access.
     * @return Const reference to element at index.
     * @throws std::out_of_range if index is out of bounds.
     */
    const T &at(unsigned int index) const
    {
        if (index >= sz)
        {
            throw std::out_of_range("Index out of range");
        }
        return storage[index];
    }

    // --- MISSING: Insert and erase operations ---
    /**
     * @brief Insert element at specific position.
     * @param index Position to insert at.
     * @param val Value to insert.
     * @throws std::out_of_range if index > size().
     */
    void insert(unsigned int index, const T &val)
    {
        if (index > sz)
            throw std::out_of_range("Index out of range");

        if (sz >= cap)
            resize();

        if (index == sz)
        {
            push_back(val);
            return;
        }

        for (unsigned int i = sz; i > index; i--)
        {
            storage[i] = storage[i - 1];
        }

        storage[index] = val;
        sz++;
    }

    /**
     * @brief Remove element at specific position.
     * @param index Position to remove from.
     * @throws std::out_of_range if index >= size().
     */
    void erase(unsigned int index)
    {
        if (index >= sz)
            throw std::out_of_range("index out of");

        if (index == sz - 1)
        {
            pop_back();
        }
        else
        {
            for (unsigned int i = index; i < sz - 1; i++)
            {
                storage[i] = storage[i + 1];
            }
            sz--;
        }
    }

    /**
     * @brief Remove the last element.
     */
    void pop_back()
    {
        if (empty())
            throw std::out_of_range("Vector is empty");
        sz--;
    }

    /**
     * @brief Reduce capacity to match current size.
     */
    void shrink_to_fit()
    {
        if (sz != cap)
        {
            T *NewStorage = new T[sz];
            for (unsigned int i = 0; i < sz; i++)
            {
                NewStorage[i] = storage[i];
            }
            delete[] storage;
            storage = NewStorage;
            cap = sz;
        }
    }

    // --- MISSING: Standard vector operations ---
    /**
     * @brief Check if vector is empty.
     * @return true if empty, false otherwise.
     */
    bool empty() const { return sz == 0; }

    /**
     * @brief Get reference to first element.
     * @return Reference to first element.
     * @throws std::out_of_range if vector is empty.
     */
    T &front()
    {
        if (empty())
            throw std::out_of_range("Vector is empty");

        return storage[0];
    }

    /**
     * @brief Get const reference to first element.
     * @return Const reference to first element.
     * @throws std::out_of_range if vector is empty.
     */
    const T &front() const
    {
        if (empty())
            throw std::out_of_range("Vector is empty");

        return storage[0];
    }

    /**
     * @brief Get reference to last element.
     * @return Reference to last element.
     * @throws std::out_of_range if vector is empty.
     */
    T &back()
    {
        if (empty())
            throw std::out_of_range("Vector is empty");

        return storage[sz - 1];
    }

    /**
     * @brief Get const reference to last element.
     * @return Const reference to last element.
     * @throws std::out_of_range if vector is empty.
     */
    const T &back() const
    {
        if (empty())
            throw std::out_of_range("Vector is empty");

        return storage[sz - 1];
    }

    /**
     * @brief Clear all elements from vector.
     */
    void clear() { sz = 0; } // sz es solo un contador logico, la reserva fisica de memoria la decide la capacidad.

    /**
     * @brief Access element without bounds checking.
     * @param index Index of element to access.
     * @return Reference to element at index.
     */
    T &operator[](unsigned int index)
    {
        return storage[index];
    }

    /**
     * @brief Access element without bounds checking (const version).
     * @param index Index of element to access.
     * @return Const reference to element at index.
     */
    const T &operator[](unsigned int index) const
    {
        return storage[index];
    }

    // --- MISSING: Comparison operators ---
    /**
     * @brief Check if two vectors are equal.
     * @param other Vector to compare with.
     * @return true if vectors are equal, false otherwise.
     */
    bool operator==(const Vector<T> &other) const
    {
        if (sz != other.sz)
            return false;

        for (unsigned int i = 0; i < sz; i++)
        {
            if (storage[i] != other.storage[i])
                return false;
        }

        return true;
    }

    /**
     * @brief Check if two vectors are not equal.
     * @param other Vector to compare with.
     * @return true if vectors are not equal, false otherwise.
     */
    bool operator!=(const Vector<T> &other) const
    {
        return !(*this == other);
    }

    /**
     * @brief Get pointer to underlying data.
     * @return Pointer to first element.
     */
    T *data()
    {
        return storage;
    }

    /**
     * @brief Get const pointer to underlying data.
     * @return Const pointer to first element.
     */
    const T *data() const
    {
        return storage;
    }

    /**
     * @brief Print vector contents for debugging.
     */
    void print() const
    {
        cout << "[";
        for (unsigned int i = 0; i < sz; i++)
        {
            cout << storage[i];
            if (i < sz - 1)
                cout << ", ";
        }
        cout << "]" << endl;
    }
};

#endif 