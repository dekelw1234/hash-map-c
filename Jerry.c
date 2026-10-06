#include "Jerry.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//the creatPlanet function dynamically allocates memory for a new Planet structure,
//initializes its fields with the given values, and returns a pointer to the newly created Planet.
//if memory allocation fails at any point, it frees previously allocated memory and returns NULL.
Planet* creatPlanet(char* planet_name, float x, float y, float z) {
    Planet* ptr = (Planet*)malloc(sizeof(Planet));  //allocate memory for the Planet structure
    if (ptr == NULL) {  //if memory allocation fails, return NULL
        return NULL;
    }

    ptr->planet_name = (char*)malloc(strlen(planet_name) + 1);  //allocate memory for the planet's name
    if (ptr->planet_name == NULL) {  //if allocation fails, free previously allocated memory and return NULL
        free(ptr);
        return NULL;
    }
    strcpy(ptr->planet_name, planet_name);  //copy the provided planet name into the allocated memory
    ptr->x = x;  //set the planet's x-coordinate
    ptr->y = y;  //set the planet's y-coordinate
    ptr->z = z;  //set the planet's z-coordinate
    return ptr;  //return the pointer to the newly created Planet
}


//the destroyPlanet function frees the memory allocated for a Planet structure and its associated planet_name.
//if the provided Planet pointer is NULL, the function does nothing.
void destroyPlanet(Planet* ptrPlanet) {
    if (ptrPlanet == NULL) {  //if the pointer to the planet is NULL, do nothing
        return;
    }
    free(ptrPlanet->planet_name);  //free the memory allocated for the planet's name
    free(ptrPlanet);  //free the memory allocated for the Planet structure itself
}


//the createJerry function dynamically allocates memory for a new Jerry structure, initializes its fields with
//the provided values, and returns a pointer to the newly created Jerry.
//if memory allocation fails at any point, it frees previously allocated memory and returns NULL.
Jerry* createJerry(char* id, char* origin, int happinessLevel,Planet* birth_planet) {
    Jerry* ptr = (Jerry*)malloc(sizeof(Jerry));  //allocate memory for the Jerry structure
    if (ptr == NULL) {  //if memory allocation for Jerry fails, return NULL
        return NULL;
    }
    Origin* ptro = (Origin*)malloc(sizeof(Origin));
    if (ptro == NULL) {
        free(ptr);
        return NULL;  //return NULL if memory allocation fails
    }

    if (birth_planet == NULL) {
        return NULL;  //return NULL if birth_planet is NULL
    }

    ptro->origin_name = (char*)malloc(strlen(origin) + 1);
    if (ptro->origin_name != NULL) {
        strcpy(ptro->origin_name, origin);  //copy the origin name into the structure
        ptro->birth_planet = birth_planet;  //set the birth planet for the origin
    } else {
        free(ptro);
        free(ptr);  //free the memory if origin_name allocation fails
        return NULL;
    }


    ptr->id = (char*)malloc(strlen(id) + 1);  //allocate memory for the Jerry's ID
    if (ptr->id == NULL) {  //if memory allocation for the ID fails, free previously allocated memory and return NULL
        free(ptro->origin_name);
        free(ptro);
        free(ptr);
        return NULL;
    }

    strcpy(ptr->id, id);  //copy the provided ID into the allocated memory
    ptr->origin = ptro;  //set the origin of the Jerry
    ptr->happinessLevel = happinessLevel;  //set the happiness level of the Jerry
    ptr->number_of_characteristics = 0;  //initialize the number of characteristics to 0
    ptr->pointer_physical_characteristics = NULL;  //set the pointer to physical characteristics to NULL

    return ptr;  //return the pointer to the newly created Jerry
}


