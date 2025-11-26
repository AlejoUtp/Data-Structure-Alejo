/**
 * @file hash_table.h
 * @brief Implementación de Hash Table con direccionamiento abierto (open addressing)
 * 
 * Esta implementación utiliza linear probing para resolver colisiones y
 * lazy deletion para manejar las eliminaciones de manera eficiente.
 */

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stddef.h>
#include <stdbool.h>

/**
 * @brief Estados posibles de una celda en la tabla hash
 */
typedef enum {
    EMPTY,      /**< Celda vacía, nunca usada */
    OCCUPIED,   /**< Celda ocupada con un elemento válido */
    DELETED     /**< Celda marcada como eliminada (lazy deletion) */
} CellState;

/**
 * @brief Estructura que representa una entrada en la tabla hash
 */
typedef struct {
    char *key;           /**< Clave (string) */
    void *value;         /**< Valor asociado a la clave */
    CellState state;     /**< Estado de la celda */
} HashEntry;

/**
 * @brief Estructura que representa la tabla hash
 */
typedef struct {
    HashEntry *table;    /**< Array dinámico de entradas */
    size_t capacity;     /**< Capacidad total de la tabla */
    size_t size;         /**< Número de elementos actualmente almacenados */
    size_t deleted;      /**< Número de elementos marcados como eliminados */
} HashTable;

/**
 * @brief Crea una nueva tabla hash vacía
 * 
 * Inicializa una tabla hash con una capacidad inicial predeterminada.
 * Todas las celdas se inicializan en estado EMPTY.
 * 
 * @param initial_capacity Capacidad inicial de la tabla (debe ser > 0)
 * @return Puntero a la tabla hash creada, o NULL si hay error
 * 
 * @note El usuario debe liberar la memoria con hash_table_destroy()
 */
HashTable* hash_table_create(size_t initial_capacity);

/**
 * @brief Función hash para strings
 * 
 * Calcula el índice hash para una clave dada usando el algoritmo djb2.
 * Esta función dispersa las claves uniformemente en el rango [0, capacity).
 * 
 * @param key Clave a hashear (string)
 * @param capacity Capacidad de la tabla hash
 * @return Índice hash en el rango [0, capacity)
 * 
 * @warning key no debe ser NULL
 */
size_t hash_function(const char *key, size_t capacity);

/**
 * @brief Inserta o actualiza un par clave-valor en la tabla
 * 
 * Si la clave ya existe, actualiza su valor. Si no existe, crea una nueva entrada.
 * Utiliza linear probing para manejar colisiones. Si el factor de carga
 * supera 0.7, realiza un rehashing automático.
 * 
 * @param ht Puntero a la tabla hash
 * @param key Clave a insertar (se hace copia interna)
 * @param value Valor a asociar con la clave
 * @return true si la inserción fue exitosa, false en caso de error
 * 
 * @note La función hace una copia de la clave, pero no del valor
 * @warning ht y key no deben ser NULL
 */
bool hash_table_insert(HashTable *ht, const char *key, void *value);

/**
 * @brief Busca un valor por su clave
 * 
 * Busca la clave en la tabla usando linear probing. Salta sobre celdas
 * marcadas como DELETED durante la búsqueda.
 * 
 * @param ht Puntero a la tabla hash
 * @param key Clave a buscar
 * @return Puntero al valor asociado, o NULL si no se encuentra la clave
 * 
 * @warning ht y key no deben ser NULL
 */
void* hash_table_get(const HashTable *ht, const char *key);

/**
 * @brief Elimina un elemento de la tabla (lazy deletion)
 * 
 * Marca la celda correspondiente como DELETED en lugar de eliminarla físicamente.
 * Esto permite que las búsquedas continúen correctamente con linear probing.
 * 
 * @param ht Puntero a la tabla hash
 * @param key Clave del elemento a eliminar
 * @return true si el elemento fue eliminado, false si no se encontró
 * 
 * @warning ht y key no deben ser NULL
 */
bool hash_table_delete(HashTable *ht, const char *key);

/**
 * @brief Verifica si una clave existe en la tabla
 * 
 * @param ht Puntero a la tabla hash
 * @param key Clave a verificar
 * @return true si la clave existe, false en caso contrario
 * 
 * @warning ht y key no deben ser NULL
 */
bool hash_table_contains(const HashTable *ht, const char *key);

/**
 * @brief Obtiene el número de elementos en la tabla
 * 
 * @param ht Puntero a la tabla hash
 * @return Número de elementos activos (sin contar los eliminados)
 * 
 * @warning ht no debe ser NULL
 */
size_t hash_table_size(const HashTable *ht);

/**
 * @brief Verifica si la tabla está vacía
 * 
 * @param ht Puntero a la tabla hash
 * @return true si la tabla no tiene elementos, false en caso contrario
 * 
 * @warning ht no debe ser NULL
 */
bool hash_table_is_empty(const HashTable *ht);

/**
 * @brief Calcula el factor de carga actual
 * 
 * El factor de carga es (size + deleted) / capacity, e indica qué tan llena
 * está la tabla. Un factor alto degrada el rendimiento del linear probing.
 * 
 * @param ht Puntero a la tabla hash
 * @return Factor de carga en el rango [0.0, 1.0]
 * 
 * @warning ht no debe ser NULL
 */
double hash_table_load_factor(const HashTable *ht);

/**
 * @brief Redimensiona la tabla hash (rehashing)
 * 
 * Crea una nueva tabla con mayor capacidad y reinserta todos los elementos
 * activos. Los elementos marcados como DELETED no se reinsertan. Esto
 * mejora el rendimiento cuando hay muchas colisiones o eliminaciones.
 * 
 * @param ht Puntero a la tabla hash
 * @param new_capacity Nueva capacidad (debe ser mayor que la actual)
 * @return true si el rehashing fue exitoso, false en caso de error
 * 
 * @warning ht no debe ser NULL
 * @note Esta operación es costosa O(n), se hace automáticamente cuando es necesario
 */
bool hash_table_rehash(HashTable *ht, size_t new_capacity);

/**
 * @brief Elimina todos los elementos de la tabla
 * 
 * Libera todas las claves y marca todas las celdas como EMPTY.
 * La capacidad de la tabla no cambia.
 * 
 * @param ht Puntero a la tabla hash
 * 
 * @warning ht no debe ser NULL
 * @note Los valores no se liberan automáticamente (responsabilidad del usuario)
 */
void hash_table_clear(HashTable *ht);

/**
 * @brief Destruye la tabla hash y libera toda su memoria
 * 
 * Libera todas las claves, el array de entradas y la estructura de la tabla.
 * 
 * @param ht Puntero a la tabla hash a destruir
 * 
 * @note Los valores almacenados NO se liberan automáticamente
 * @warning Después de llamar esta función, ht queda inválido
 */
void hash_table_destroy(HashTable *ht);

/**
 * @brief Imprime el contenido de la tabla (para debugging)
 * 
 * Muestra el estado de cada celda y su contenido si está ocupada.
 * Útil para visualizar colisiones y el estado interno de la tabla.
 * 
 * @param ht Puntero a la tabla hash
 * 
 * @warning ht no debe ser NULL
 */
void hash_table_print(const HashTable *ht);

#endif /* HASH_TABLE_H */