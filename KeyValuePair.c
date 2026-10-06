#include <stdio.h>
#include <stdlib.h>
#include "KeyValuePair.h"
#include "LinkedList.h"

// Define Pair structure
struct KeyValuePair_t {
    Element key;      // Key element
    Element value;    // Value element
    CopyFunction copyKey;
    CopyFunction copyValue;
    FreeFunction freeKey;
    FreeFunction freeValue;
    PrintFunction printKey;
    PrintFunction printValue;
    EqualFunction equal_function;
};

// Function to create a key-value pair
Pair* createKeyValuePair(Element key, Element val, FreeFunction freeKey, FreeFunction freeValue,
                         CopyFunction copyKey, CopyFunction copyValue, PrintFunction printKey,
                         PrintFunction printValue, EqualFunction equal_function) {
    if (key == NULL || val == NULL || freeKey == NULL || copyKey == NULL ||
        freeValue == NULL || copyValue == NULL || printKey == NULL || printValue == NULL) {
        return NULL;  // validate input parameters
    }

    Pair* pair = (Pair*)malloc(sizeof(Pair));
    if (pair == NULL) {
        return NULL;  // memory allocation failure
    }

    pair->key = copyKey(key);  // copy the key
    pair->value = val;  // assign value

    // Assign function pointers
    pair->copyKey = copyKey;
    pair->copyValue = copyValue;
    pair->freeKey = freeKey;
    pair->freeValue = freeValue;
    pair->printKey = printKey;
    pair->printValue = printValue;
    pair->equal_function = equal_function;

    return pair;
}

// Function to destroy a key-value pair
status destroyKeyValuePair(Pair* pair) {
    if (pair == NULL) {
        return failure;  // check if pair is NULL
    }
    if (pair->freeKey != NULL) {  // check if freeKey function is provided
        if (pair->key != NULL) {
            pair->freeKey(pair->key);  // free the key
        }
    }
    if (pair->freeValue != NULL) {  // check if freeValue function is provided
        if (pair->value != NULL) {
            pair->freeValue(pair->value);  // free the value
        }
    }
    free(pair);  // free the pair structure
    return success;
}

// Function to display key
status displayKey(Pair* pair) {
    if (pair == NULL || pair->key == NULL) {
        return failure;  // check for NULL
    }
    if (pair->printKey(pair->key) == failure) {
        return failure;  // call print function for the key
    }
    return success;
}

// Function to display value
status displayValue(Pair* pair) {
    if (pair == NULL || pair->value == NULL) {
        return failure;  // check for NULL
    }
    if (pair->printValue(pair->value) == failure) {
        return failure;
    }
    return success;
}

Element getKey(Element element) {
    if (element == NULL) {
        return NULL;  // check for NULL
    }
    Pair* ptrkey = (Pair*)element;  // cast to pair
    return ptrkey->key;  // return the key
}

Element getValue(Element element) {
    if (element == NULL) {
        return NULL;  // check for NULL
    }
    Pair* ptrval = (Pair*)element;  // cast to pair
    return ptrval->value;  // return the value
}

// Function to compare if the key is equal to the provided element
bool isEqualKey(Pair* pair, Element element) {
    if (pair == NULL || element == NULL || pair->key == NULL || pair->equal_function == NULL) {
        return false;  // check for NULL
    }
    return pair->equal_function(pair->key, element);  // compare keys
}