//the destroyJerry function frees the memory allocated for a Jerry structure, including its associated fields such as
//id, physical characteristics, and origin. If any pointer is NULL, the function does nothing for that part of the structure.
void destroyJerry(Jerry* ptr_jerry) {
    if (ptr_jerry == NULL) {  //if the pointer to Jerry is NULL, do nothing
        return;
    }

    if (ptr_jerry->id == NULL) {  //if the ID pointer is NULL, no need to free it
        return;
    }
    free(ptr_jerry->id);  //free the memory allocated for the Jerry's ID

    //loop through and free all physical characteristics associated with the Jerry
    for (int i = 0; i < ptr_jerry->number_of_characteristics; i++) {
        if (ptr_jerry->pointer_physical_characteristics[i] != NULL) {
            destroyPhysicalCharacteristics(ptr_jerry->pointer_physical_characteristics[i]);
        }
        ptr_jerry->pointer_physical_characteristics[i] = NULL;
    }

    //free the origin and the memory allocated for physical characteristics array
    if (ptr_jerry->origin!= NULL) {
        destroyOrigin(ptr_jerry->origin);
    }
    free(ptr_jerry->pointer_physical_characteristics);
    //finally, free the memory allocated for the Jerry structure itself
    free(ptr_jerry);
}


//the creatPhysicalCharacteristics function allocates memory for a new PhysicalCharacteristics structure,
//sets its fields (name and value), and returns a pointer to the newly created structure.
PhysicalCharacteristics* creatPhysicalCharacteristics(char* characteristic_name, float value) {
    PhysicalCharacteristics* ptr = (PhysicalCharacteristics*)malloc(sizeof(PhysicalCharacteristics));
    if (ptr == NULL) {
        return NULL;  //return NULL if memory allocation fails
    }

    ptr->characteristic_name = (char*)malloc(strlen(characteristic_name) + 1);
    if (ptr->characteristic_name == NULL) {
        free(ptr);  //free the previously allocated memory if characteristic_name allocation fails
        return NULL;
    }
    strcpy(ptr->characteristic_name, characteristic_name);  //copy the characteristic name into the struct
    ptr->value = value;  //set the value of the characteristic

    return ptr;  //return the newly created PhysicalCharacteristics object
}


//the addCharacteristics function adds a new PhysicalCharacteristics object to a Jerry's list of characteristics.
status addCharacteristics(Jerry* jerry, PhysicalCharacteristics* ability_name) {
    if (jerry == NULL || ability_name == NULL) {
        return failure;  //return failure if Jerry or ability_name is NULL
    }
    //reallocate memory for the array of physical characteristics to accommodate the new characteristic
    PhysicalCharacteristics** tempArry = realloc(jerry->pointer_physical_characteristics,(jerry->number_of_characteristics + 1) * sizeof(PhysicalCharacteristics*));
    if (tempArry == NULL) {
        return failure;  //return failure if realloc fails
    }

    //add the new characteristic to the array
    tempArry[jerry->number_of_characteristics] = ability_name;
    jerry->pointer_physical_characteristics = tempArry;  //update the pointer to the new array
    jerry->number_of_characteristics++;  //increment the number of characteristics

    return success;  //return success
}




//the destroyPhysicalCharacteristics function frees the memory allocated for a PhysicalCharacteristics structure,
//including its characteristic name.
void destroyPhysicalCharacteristics(PhysicalCharacteristics* ptrPhysicalCharacteristics) {
    if (ptrPhysicalCharacteristics == NULL) {
        return;  //do nothing if the pointer is NULL
    }

    free(ptrPhysicalCharacteristics->characteristic_name);  //free the memory allocated for characteristic name
    free(ptrPhysicalCharacteristics);  //free the memory allocated for the PhysicalCharacteristics structure
}


