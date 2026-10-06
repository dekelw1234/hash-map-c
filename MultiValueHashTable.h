#ifndef MULTIVALUEHASHTABLE_H
#define MULTIVALUEHASHTABLE_H
#include "HashTable.h"
#include "Defs.h"
#include "LinkedList.h"
#include "KeyValuePair.h"

/* defines the structure for a multi-value hash table */
typedef struct MultyValueHashTable_s MultiHashTable;

/*
 * creates a multi-value hash table to store keys with multiple values
 * parameters:
 * - copy, free, and print functions for keys
 * - copy, free, and print functions for linked list values
 * - equal functions for comparing keys and values
 * - a function to transform keys into numbers for hashing
 * - the number of buckets in the hash table
 * returns: pointer to the created multi-value hash table
 */
MultiHashTable* createMultiValueHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyLinkedlistvalue, FreeFunction destroyList, PrintFunction displayList, EqualFunction equalKey, EqualFunction equalValue, TransformIntoNumberFunction transformIntoNumber, int hashNumber);

/*
 * destroys a multi-value hash table and frees all associated memory
 * parameters: pointer to the multi-value hash table
 * returns: status indicating success or failure
 */
status destroyMultiValueHashTable(MultiHashTable*);

/*
 * adds a key and its associated value to the multi-value hash table
 * parameters: pointer to the hash table, key element, and value element
 * returns: status indicating success or failure
 */
status addToMultiValueHashTable(MultiHashTable*, Element, Element);

/*
 * looks up all values associated with a key in the multi-value hash table
 * parameters: pointer to the hash table and the key to search for
 * returns: a linked list of values associated with the key or null if not found
 */
Element lookupInMultiValueHashTable(MultiHashTable*, Element);

/*
 * removes a specific value associated with a key from the multi-value hash table
 * parameters: pointer to the hash table, key element, and value element
 * returns: status indicating success or failure
 */
status removeFromMultiValueHashTable(MultiHashTable*, Element, Element);

/*
 * displays all values associated with a specific key in the multi-value hash table
 * parameters: pointer to the hash table and the key to display
 * returns: status indicating success or failure
 */
status displayMultiValueHashElementsByKey(MultiHashTable*, Element);

#endif //MULTIVALUEHASHTABLE_H
