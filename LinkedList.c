#include "LinkedList.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    Element value;
    struct Node* next;
} Node;

struct Linked_list_t {
    Node* head;
    int length;
    CopyFunction copy;
    FreeFunction free_function;
    EqualFunction equal_function;
    PrintFunction print_function;
};

typedef struct Linked_list_t List;

status destroyNode(Node* node, FreeFunction free_function) {
    if (node == NULL) { // check if node is null before proceeding
        return failure;
    }
    free_function(node->value); // free the value stored in the node
    free(node); // free the node itself
    return success;
}

Node* createNode(Element element, CopyFunction copyFunc) {
    if (element == NULL) { // ensure the element is not null
        return NULL;
    }
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) { // check memory allocation success
        return NULL;
    }

    node->value = copyFunc(element); // copy the element into the node
    if (node->value == NULL) { // check if copying was successful
        free(node);
        return NULL;
    }
    node->next = NULL; // initialize the next pointer to null
    return node;
}

List* createLinkedList(CopyFunction copyFunction, FreeFunction freeFunction, EqualFunction equalFunction, PrintFunction print_function, Element element) {
    if (copyFunction == NULL || freeFunction == NULL || equalFunction == NULL) {
        printf("error: one or more function pointers are null.\n");
        return NULL;
    }
    List* list = (List*)malloc(sizeof(List));
    if (list == NULL) { // check memory allocation success
        printf("error: failed to allocate memory for list.\n");
        return NULL;
    }
    list->copy = copyFunction;
    list->free_function = freeFunction;
    list->equal_function = equalFunction;
    list->head = NULL;
    list->length = 0;
    list->print_function = print_function;

    if (element != NULL) {
        Node* node = createNode(element, copyFunction);
        if (node == NULL) { // check if node creation was successful
            printf("error: failed to create the first node.\n");
            free(list);
            return NULL;
        }
        list->head = node; // set the head to the new node
        list->length = 1;
    } else {
        list->head = NULL; // initialize an empty list
        list->length = 0;
    }

    return list;
}

status destroyList(List* list) {
    if (list == NULL) { // ensure the list is not null
        return failure;
    }
    Node* curr = list->head;
    while (curr != NULL) { // iterate through all nodes in the list
        Node* next = curr->next; // save the next node
        destroyNode(curr, list->free_function); // destroy the current node
        curr = next; // move to the next node
    }
    free(list); // free the list structure
    return success;
}

Node* findNodeByElement(List* list, Element element) {
    if (list == NULL) { // ensure the list is not null
        return NULL;
    }
    Node* curr = list->head;
    while (curr != NULL) { // iterate through the list
        if (list->equal_function(curr->value, element)) { // check if the current node matches the element
            return curr;
        }
        curr = curr->next; // move to the next node
    }
    return NULL; // return null if not found
}

status deleteNode(List* list, Element element) {
    if (list == NULL || element == NULL) { // check for null parameters
        return failure;
    }
    if (list->length == 0) { // ensure the list is not empty
        return failure;
    }
    Node* curr = list->head;
    Node* prev = NULL;

    while (curr != NULL) { // iterate through the list
        if (list->equal_function(curr->value, element) == true) { // check if the current node matches the element
            if (prev == NULL) { // handle the case where the node to delete is the head
                list->head = curr->next;
            } else {
                prev->next = curr->next; // unlink the current node
            }
            destroyNode(curr, list->free_function); // free the node
            list->length--; // decrement the list length
            return success;
        }
        prev = curr; // move prev to the current node
        curr = curr->next; // move to the next node
    }
    return failure; // element not found
}

status appendNode(List* list, Element element) {
    if (list == NULL) { // ensure the list is not null
        printf("error: list is null\n");
        return failure;
    }
    if (element == NULL) { // ensure the element is not null
        printf("error: element is null\n");
        return failure;
    }
    if (list->copy == NULL) { // ensure the copy function is set
        printf("error: copy function is null\n");
        return failure;
    }

    Node* newNode = createNode(element, list->copy);
    if (newNode == NULL) { // check if node creation was successful
        printf("error: failed to create a new node\n");
        return failure;
    }

    if (list->head == NULL) { // handle case where list is empty
        list->head = newNode;
    } else {
        Node* curr = list->head;
        while (curr->next != NULL) { // traverse to the end of the list
            curr = curr->next;
        }
        curr->next = newNode; // append the new node at the end
    }

    list->length++; // increment the list length
    return success;
}

status displayList(List* list) {
    if (list == NULL) { // ensure the list is not null
        return failure;
    }
    Node* curr = list->head;
    while (curr != NULL) { // iterate through the list
        list->print_function(curr->value); // print the value of the current node
        curr = curr->next; // move to the next node
    }
    return success;
}

int getLengthList(List* list) {
    if (list) { // ensure the list is not null
        return list->length; // return the length of the list
    }
    return 0; // return 0 if list is null
}

Element getDataByIndex(List* list, int idx) {
    if (list == NULL || idx < 1 || idx > list->length) { // check for valid index
        return NULL;
    }
    Node* curr = list->head;
    for (int i = 1; i < idx; i++) { // iterate to the specified index
        curr = curr->next;
    }
    return curr->value; // return the value at the index
}

Element searchByKeyInList(List* list, Element key) {
    if (list == NULL) { // ensure the list is not null
        return NULL;
    }

    Node* curr = list->head;
    while (curr != NULL) { // iterate through the list
        if (list->equal_function(curr->value, key) == true) { // check if the current node matches the key
            return curr->value;
        }
        curr = curr->next; // move to the next node
    }
    return NULL; // return null if key not found
}
status freefunction(Element element) {
    if (element == NULL) {
        return failure;
    }
    return success;
}


List* copylist(List* list) {
    if (list == NULL || list->head == NULL) { // check if the list is null or empty
        return NULL;
    }
    List* newlist = createLinkedList(list->copy, freefunction, list->equal_function, list->print_function, NULL);

    if (newlist == NULL) { // check if new list creation was successful
        return NULL;
    }

    Node* currnode = list->head;
    Node* newprevnode = NULL;

    while (currnode != NULL) { // iterate through the list
        Node* newnode = createNode(currnode->value, newlist->copy);
        if (newnode == NULL) { // check if node creation was successful
            destroyList(newlist); // clean up if node creation fails
            return NULL;
        }

        if (newprevnode == NULL) { // handle the first node
            newlist->head = newnode;
        } else {
            newprevnode->next = newnode; // link the new node
        }

        newprevnode = newnode; // update the previous node pointer
        currnode = currnode->next; // move to the next node
        newlist->length++; // increment the length of the new list
    }
    return newlist; // return the copied list
}
