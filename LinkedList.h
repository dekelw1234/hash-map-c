#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Defs.h"

/* defines the structure for a linked list */
typedef struct Linked_list_t List;

/*
 * creates a new linked list
 * parameters: copy function for copying elements, free function for freeing elements,
 * equal function for comparing elements, print function for displaying elements,
 * and an initial element to be added to the list
 * returns: a pointer to the created list
 */
List* createLinkedList(CopyFunction copyFunction, FreeFunction freeFunction, EqualFunction equalFunction, PrintFunction print_function, Element element);

/*
 * destroys the linked list and frees all associated memory
 * parameters: a pointer to the list
 * returns: status indicating success or failure
 */
status destroyList(List* list);

/*
 * appends a new node to the end of the list
 * parameters: a pointer to the list and the element to append
 * returns: status indicating success or failure
 */
status appendNode(List* list, Element elem);

/*
 * deletes a node from the list that matches the given element
 * parameters: a pointer to the list and the element to delete
 * returns: status indicating success or failure
 */
status deleteNode(List* list, Element element);

/*
 * displays the elements in the list
 * parameters: a pointer to the list
 * returns: status indicating success or failure
 */
status displayList(List* list);

/*
 * retrieves data from the list by index
 * parameters: a pointer to the list and the index to retrieve
 * returns: the element at the given index or null if invalid
 */
Element getDataByIndex(List* list, int idx);

/*
 * gets the length of the list
 * parameters: a pointer to the list
 * returns: the number of elements in the list
 */
int getLengthList(List* list);

/*
 * searches for an element in the list using a key
 * parameters: a pointer to the list and the key to search for
 * returns: a pointer to the found element or null if not found
 */
void* searchByKeyInList(List* list, Element key);

/*
 * creates a copy of the list
 * parameters: a pointer to the original list
 * returns: a pointer to the new copied list
 */
List* copylist(List* list);

#endif //LINKEDLIST_H
