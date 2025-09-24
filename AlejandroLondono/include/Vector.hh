#ifndef VECTOR_HH
#define VECTOR_HH

#include <iostream>
#include <stdexcept>

template <typename T>
class Vector
{
private:
    // Stores the elements of the vector
    T *storage;
    // Current number of elements in the vector
    unsigned int sz;
    // Maximum number of elements that storage can hold
    unsigned int cap;
    // Policy for resizing the vector
    double policy;

public:
    // --- Constructores ---------------------------------------

    // Constructor por defecto
    Vector()
    {
        storage = new T[5];
        sz = 0;
        cap = 5;
        policy = 1.5;
    }

    // Constructor con capacidad inicial y factor de crecimiento opcional
    Vector(unsigned int c, double p = 1.5)
    {
        storage = new T[c];
        sz = 0;
        cap = c;
        policy = p;
    }

    // Constructor copia
    Vector(const Vector<T> &other)
    {
        sz = other.size();
        cap = other.cap;
        policy = other.policy;
        storage = new T[cap];
        for (unsigned int i = 0; i < sz; i++)
        {
            storage[i] = other.storage[i];
        }
    }

    // Constructor por lista de inicialización
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

    // --- Operador de asignación ---------------------
    Vector<T> &operator=(const Vector<T> &other)
    {
        if (this != &other)
        {
            delete[] storage;
            sz = other.sz;
            cap = other.cap; // Para LAVector
            storage = new T[cap];
            for (unsigned int i = 0; i < sz; i++)
            {
                storage[i] = other.storage[i];
            }
        }
        return *this;
    }

    // Destructor
    ~Vector() { delete[] storage; }

    // --- Métodos de acceso (getters) ---------------------------------------

    unsigned int size() const { return sz; }
    unsigned int getCapacity() const { return cap; }
    double getPolicy() const { return policy; }

    // --- Métodos de modificación ---------------------------------------

    void push_back(const Vector<T> &other)
    {
        reserve(sz + other.size());
        for (unsigned int i = 0; i < other.size(); i++)
        {
            push_back(other.storage[i]);
        }
    }

    void push_back(const T &elem)
    {
        if (sz == cap)
        {
            resize();
        }
        storage[sz] = elem;
        sz++;
    }

    void pop_back()
    {
        if (sz > 0)
            sz--;
    }

    void shrink_to_fit()
    {
        if (sz < cap)
        {
            T *new_storage = new T[sz];
            for (unsigned int i = 0; i < sz; i++)
            {
                new_storage[i] = storage[i];
            }
            delete[] storage;
            storage = new_storage;
            cap = sz;
        }
    }
    // --- Acceso por índice ---------------------------------------

    // Permite modificar el elemento
    T &operator[](unsigned int index)
    {
        return storage[index];
    }

    // Solo lectura cuando el Vector es const
    const T &operator[](unsigned int index) const
    {
        return storage[index];
    }

    T &at(unsigned int index)
    {
        if (index >= sz)
        {
            throw out_of_range("Index out of range");
        }
        return storage[index];
    }

    const T &at(unsigned int index) const
    {
        if (index >= sz)
        {
            throw out_of_range("Index out of range");
        }
        return storage[index];
    }

private:
    void resize()
    {
        cap *= policy;
        T *new_storage = new T[cap];
        for (unsigned int i = 0; i < sz; i++)
        {
            new_storage[i] = storage[i];
        }
        delete[] storage;
        storage = new_storage;
    }

    void reserve(unsigned int new_capacity)
    {
        if (new_capacity > cap)
        {
            cap = new_capacity;
            T *new_storage = new T[cap];
            for (unsigned int i = 0; i < sz; i++)
            {
                new_storage[i] = storage[i];
            }
            delete[] storage;
            storage = new_storage;
        }
    }
};

#endif // !VECTOR_HH