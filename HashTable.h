#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include "Defs.h"

/* defines the structure for a hash table */
typedef struct hashTable_s *hashTable;

/*
 * creates a hash table with the specified functions and parameters
 * parameters:
 * copy, free, and print functions for keys and values
 * an equal function for comparing keys
 * a function to transform keys into numbers for hashing
 * the number of buckets in the hash table
 * returns: pointer to the created hash table
 */
hashTable createHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey, TransformIntoNumberFunction transformIntoNumber, int hashNumber);

/*
 * destroys a hash table and frees all associated memory
 * parameters: pointer to the hash table
 * returns: status indicating success or failure
 */
status destroyHashTable(hashTable);

/*
 * adds a key-value pair to the hash table
 * parameters: pointer to the hash table, key element, and value element
 * returns: status indicating success or failure
 */
status addToHashTable(hashTable, Element key, Element value);

/*
 * looks up a value in the hash table by its key
 * parameters: pointer to the hash table and the key to search for
 * returns: the value element associated with the key or null if not found
 */
Element lookupInHashTable(hashTable, Element key);

/*
 * removes a key-value pair from the hash table
 * parameters: pointer to the hash table and the key to remove
 * returns: status indicating success or failure
 */
status removeFromHashTable(hashTable, Element key);

/*
 * displays all elements in the hash table
 * parameters: pointer to the hash table
 * returns: status indicating success or failure
 */
status displayHashElements(hashTable);

#endif /* HASH_TABLE_H */