status removeCharacteristics(Jerry* jerry, char* ability_name) {
    if (jerry == NULL || ability_name == NULL || jerry->number_of_characteristics == 0) {
        return failure;  // Return failure if Jerry or ability_name is NULL, or there are no characteristics.
    }

    int indexToRemove = -1;
    for (int i = 0; i < jerry->number_of_characteristics; i++) {
        if (strcmp(jerry->pointer_physical_characteristics[i]->characteristic_name, ability_name) == 0) {
            indexToRemove = i;  // Found the characteristic to remove.
            break;
        }
    }

    if (indexToRemove == -1) {  // Characteristic not found.
        return failure;
    }

    // Destroy the removed characteristic
    destroyPhysicalCharacteristics(jerry->pointer_physical_characteristics[indexToRemove]);

    // Shift remaining characteristics to fill the gap
    for (int i = indexToRemove; i < jerry->number_of_characteristics - 1; i++) {
        jerry->pointer_physical_characteristics[i] = jerry->pointer_physical_characteristics[i + 1];
    }

    // Reallocate memory for the array, reducing the size by 1
    PhysicalCharacteristics** tempArry = (PhysicalCharacteristics**)realloc(jerry->pointer_physical_characteristics,
        (jerry->number_of_characteristics - 1) * sizeof(PhysicalCharacteristics*));

    if (tempArry == NULL && jerry->number_of_characteristics > 1) {
        return failure;  // Return failure if realloc fails and there are more than one characteristic.
    }

    jerry->pointer_physical_characteristics = tempArry;  // Update the pointer to the reallocated memory.
    jerry->number_of_characteristics--;  // Decrease the number of characteristics.

    return success;  // Return success after removing the characteristic.
}




//the is_ability_exists function checks whether a specific physical characteristic (ability_name)
//already exists for a Jerry.

bool is_ability_exists(Jerry* jerry, char* ability_name) {
    if (jerry == NULL || jerry->pointer_physical_characteristics == NULL) {
        return false;  //return false if Jerry or his characteristics are NULL
    }
    for (int i = 0; i < jerry->number_of_characteristics; i++) {
        // Compare the characteristic name with the ability_name
        if (strcmp(jerry->pointer_physical_characteristics[i]->characteristic_name, ability_name) == 0) {
            return true;  // Return true if the characteristic is found
        }
    }
    return false;  // Return false if the characteristic is not found
}



//the destroyOrigin function frees the memory allocated for an Origin structure, including its name.

void destroyOrigin(Origin* ptrOrigin) {
    if (ptrOrigin == NULL) {
        return;  //do nothing if the Origin pointer is NULL
    }
    free(ptrOrigin->origin_name);  //free the memory for the origin name
    free(ptrOrigin);  //free the memory for the Origin structure itself
}


status printPlanet(Planet* planet) {
    if (planet == NULL) {
        return failure;  //feturn failure if the planet is NULL
    }
    printf("Planet : %s (%.2f,%.2f,%.2f) \n", planet->planet_name, planet->x, planet->y, planet->z);
    return success;  //feturn success after printing planet details
}


status printOrigin(Origin* origin) {
    if (origin == NULL) {
        return failure;  //return failure if the origin is NULL
    }
    printf("Origin : %s \n", origin->origin_name);
    return success;  //return success after printing origin details
}


status printJerry(Jerry* jerry) {
    if (jerry == NULL) {
        printf("Jerry is NULL\n");
        return failure;  //print message and exit if Jerry is NULL
    }
    printf("Jerry , ID - %s : \n", jerry->id);
    printf("Happiness level : %d \n", jerry->happinessLevel);
    printOrigin(jerry->origin);  //print origin details
    printPlanet(jerry->origin->birth_planet);  //print birth planet details

    if (jerry->number_of_characteristics > 0 && jerry->pointer_physical_characteristics != NULL) {
        printf("Jerry's physical Characteristics available :\n");
        for (int i = 0; i < jerry->number_of_characteristics; i++) {
            if (jerry->pointer_physical_characteristics[i] == NULL) {
                return failure;
            }
            if (i == 0) {
                printf("\t");
            }
            printf("%s : %.2f", jerry->pointer_physical_characteristics[i]->characteristic_name, jerry->pointer_physical_characteristics[i]->value);
            if (i != jerry->number_of_characteristics - 1) {
                printf(" , ");
            } else {
                printf(" \n");
            }
        }
    }
    return success;
}




