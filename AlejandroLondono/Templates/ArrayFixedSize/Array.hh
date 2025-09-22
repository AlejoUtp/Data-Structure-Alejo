#ifndef ARRAY_HH
#define ARRAY_HH

#include <iostream>
#include <stdexcept>

using namespace std;

/**
 * @brief A fixed-size array implementation.
 *
 * This class provides a fixed-size array with bounds checking and basic operations.
 * Designed specifically for implementing queues with fixed capacity and circular behavior.
 *
 * @tparam T Type of elements stored in the array.
 */
template <typename T>
class Array
{
private:
    T *data;          ///< Pointer to the array data.
    unsigned int cap; ///< Fixed capacity of the array.

public:
    /**
     * @brief Constructor with fixed capacity.
     * @param capacity Fixed capacity for the array.
     * @throws std::invalid_argument if capacity is 0.
     */
    explicit Array(unsigned int capacity) : cap(capacity)
    {
        if (capacity == 0)
            throw invalid_argument("Capacity must be greater than 0");

        data = new T[cap];
    }

    /**
     * @brief Constructor with capacity and default value for all elements.
     * @param capacity Fixed capacity for the array.
     * @param defaultValue Default value to initialize all elements.
     * @throws std::invalid_argument if capacity is 0.
     */
    Array(unsigned int capacity, const T &defaultValue) : cap(capacity)
    {
        if (capacity == 0)
            throw invalid_argument("Capacity must be greater than 0");

        data = new T[cap];
        for (unsigned int i = 0; i < cap; i++)
        {
            data[i] = defaultValue;
        }
    }

    /**
     * @brief Copy constructor. Creates a deep copy of another array.
     * @param other Array to copy.
     */
    Array(const Array<T> &other) : cap(other.cap)
    {
        data = new T[cap];
        for (unsigned int i = 0; i < cap; i++)
        {
            data[i] = other.data[i];
        }
    }

    /**
     * @brief Assignment operator. Assigns the contents of another array to this array.
     * @param other Array to copy.
     * @return Reference to this array.
     * @throws std::invalid_argument if arrays have different capacities.
     */
    Array<T> &operator=(const Array<T> &other)
    {
        if (this != &other)
        {
            if (cap != other.cap)
            {
                throw invalid_argument("Arrays must have the same capacity for assignment");
            }
            for (unsigned int i = 0; i < cap; i++)
            {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    /**
     * @brief Destructor. Frees the allocated memory.
     */
    ~Array()
    {
        delete[] data;
    }

    /**
     * @brief Get the fixed capacity of the array.
     * @return The capacity of the array.
     */
    unsigned int capacity() const
    {
        return cap;
    }

    /**
     * @brief Get the element at a specific index with bounds checking.
     * @param index Index of the element to retrieve.
     * @return Reference to the element at the specified index.
     * @throws std::out_of_range if the index is out of bounds.
     */
    T &at(unsigned int index)
    {
        if (index >= cap)
            throw out_of_range("Index out of range");
        return data[index];
    }

    /**
     * @brief Get the element at a specific index with bounds checking (const version).
     * @param index Index of the element to retrieve.
     * @return Const reference to the element at the specified index.
     * @throws std::out_of_range if the index is out of bounds.
     */
    const T &at(unsigned int index) const
    {
        if (index >= cap)
            throw out_of_range("Index out of range");
        return data[index];
    }

    /**
     * @brief Access an element using the subscript operator.
     * @param index Index of the element to access.
     * @return Reference to the element at the specified index.
     * @note This operator does not perform bounds checking for performance.
     */
    T &operator[](unsigned int index)
    {
        return data[index];
    }

    /**
     * @brief Access an element using the subscript operator (const version).
     * @param index Index of the element to access.
     * @return Const reference to the element at the specified index.
     * @note This operator does not perform bounds checking for performance.
     */
    const T &operator[](unsigned int index) const
    {
        return data[index];
    }

    /**
     * @brief Fill all positions of the array with a specific value.
     * @param value Value to fill the array with.
     */
    void fill(const T &value)
    {
        for (unsigned int i = 0; i < cap; i++)
        {
            data[i] = value;
        }
    }

    /**
     * @brief Check if two arrays are equal (same capacity and elements).
     * @param other Array to compare with.
     * @return true if arrays are equal, false otherwise.
     */
    bool operator==(const Array<T> &other) const
    {
        if (cap != other.cap)
            return false;

        for (unsigned int i = 0; i < cap; i++)
        {
            if (data[i] != other.data[i])
                return false;
        }
        return true;
    }

    /**
     * @brief Check if two arrays are not equal.
     * @param other Array to compare with.
     * @return true if arrays are not equal, false otherwise.
     */
    bool operator!=(const Array<T> &other) const
    {
       return !(*this == other);
    }

    /**
     * @brief Get a pointer to the underlying array data.
     * @return Pointer to the first element of the array.
     * @note Use with caution. Direct access to internal data.
     */
    T *getData()
    {
        return data;
    }

    /**
     * @brief Get a const pointer to the underlying array data.
     * @return Const pointer to the first element of the array.
     * @note Use with caution. Direct access to internal data.
     */
    const T *getData() const
    {
        return data;
    }

    /**
     * @brief Print the elements of the array.
     * @note Prints all elements regardless of whether they contain meaningful data.
     */
    void print() const
    {
        cout << "[";
        for (unsigned int i = 0; i < cap; i++)
        {
            cout << data[i];
            if (i < cap - 1)
            {
                cout << ", ";
            }
        }
        cout << "]" << endl;
    }
};

#endif // ARRAY_HH 