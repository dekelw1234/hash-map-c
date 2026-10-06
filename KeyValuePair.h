#ifndef KEYVALUEPAIR_H
#define KEYVALUEPAIR_H
#include "Defs.h"

/* defines the structure for a key-value pair */
typedef struct KeyValuePair_t Pair;

/* defines a generic type for elements */
typedef void* Element;

/*
 * creates a key-value pair with the specified elements and functions
 * parameters: key and value elements, free functions for key and value,
 * copy functions for key and value, print functions for key and value,
 * and an equal function for comparing keys
 * returns: pointer to the created key-value pair
 */
Pair* createKeyValuePair(Element key, Element val, FreeFunction freeKey, FreeFunction freeValue, CopyFunction copyKey, CopyFunction copyValue, PrintFunction printValue, PrintFunction printKey, EqualFunction equal_function);

/*
 * destroys a key-value pair and frees all associated memory
 * parameters: pointer to the key-value pair
 * returns: status indicating success or failure
 */
status destroyKeyValuePair(Pair* pair);

/*
 * displays the value stored in the key-value pair
 * parameters: pointer to the key-value pair
 * returns: status indicating success or failure
 */
status displayValue(Pair* pair);

/*
 * displays the key stored in the key-value pair
 * parameters: pointer to the key-value pair
 * returns: status indicating success or failure
 */
status displayKey(Pair* pair);

/*
 * retrieves the value from the key-value pair
 * parameters: pointer to the key-value pair
 * returns: the value element
 */
Element getValue(Element pair);

/*
 * retrieves the key from the key-value pair
 * parameters: pointer to the key-value pair
 * returns: the key element
 */
Element getKey(Element pair);

/*
 * checks if the key in the key-value pair matches the given key
 * parameters: pointer to the key-value pair and the key to compare
 * returns: true if the keys are equal, false otherwise
 */
bool isEqualKey(Pair* pair, Element key);

#endif //KEYVALUEPAIR_H
