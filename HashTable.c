#include "HashTable.h"
#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "KeyValuePair.h"

struct hashTable_s{
    CopyFunction copyKey;
    FreeFunction freeKey;
    PrintFunction printKey;

    EqualFunction equalKey;
    TransformIntoNumberFunction transformIntoNumber;
    int tableSize;
    CopyFunction copyValue;
    FreeFunction freeValue;
    PrintFunction printValue;
    List** dict;
};

// Function to create a hash table
hashTable createHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey, TransformIntoNumberFunction transformIntoNumber, int hashNumber) {
    if ((copyKey == NULL) || (freeKey == NULL) || (printKey == NULL) || (copyValue == NULL) || (freeValue == NULL) || (printValue == NULL) || (equalKey == NULL) || (transformIntoNumber == NULL) || (hashNumber == 0) || (hashNumber < 0)) {
        return NULL;  // validate input parameters
    }
    hashTable hash = malloc(sizeof(struct hashTable_s));
    if (hash == NULL) {
        return NULL;  // memory allocation failure
    }

    List** dict = malloc(sizeof(List*) * hashNumber);  // allocate space for the hash table's dictionary
    if (dict == NULL) {
        free(hash);
        return NULL;  // memory allocation failure
    }
    hash->tableSize = hashNumber;

    for (int i = 0; i < hash->tableSize; i++) {
        dict[i] = NULL;  // initialize the dictionary to NULL
    }

    hash->copyKey = copyKey;
    hash->freeKey = freeKey;
    hash->printKey = printKey;
    hash->copyValue = copyValue;
    hash->freeValue = freeValue;
    hash->printValue = printValue;
    hash->equalKey = equalKey;
    hash->transformIntoNumber = transformIntoNumber;
    hash->dict = dict;
    return hash;
}

// Function to destroy the hash table
status destroyHashTable(hashTable hash) {
    if (hash == NULL) {
        return failure;  // check if hash table is NULL
    }
    for (int i = 0; i < hash->tableSize; i++) {
        if (hash->dict[i] != NULL) {
            destroyList(hash->dict[i]);  // destroy linked list at this index
        }
    }
    free(hash->dict);  // free the dictionary array
    free(hash);  // free the hash table itself
    return success;
}

// Function to copy a pair element
Element copypair(Element element) {
    if (element == NULL) {
        return NULL;  // check if element is NULL
    }
    Pair* castPair = (Pair*)element;
    return castPair;  // return the cast pair
}

// Function to print a pair element
status printpair(Element element) {
    if (element == NULL) {
        return failure;  // check if element is NULL
    }
    Pair* castPair = (Pair*)element;
    if (displayKey(castPair) == failure) {
        return failure;  // print the key
    }
    if (displayValue(castPair) == failure) {
        return failure;  // print the value
    }
    return success;
}

// Function to destroy a pair element
status destroyPair(Element element) {
    if (element == NULL) {
        return failure;  // check if element is NULL
    }
    Pair* castPair = (Pair*)element;
    if ((destroyKeyValuePair(castPair) == failure)) {
        return failure;  // destroy the key-value pair
    }
    return success;
}

// Function to compare two pair elements
bool paircomper(Element element1, Element element2) {
    if (element1 == NULL || element2 == NULL) {
        return false;  // check if elements are NULL
    }
    Pair* castPair = (Pair*)element1;
    if (isEqualKey(castPair, element2) == true) {
        return true;  // check if keys are equal
    }
    return false;
}

// Function to add a key-value pair to the hash table
status addToHashTable(hashTable hash, Element key, Element value) {
    if ((hash == NULL) || (key == NULL) || (value == NULL)) {
        return failure;  // check for NULL parameters
    }

    Pair* pairptr = createKeyValuePair(key, value, hash->freeKey, hash->freeValue, hash->copyKey, hash->copyValue, hash->printValue, hash->printKey, hash->equalKey);

    if (!pairptr) {
        return failure;  // check if pair creation failed
    }

    int idx = hash->transformIntoNumber(getKey(pairptr)) % hash->tableSize;  // get the index in the hash table

    if (hash->dict[idx] == NULL) {
        List* list = createLinkedList(copypair, destroyPair, paircomper, printpair, pairptr);
        if (!list) {
            destroyKeyValuePair(pairptr);
            return failure;  // create linked list failure
        }
        hash->dict[idx] = list;  // assign the new list to the table
        return success;
    }

    Pair* is_exists = searchByKeyInList(hash->dict[idx], getKey(pairptr));  // check if key exists

    if (is_exists) {
        destroyKeyValuePair(pairptr);
        return failure;  // key already exists
    }

    if (appendNode(hash->dict[idx], pairptr) == failure) {
        destroyKeyValuePair(pairptr);
        return failure;  // append to list failed
    }

    return success;
}

// Function to look up a key in the hash table
Element lookupInHashTable(hashTable hash, Element key) {
    if ((hash == NULL) || (key == NULL)) {
        return NULL;  // check for NULL parameters
    }

    int idx = hash->transformIntoNumber(key) % hash->tableSize;  // get the index for the key

    if (idx < 0) {
        return NULL;  // invalid index
    }

    Pair* pair = searchByKeyInList(hash->dict[idx], key);  // search for the pair in the list

    if (pair == NULL) {
        return NULL;  // pair not found
    }

    Element element = getValue(pair);  // get the value from the pair
    if (element == NULL) {
        return NULL;  // value is NULL
    }

    return element;
}

// Function to remove a key from the hash table
status removeFromHashTable(hashTable hash, Element key) {
    if ((hash == NULL) || (key == NULL)) {
        return failure;  // check for NULL parameters
    }
    int idx = hash->transformIntoNumber(key) % hash->tableSize;  // get the index for the key

    if (deleteNode(hash->dict[idx], key) == success) {
        if (getLengthList(hash->dict[idx]) == 0) {
            destroyList(hash->dict[idx]);
            hash->dict[idx] = NULL;  // clean up empty list
        }
        return success;
    }
    return failure;  // deletion failed
}

// Function to display all elements in the hash table
status displayHashElements(hashTable hash) {
    if (hash == NULL) {
        return failure;  // check if hash table is NULL
    }
    for (int i = 0; i < hash->tableSize; i++) {
        for (int j = 0; j < getLengthList(hash->dict[i]); j++) {
            printpair(getDataByIndex(hash->dict[i], j));  // print each element in the list
        }
    }
    return success;
}
