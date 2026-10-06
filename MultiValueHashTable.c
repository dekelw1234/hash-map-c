#include "MultiValueHashTable.h"
#include "HashTable.h"
#include "LinkedList.h"
#include "Defs.h"
#include <stdio.h>
#include <stdlib.h>

struct MultyValueHashTable_s {
    hashTable hash;
    CopyFunction copyKey;
    FreeFunction freeKey;
    PrintFunction printKey;
    EqualFunction equalKey;
    EqualFunction equalvalue;
    CopyFunction copyValue;
    FreeFunction freeValue;
    PrintFunction printValue;
    TransformIntoNumberFunction transformIntoNumber;
    int hashNumber;
};

typedef struct MultyValueHashTable_s MultiHashTable;

// function to destroy the multi-value hash table
status destroyMultiValueHashTable(MultiHashTable* multi_hash_table) {
    if (multi_hash_table == NULL) {
        return failure;  // check if multi-hash table is null
    }
    if (destroyHashTable(multi_hash_table->hash) == failure) {
        return failure;  // failure to destroy hash table
    }
    free(multi_hash_table);  // free the multi-hash table memory
    return success;
}

// function to copy a list value
Element copylistval(Element element) {
    if (element == NULL) {
        return NULL;  // check if element is null
    }
    List* castllist = (List*)element;
    return castllist;  // return the cast list
}

// function to free a list value
status freelist(Element element) {
    if (element == NULL) {
        return failure;  // check if element is null
    }
    List* castllist = (List*)element;
    return destroyList(castllist);  // destroy the list
}

// function to print a list value
status printlist(Element element) {
    if (element == NULL) {
        return failure;  // check if element is null
    }
    List* castllist = (List*)element;
    return displayList(castllist);  // display the list
}

// function to create a multi-value hash table
MultiHashTable* createMultiValueHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyvalue, FreeFunction freevalue, PrintFunction printvalue, EqualFunction equalKey, EqualFunction equalValue, TransformIntoNumberFunction transformIntoNumber, int hashNumber) {

    MultiHashTable* multi_hash_table = malloc(sizeof(MultiHashTable));
    if (multi_hash_table == NULL) {
        return NULL;  // check if memory allocation failed
    }

    // create the underlying hash table
    hashTable hash = createHashTable(copyKey, freeKey, printKey, copylistval, freelist, printlist, equalKey, transformIntoNumber, hashNumber);
    if (hash == NULL) {
        destroyMultiValueHashTable(multi_hash_table);
        return NULL;  // check if hash table creation failed
    }

    // initialize multi-value hash table fields
    multi_hash_table->hashNumber = hashNumber;
    multi_hash_table->hash = hash;
    multi_hash_table->copyKey = copyKey;
    multi_hash_table->freeKey = freeKey;
    multi_hash_table->equalKey = equalKey;
    multi_hash_table->printKey = printKey;
    multi_hash_table->copyValue = copyvalue;
    multi_hash_table->printValue = printvalue;
    multi_hash_table->freeValue = freevalue;
    multi_hash_table->equalvalue = equalValue;
    multi_hash_table->transformIntoNumber = transformIntoNumber;

    return multi_hash_table;
}

// function to add a key-value pair to the multi-value hash table
status addToMultiValueHashTable(MultiHashTable* multi_hash_table, Element key, Element value) {
    if ((multi_hash_table == NULL) || (multi_hash_table->hash == NULL) || (key == NULL) || (value == NULL)) {
        return failure;  // check if any parameter is null
    }

    // check if the key already exists in the hash table
    Element is_key_in_hash = lookupInHashTable(multi_hash_table->hash, key);  // returns a list of values

    if (is_key_in_hash != NULL) {
        // if the key exists, append the value to the existing list
        if (appendNode(is_key_in_hash, value) == failure) {
            return failure;  // append failed
        }
    }

    if (is_key_in_hash == NULL) {
        // if the key doesn't exist, create a new list for values and add the key-value pair to the hash table
        List* ptrValueList = createLinkedList(multi_hash_table->copyValue, multi_hash_table->freeValue, multi_hash_table->equalvalue, multi_hash_table->printValue, value);
        if (ptrValueList == NULL) {
            return failure;  // list creation failed
        }
        // add the key-value pair to the hash table
        if (addToHashTable(multi_hash_table->hash, key, ptrValueList) == failure) {
            destroyList(ptrValueList);  // clean up created list
            return failure;  // add failed
        }
        return success;
    }
    return success;
}

// function to look up values by key in the multi-value hash table
Element lookupInMultiValueHashTable(MultiHashTable* multi_hash_table, Element key) {
    if ((multi_hash_table == NULL) || (key == NULL)) {
        return NULL;  // check if parameters are null
    }
    Element element = lookupInHashTable(multi_hash_table->hash, key);  // retrieve list by key
    if (element == NULL) {
        return NULL;  // if no values found for the key
    }
    return element;  // return the list of values
}

// function to remove a value by key from the multi-value hash table
status removeFromMultiValueHashTable(MultiHashTable* multi_hash_table, Element key, Element value) {
    if ((multi_hash_table == NULL) || (key == NULL)) {
        return failure;  // check if any parameter is null
    }
    Element list = lookupInHashTable(multi_hash_table->hash, key);  // retrieve the list by key
    if (list == NULL) {
        return failure;  // no list found for the key
    }

    // remove the value from the list
    if (deleteNode(list, value) == failure) {
        return failure;  // deletion failed
    }
    // if the list becomes empty, remove the key from the hash table
    if (getLengthList(list) == 0) {
        if (removeFromHashTable(multi_hash_table->hash, key) == failure) {
            return failure;  // removal from hash table failed
        }
    }
    return success;
}

// function to display values by key in the multi-value hash table
status displayMultiValueHashElementsByKey(MultiHashTable* multi_hash_table, Element key) {
    if ((multi_hash_table == NULL) || (key == NULL)) {
        return failure;  // check if parameters are null
    }
    // print the list of values for the key
    if (printlist(lookupInMultiValueHashTable(multi_hash_table, key)) == failure) {
        return failure;  // print failed
    }
    return success;
}