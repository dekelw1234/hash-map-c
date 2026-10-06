#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "MultiValueHashTable.h"
#include "HashTable.h"
#include "Jerry.h"
#include <string.h>
#include "Defs.h"


//converts the input string to uppercase
char* strupr(char* str) {
    //check if the input string is NULL
    if (str == NULL) {
        return NULL;  //return NULL if the input string is NULL
    }
    //pointer to iterate over each character in the string
    char* ptr = str;
    //iterate through each character of the string
    while (*ptr) {
        //convert the current character to uppercase
        *ptr = toupper((unsigned char)*ptr);
        ptr++;  // move to the next character
    }
    return str;  //return the string after conversion
}


// Helper function to check if a number is prime
bool isPrime(int num) {
    if (num <= 1) return false; // 0 and 1 are not prime numbers
    if (num <= 3) return true; // 2 and 3 are prime
    if (num % 2 == 0 || num % 3 == 0) return false; // divisible by 2 or 3

    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return false;
    }
    return true;
}

// Function to find the closest prime number
int findClosestPrime(int num) {
    if (isPrime(num)) return num; // If the number is already prime, return it

    int lower = num - 1; // Start checking below the number
    int upper = num + 1; // Start checking above the number

    while (true) {
        if (lower > 1 && isPrime(lower)) return lower; // Check downward
        if (isPrime(upper)) return upper;             // Check upward
        lower--;
        upper++;
    }
}

// Function to calculate the number of digits in a number without using log10
int countDigits(int num) {
    if (num == 0) return 1; // Special case for 0
    int count = 0;
    num = abs(num); // Handle negative numbers
    while (num > 0) {
        num /= 10; // Remove the last digit
        count++;   // Increment the digit count
    }
    return count;
}
int convertStringToAsciiInt(Element element) {
    if (element == NULL) {  // Check if the element is NULL
        return 0;  // If the element is NULL, return 0
    }
    char* str = (char*)element;  // Cast element to a string
    int ascinum = 0;  // Initialize the sum of ASCII values
    // Loop through each character of the string
    for (int i = 0; i < strlen(str); i++) {
        ascinum += (int)str[i];  // Add the ASCII value of the current character
    }
    return ascinum;  // Return the sum of ASCII values
}
TransformIntoNumberFunction ConvToInt = convertStringToAsciiInt;


status printkeyinhash(Element key) {
    char* castStrKey = (char*)key;  // Cast the element to a string
    printf("%s ", castStrKey);  // Print the string key
    return success;  // Return success after printing
}

bool comperJerry(Element element1, Element element2) {
    if ((element1 == NULL) || (element2 == NULL)) {  // Check if either element is NULL
        return false;  // If either is NULL, return false
    }
    Jerry* ptrjerry1 = element1;  // Cast element1 to a Jerry pointer
    Jerry* ptrjerry2 = element2;  // Cast element2 to a Jerry pointer

    if (ptrjerry1->id != NULL && ptrjerry2->id != NULL) {  // Check if both Jerry IDs are not NULL
        if (strcmp(ptrjerry1->id, ptrjerry2->id) == 0) {  // Compare the IDs
            return true;  // Return true if IDs are equal
        }
    }
    return false;  // Return false if IDs are not equal
}


Element copyjerry(Element element) {
    if (element == NULL) {  // Check if the element is NULL
        return NULL;  // Return NULL if the element is NULL
    }
    return element;  // Return the same element (shallow copy)
}

Element deepcopystrKey(Element str) {
    if (str == NULL) {  // Check if the element is NULL
        return NULL;  // Return NULL if the element is NULL
    }
    char* catstr = (char*)str;  // Cast element to a string
    catstr = malloc(strlen(str) + 1);  // Allocate memory for the new string
    if (catstr == NULL) {  // Check if memory allocation failed
        return NULL;  // Return NULL if allocation failed
    }
    strcpy(catstr, str);  // Copy the string into the newly allocated memory
    return catstr;  // Return the deep copied string
}


bool comperstrKey(Element element1, Element element) {
    if (element1 == NULL || element == NULL) {  // Check if either element is NULL
        return false;  // Return false if any of the elements is NULL
    }
    char* castpc = element;  // Cast element to a string
    char* pcid = element1;  // Cast the first element to a string

    if (strcmp(pcid, castpc) == 0) {  // Compare the two strings
        return true;  // Return true if they are equal
    }
    return false;  // Return false if the strings are not equal
}

status fakefree(Element element) {
    if (element == NULL) {  // Check if the element is NULL
        return failure;  // Return failure if the element is NULL
    }
    return success;  // Return success as no real memory freeing is performed
}

status freestr(Element element) {
    if (element == NULL) {  // Check if the element is NULL
        return failure;  // Return failure if the element is NULL
    }
    char* castchar = element;  // Cast element to a string
    free(castchar);  // Free the memory occupied by the string
    return success;  // Return success after freeing the memory
}

status freejerry(Element element) {
    if (element == NULL) {  // Check if the element is NULL
        return failure;  // Return failure if the element is NULL
    }
    Jerry* ptrjerry = element;  // Cast element to a Jerry pointer
    destroyJerry(ptrjerry);  // Destroy the Jerry object
    return success;  // Return success after freeing the Jerry
}
status displayjerry(Element element) {
    if (element == NULL) {  // Check if the element is NULL
        return failure;  // Return failure if the element is NULL
    }
    Jerry* ptrjerry = element;  // Cast element to a Jerry pointer
    if (printJerry(ptrjerry) == failure) {  // Print the Jerry's information
        return failure;  // Return failure if printing fails
    }
    return success;  // Return success after displaying the Jerry
}


//searches for a planet in the array by name and returns a pointer to the planet if found, or NULL if not found.
Planet* findPlanetByName(Planet* planetArry[], const char* name, const int planetCount) {
    //loop for all planets in the array
    for (int i = 0; i < planetCount; i++) {
        //compare the name of the planet with the input name
        if (strcmp(planetArry[i]->planet_name, name) == 0) {
            //return the planet if a match is found
            return planetArry[i];
        }
    }
    return NULL;
}

Jerry* findJerryById(hashTable* jerryHash, char* jerryid) {
    if (jerryid == NULL) {  // Check if the provided ID is NULL
        return NULL;  // Return NULL if the ID is invalid
    }

    Jerry* jerryptr = lookupInHashTable(*jerryHash, jerryid);  // Search for the Jerry in the hash table using the ID
    return jerryptr;  // Return the found Jerry pointer (NULL if not found)
}



status addNewJerryToMain(const int numberOfPlanets, int* numberOfJerries, List** jerryArry, Planet* planetArry[], hashTable* jerryHash) {
    char jerryid[300];
    char planetname[300];
    char originName[300];
    int happinesLevel;

    printf("What is your Jerry's ID ? \n");
    scanf("%s", jerryid);
    if (findJerryById(jerryHash, jerryid) != NULL) {  // Check if Jerry ID already exists
        printf("Rick did you forgot ? you already left him here ! \n");
        return success;  // Return success even though no new Jerry is added
    }

    printf("What planet is your Jerry from ? \n");
    scanf("%s", planetname);

    Planet* ptr_planet = findPlanetByName(planetArry, planetname, numberOfPlanets);  // Find planet by name
    if (ptr_planet == NULL || numberOfPlanets == 0) {  // Check if planet is found or no planets available
        printf("%s is not a known planet ! \n", planetname);
        return success;  // Return success but no valid planet found
    }

    printf("What is your Jerry's dimension ? \n");
    scanf("%s", originName);
    printf("How happy is your Jerry now ? \n");
    scanf("%d", &happinesLevel);

    Jerry* ptrjerry = createJerry(jerryid, originName, happinesLevel, ptr_planet);  // Create a new Jerry
    if (ptrjerry == NULL) {  // Check if Jerry creation failed
        return failure;  // Return failure if Jerry could not be created
    }

    appendNode(*jerryArry, ptrjerry);  // Add the new Jerry to the linked list
    printJerry(getDataByIndex(*jerryArry, (*numberOfJerries) + 1));  // Print details of the new Jerry
    addToHashTable(*jerryHash, jerryid, ptrjerry);  // Add Jerry to the hash table
    *numberOfJerries = *numberOfJerries + 1;  // Increment the count of Jerries

    return success;
}

status addPcToJerry(hashTable* jerryHash, MultiHashTable** CpMultiHash) {
    char jerryid[300], physicalcharacteristic[300];
    float value;

    printf("What is your Jerry's ID ? \n");
    scanf("%s", jerryid);
    Jerry* ptrjerry = findJerryById(jerryHash, jerryid);  // Find the Jerry by ID
    if (ptrjerry == NULL) {  // Check if Jerry exists
        printf("Rick this Jerry is not in the daycare ! \n");
        return success;
    }

    printf("What physical characteristic can you add to Jerry - %s ? \n", jerryid);
    scanf("%s", physicalcharacteristic);
    if (is_ability_exists(ptrjerry, physicalcharacteristic) == true) {  // Check if characteristic already exists
        printf("The information about his %s already available to the daycare ! \n", physicalcharacteristic);
        return success;
    }

    printf("What is the value of his %s ? \n", physicalcharacteristic);
    scanf("%f", &value);

    PhysicalCharacteristics* ptr_physical_characteristics = creatPhysicalCharacteristics(physicalcharacteristic, value);  // Create new characteristic
    if (ptr_physical_characteristics == NULL) {  // Check if memory allocation fails
        printf("A memory problem has been detected in the program \n");
        return failure;
    }

    if (addCharacteristics(ptrjerry, ptr_physical_characteristics) == failure) {  // Add characteristic to Jerry
        printf("A memory problem has been detected in the program \n");
        return failure;
    }

    if (addToMultiValueHashTable(*CpMultiHash, ptr_physical_characteristics->characteristic_name, ptrjerry) == failure) {  // Add to multi-hash table
        return failure;
    }

    printf("%s: \n", physicalcharacteristic);
    displayMultiValueHashElementsByKey(*CpMultiHash, ptr_physical_characteristics->characteristic_name);  // Display the updated characteristics
    return success;
}



status removePcFromJerry(hashTable* jerryHash, MultiHashTable** CpMultiHash) {
    char jerryid[300], physicalcharacteristic[300];

    printf("What is your Jerry's ID ? \n");
    scanf("%s", jerryid);
    Jerry* ptrjerry = findJerryById(jerryHash, jerryid);  // Find the Jerry by ID
    if (ptrjerry == NULL) {  // Check if Jerry exists
        printf("Rick this Jerry is not in the daycare ! \n");
        return success;
    }

    printf("What physical characteristic do you want to remove from Jerry - %s ? \n", jerryid);
    scanf("%s", physicalcharacteristic);
    if (is_ability_exists(ptrjerry, physicalcharacteristic)) {  // Check if the characteristic exists
        if (removeCharacteristics(ptrjerry, physicalcharacteristic) == failure) {  // Remove the characteristic from Jerry
            printf("A memory problem has been detected in the program \n");
            return failure;
        }
        printJerry(ptrjerry);  // Print updated Jerry details
    } else {
        printf("The information about his %s not available to the daycare ! \n", physicalcharacteristic);  // Characteristic doesn't exist
        return success;
    }

    if (removeFromMultiValueHashTable(*CpMultiHash, physicalcharacteristic, ptrjerry) == failure) {  // Remove from multi-hash table
        return failure;
    }

    return success;
}


status removeJerryFromMain(hashTable* jerryHash, MultiHashTable** CpMultiHash, int* numberOfJerries, List** jerryArry) {
    char jerryid[300];
    printf("What is your Jerry's ID ? \n");
    scanf("%s", jerryid);
    Jerry* ptrjerry = findJerryById(jerryHash, jerryid);  // Find the Jerry by ID
    if (ptrjerry == NULL) {  // Check if Jerry exists in the hash table
        printf("Rick this Jerry is not in the daycare ! \n");
        return success;  // Return success even though no removal occurs
    }

    // Loop through the Jerry's characteristics and remove them from the multi-hash table
    for (int i = 0; i < ptrjerry->number_of_characteristics; i++) {
        removeFromMultiValueHashTable(*CpMultiHash, ptrjerry->pointer_physical_characteristics[i]->characteristic_name, ptrjerry);
    }

    if (removeFromHashTable(*jerryHash, jerryid) == failure) {  // Remove Jerry from the hash table
        return failure;  // Return failure if removal from the hash table fails
    }

    if (deleteNode(*jerryArry, ptrjerry) == failure) {  // Remove Jerry from the linked list
        return failure;  // Return failure if removal from the linked list fails
    }

    *numberOfJerries = *numberOfJerries - 1;  // Update the number of Jerries
    printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
    return success;
}


status similarjerry(hashTable* jerryHash, MultiHashTable** CpMultiHash, int* numberOfJerries, List** jerryArry) {
    char physicalcharacteristic[300];
    float value;
    printf("What do you remember about your Jerry ? \n");
    scanf("%s", physicalcharacteristic);

    List* listwithcp = lookupInMultiValueHashTable(*CpMultiHash, physicalcharacteristic);  // Lookup characteristics in the multi-hash table
    if (listwithcp == NULL) {  // If no Jerries have the characteristic
        printf("Rick we can not help you - we do not know any Jerry's %s ! \n", physicalcharacteristic);
        return success;  // Return success even though no Jerry was found
    }

    printf("What do you remember about the value of his %s ? \n", physicalcharacteristic);
    scanf("%f", &value);

    List* ptrcopylist = copylist(listwithcp);  // Create a copy of the list with matching characteristics
    if (ptrcopylist == NULL) {  // Check if list copy fails
        return failure;
    }

    Jerry* selectedJerry = getDataByIndex(listwithcp, 1);  // Initialize selected Jerry as the first one in the list
    // Loop through the list of Jerries to find the most similar Jerry
    for (int j = 1; j < getLengthList(listwithcp) + 1; j++) {
        Jerry* ptrjerry = getDataByIndex(ptrcopylist, 1);
        for (int i = 0; i < ptrjerry->number_of_characteristics; i++) {
            if (strcmp(ptrjerry->pointer_physical_characteristics[i]->characteristic_name, physicalcharacteristic) == 0) {
                float cuursum = fabsf(ptrjerry->pointer_physical_characteristics[i]->value - value);  // Compare the characteristics' values
                if (fabsf(selectedJerry->pointer_physical_characteristics[i]->value - value) > cuursum) {  // Check if the current Jerry is more similar
                    selectedJerry = ptrjerry;  // Update selectedJerry
                }
                break;
            }
        }
        deleteNode(ptrcopylist, ptrjerry);  // Remove the current Jerry from the list after checking
    }

    printf("Rick this is the most suitable Jerry we found : \n");
    printJerry(selectedJerry);  // Print details of the selected Jerry
    destroyList(ptrcopylist);  // Destroy the temporary list

    // Remove the selected Jerry's characteristics from the multi-hash table
    for (int i = 0; i < selectedJerry->number_of_characteristics; i++) {
        removeFromMultiValueHashTable(*CpMultiHash, selectedJerry->pointer_physical_characteristics[i]->characteristic_name, selectedJerry);
    }

    if (removeFromHashTable(*jerryHash, selectedJerry->id) == failure) {  // Remove the Jerry from the hash table
        return failure;
    }

    if (deleteNode(*jerryArry, selectedJerry) == failure) {  // Remove the Jerry from the linked list
        return failure;
    }

    *numberOfJerries = *numberOfJerries - 1;  // Update the number of Jerries
    printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
    return success;
}

status saddestJerry(hashTable* jerryHash, MultiHashTable** CpMultiHash, int* numberOfJerries, List** jerryArry) {
    if (*numberOfJerries == 0) {  // Check if there are any Jerries in the daycare
        printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
        return success;  // Return success but no action is taken since there are no Jerries
    }

    List* ptrcopylist = copylist(*jerryArry);  // Create a copy of the list of Jerries
    if (ptrcopylist == NULL) {  // Check if the list copy fails
        return failure;
    }

    Jerry* selectedJerry = getDataByIndex(*jerryArry, 1);  // Initialize selected Jerry as the first one in the list
    // Loop through the list of Jerries to find the saddest Jerry
    for (int j = 1; j < getLengthList(*jerryArry) + 1; j++) {
        Jerry* ptrjerry = getDataByIndex(ptrcopylist, 1);
        if (selectedJerry->happinessLevel > ptrjerry->happinessLevel) {  // Check if the current Jerry has a lower happiness level
            selectedJerry = ptrjerry;  // Update selectedJerry
        }
        deleteNode(ptrcopylist, ptrjerry);  // Remove the current Jerry from the list after checking
    }

    printf("Rick this is the most suitable Jerry we found : \n");
    printJerry(selectedJerry);  // Print details of the selected Jerry
    destroyList(ptrcopylist);  // Destroy the temporary list

    // Remove the selected Jerry's characteristics from the multi-hash table
    for (int i = 0; i < selectedJerry->number_of_characteristics; i++) {
        removeFromMultiValueHashTable(*CpMultiHash, selectedJerry->pointer_physical_characteristics[i]->characteristic_name, selectedJerry);
    }

    if (removeFromHashTable(*jerryHash, selectedJerry->id) == failure) {  // Remove the Jerry from the hash table
        return failure;
    }

    if (deleteNode(*jerryArry, selectedJerry) == failure) {  // Remove the Jerry from the linked list
        return failure;
    }

    *numberOfJerries = *numberOfJerries - 1;  // Update the number of Jerries
    printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
    return success;
}

void minimain7() {

    printf("What information do you want to know ? \n");
    printf("1 : All Jerries \n");
    printf("2 : All Jerries by physical characteristics \n");
    printf("3 : All known planets \n");

}


status showWhatYouGot(const int numberOfPlanets, int* numberOfJerries, List** jerryArry, Planet* planetArry[], MultiHashTable** cpMultihash) {
    int choice = 0;
    do {
        minimain7();  // Display the menu options.

        // Read the user input and handle invalid input.
        if (scanf("%d", &choice) != 1) {
            printf("Rick this option is not known to the daycare ! \n");
            while (getchar() != '\n');  // Clear the input buffer.
            choice = -1;  // Reset choice to avoid exiting the loop.
            return failure;
        }

        // Check for leftover input (characters after a valid integer).
        char leftover;
        if (scanf("%c", &leftover) == 1 && leftover != '\n') {
            printf("Rick this option is not known to the daycare ! \n");
            while (getchar() != '\n');  // Clear the input buffer.
            choice = -1;  // Reset choice to avoid exiting the loop.
            return failure;
        }

        // Ensure the choice is within the valid range.
        if (choice < 1 || choice > 3) {
            printf("Rick this option is not known to the daycare ! \n");
            return failure;
        }

        // Handle the user choice.
        switch (choice) {
            case 1:
                if (*numberOfJerries == 0) {
                    printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
                    return failure;
                }
                displayList(*jerryArry);  // Display all Jerries.
                return success;

            case 2:
                // Ask for a physical characteristic and display matching Jerries.
                char physicalcharacteristic[300];
                printf("What physical characteristics ? \n");
                scanf("%s", physicalcharacteristic);
                if (lookupInMultiValueHashTable(*cpMultihash, physicalcharacteristic) == false) {
                    printf("Rick we can not help you - we do not know any Jerry's %s ! \n", physicalcharacteristic);
                    return failure;
                }
                printf("%s : \n", physicalcharacteristic);
                if (displayMultiValueHashElementsByKey(*cpMultihash, physicalcharacteristic) == failure) {
                    return failure;
                }
                return success;

            case 3:
                // Display the list of known planets.
                for (int i = 0; i < numberOfPlanets; i++) {
                    printPlanet(planetArry[i]);
                }
                return success;

            default:
                break;
        }
    } while (1);
}

void minimain8() {

    printf("What activity do you want the Jerries to partake in ? \n");
    printf("1 : Interact with fake Beth \n");
    printf("2 : Play golf \n");
    printf("3 : Adjust the picture settings on the TV \n");

}

status letsJerryPlay(int* numberOfJerries, List** jerryArry) {
    int choice = 0;
    if (*numberOfJerries == 0) {
        printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
        return failure;
    }
    do {
        minimain8();  // Display the menu options for activities.

        // Read the user input and handle invalid input.
        if (scanf("%d", &choice) != 1) {
            printf("Rick this option is not known to the daycare ! \n");
            while (getchar() != '\n');  // Clear the input buffer.
            choice = -1;  // Reset choice to avoid exiting the loop.
            return failure;
        }

        // Check for leftover input (characters after a valid integer).
        char leftover;
        if (scanf("%c", &leftover) == 1 && leftover != '\n') {
            printf("Rick this option is not known to the daycare ! \n");
            while (getchar() != '\n');  // Clear the input buffer.
            choice = -1;  // Reset choice to avoid exiting the loop.
            return failure;
        }

        // Ensure the choice is within the valid range.
        if (choice < 1 || choice > 3) {
            printf("Rick this option is not known to the daycare ! \n");
            return failure;
        }

        // Handle the user choice.
        switch (choice) {
            case 1:
                // Modify the happiness levels based on the activity.
                for (int j = 1; j < getLengthList(*jerryArry) + 1; j++) {
                    Jerry* ptrJerry = getDataByIndex(*jerryArry, j);
                    if (ptrJerry->happinessLevel >= 20) {
                        ptrJerry->happinessLevel += 15;
                        if (ptrJerry->happinessLevel > 100) {
                            ptrJerry->happinessLevel = 100;
                        }
                    }
                    if (ptrJerry->happinessLevel < 20) {
                        ptrJerry->happinessLevel -= 5;
                        if (ptrJerry->happinessLevel < 0) {
                            ptrJerry->happinessLevel = 0;
                        }
                    }
                }
                printf("The activity is now over ! \n");
                displayList(*jerryArry);  // Display updated list of Jerries.
                return success;

            case 2:
                // Modify the happiness levels for golf activity.
                for (int j = 1; j < getLengthList(*jerryArry) + 1; j++) {
                    Jerry* ptrJerry = getDataByIndex(*jerryArry, j);
                    if (ptrJerry->happinessLevel >= 50) {
                        ptrJerry->happinessLevel += 10;
                        if (ptrJerry->happinessLevel > 100) {
                            ptrJerry->happinessLevel = 100;
                        }
                    }
                    if (ptrJerry->happinessLevel < 50) {
                        ptrJerry->happinessLevel -= 10;
                        if (ptrJerry->happinessLevel < 0) {
                            ptrJerry->happinessLevel = 0;
                        }
                    }
                }
                printf("The activity is now over ! \n");
                displayList(*jerryArry);  // Display updated list of Jerries.
                return success;

            case 3:
                // Modify the happiness levels for adjusting the TV.
                for (int i = 1; i < getLengthList(*jerryArry) + 1; i++) {
                    Jerry* ptrJerry = getDataByIndex(*jerryArry, i);
                    ptrJerry->happinessLevel += 20;
                    if (ptrJerry->happinessLevel > 100) {
                        ptrJerry->happinessLevel = 100;
                    }
                }
                printf("The activity is now over ! \n");
                displayList(*jerryArry);  // Display updated list of Jerries.
                return success;

            default:
                break;
        }
    } while (1);
}





void printMenu() {
    printf("Welcome Rick, what are your Jerry's needs today ? \n");
    printf("1 : Take this Jerry away from me \n");
    printf("2 : I think I remember something about my Jerry \n");
    printf("3 : Oh wait. That can't be right \n");
    printf("4 : I guess I will take back my Jerry now \n");
    printf("5 : I can't find my Jerry. Just give me a similar one \n");
    printf("6 : I lost a bet. Give me your saddest Jerry \n");
    printf("7 : Show me what you got \n");
    printf("8 : Let the Jerries play \n");
    printf("9 : I had enough. Close this place \n");
}

//destroys all planets and jerries by iterating through arrays, freeing memory, and nullifying pointers.
void destroyAll( const int numberOfPlanets, List** jerryArry, Planet* planetArry[],hashTable* jerryHash,MultiHashTable** CpMultiHash) {
    if(*jerryHash==NULL || *planetArry == NULL ||*jerryArry== NULL || *CpMultiHash == NULL ) {
        return;
    }
    //iterate over planets and destroy each planet if it's not NULL
    destroyHashTable(*jerryHash);
    destroyMultiValueHashTable(*CpMultiHash);
    destroyList(*jerryArry);
    for (int j = 0; j < numberOfPlanets; j++) {
        //check if the planet is not NULL before attempting to destroy it
        if (planetArry[j] != NULL) {
            destroyPlanet(planetArry[j]);
        }
    }
}

status MakeCpMHashFromJerries(List** jerryArry, MultiHashTable** CpMultiHash, const int* numberOfJerries, hashTable* jerryHash) {
    // Check if the number of Jerries is zero, if so return failure
    if (*numberOfJerries == 0) {
        return failure;
    }

    // Find the nearest prime numbers for hash sizes
    int hashsize = findClosestPrime(*numberOfJerries);
    int multyhashsize = findClosestPrime((*numberOfJerries) * 3);

    // Create the multi-value hash table (CpMultiHash)
    *CpMultiHash = createMultiValueHashTable(
        (CopyFunction)deepcopystrKey,
        (FreeFunction)freestr,
        (PrintFunction)printkeyinhash,
        (CopyFunction)copyjerry,
        (FreeFunction)fakefree,
        (PrintFunction)printJerry,
        (EqualFunction)comperstrKey,
        (EqualFunction)comperJerry,
        ConvToInt,
        multyhashsize
    );

    // Create the standard hash table (jerryHash)
    *jerryHash = createHashTable(
        deepcopystrKey,
        freestr,
        printkeyinhash,
        copyjerry,
        fakefree,
        displayjerry,
        comperstrKey,
        ConvToInt,
        hashsize
    );

    // If either of the hash tables failed to create, return failure
    if (*CpMultiHash == NULL) {
        return failure;
    }
    if (*jerryHash == NULL) {
        return failure;
    }

    // Populate the multi-value hash table and the standard hash table with Jerries and their characteristics
    for (int i = 1; i < *numberOfJerries + 1; i++) {
        Jerry* ptrjerry = getDataByIndex(*jerryArry, i);
        // Add each Jerry's characteristics to the multi-value hash table
        for (int j = 0; j < ptrjerry->number_of_characteristics; j++) {
            if (addToMultiValueHashTable(*CpMultiHash, ptrjerry->pointer_physical_characteristics[j]->characteristic_name, ptrjerry) == failure) {
                return failure;  // If adding fails, return failure
            }
        }

        // Add the Jerry to the standard hash table using their ID
        if (addToHashTable(*jerryHash, ptrjerry->id, ptrjerry) == failure) {
            return failure;  // If adding fails, return failure
        }
    }

    return success;  // Return success if everything was processed correctly
}

//loads the planets from a configuration file and stores them in an array.
status loadPlanets(FILE* file, const int numberOfPlanets, Planet* planetArry[]) {
    char line[300];  //temporary buffer for each line
    char planet_name[300];  //name of the planet
    float x, y, z;  //coordinates of the planet
    fgets(line, sizeof(line), file);  //skip "Planets" header line

    //loop through each planet entry and load details into the array
    for (int i = 0; i < numberOfPlanets; i++) {
        if (fgets(line, sizeof(line), file)) {  //read the next line from the file
            //parse the planet details from the line
            sscanf(line, "%299[^,],%f,%f,%f", planet_name, &x, &y, &z);
            //create the planet using the parsed details
            Planet* planet = creatPlanet(planet_name, x, y, z);
            if (planet == NULL) {
                return failure;  //return failure if planet creation failed
            }
            planetArry[i] = planet;  //store the created planet in the array
        }
    }
    return success;  //return success if all planets are loaded
}

//loads Jerries from a configuration file and stores them in an array, along with their characteristics and planet information.
status loadJerries(FILE* file,  int* numberOfJerries, const int numberOfPlanets, List** jerryArry, Planet* planetArry[]) {
    char line[256];  //temporary buffer for each line
    char jerry_id[300], origin_name[300], planet_name[300];
    int happinessLevel = 0;
    char characteristic_name[300];
    float characteristic_value;

    fgets(line, sizeof(line), file);  //skip "Jerries" header line

    //loop through each Jerry entry and load details into the array
    while (fgets(line, sizeof(line), file) && line[0] != ' ' ) {
        if (line[0] != '\t') {
            //skip lines starting with a tab
            //parse Jerry details from the line

            sscanf(line, "%299[^,],%299[^,],%299[^,],%d", jerry_id, origin_name, planet_name, &happinessLevel);
            //find the planet by name and create the origin and Jerry object
            Planet* ptrplanet = findPlanetByName(planetArry, planet_name, numberOfPlanets);
            Jerry* jerry = createJerry(jerry_id,origin_name, happinessLevel,ptrplanet);

            if (ptrplanet == NULL || jerry == NULL) {
                return failure;  //return failure if any creation fails (planet, origin, or Jerry)
            }
            if(numberOfJerries != NULL) {
                if (*numberOfJerries == 0) {
                    *jerryArry = createLinkedList(copyjerry, freejerry, comperJerry, displayjerry, jerry);
                    if (*jerryArry == NULL) {
                        return failure;
                    }
                } else {
                    appendNode(*jerryArry,jerry);
                }
                (*numberOfJerries)++;
            }
        }
            if( line[0] == '\t') {
                //read physical characteristics for the current Jerry

                //continue reading characteristics (tab-indented lines)
                //parse the characteristic name and value
                sscanf(line, "%*[ \t]%299[^:]:%f", characteristic_name, &characteristic_value);
                //create the characteristic object
                PhysicalCharacteristics* ptrPhysicalCharacteristics = creatPhysicalCharacteristics(characteristic_name, characteristic_value);
                if (ptrPhysicalCharacteristics == NULL) {
                    return failure;  //return failure if characteristic creation fails
                }
                //add the characteristic to the Jerry
                if (numberOfJerries == NULL) {
                    return failure;
                }
                if (addCharacteristics(getDataByIndex(*jerryArry,*numberOfJerries),ptrPhysicalCharacteristics) == failure){
                    return failure;  //return failure if adding the characteristic fails
                }
            }
    }
        return success;  //return success if all Jerries are loaded
}

//loads the entire configuration (planets and Jerries) from a given file.
status loadConfiguration(char* configurationFile, const int numberOfPlanets, int* numberOfJerries, List** jerryArry, Planet* planetArry[] ) {
    //open the configuration file for reading
    FILE* file = fopen(configurationFile, "r");
    if (!file) {
        fclose(file);
        return failure;  //return failure if the file cannot be opened
    }

    //load planets from the configuration file
    status res = loadPlanets(file, numberOfPlanets, planetArry);
    if (res == failure) {
        fclose(file);
        return failure;  //return failure if loading planets fails
    }

    //load Jerries from the configuration file
    res = loadJerries(file, numberOfJerries, numberOfPlanets, jerryArry, planetArry);
    if (res == failure) {
        fclose(file);
        return failure;  //return failure if loading Jerries fails
    }
    fclose(file);  //close the file after processing
    return success;  //return success if everything went well
}




int main(int argc, char *argv[]) {
    int choice = 0;

    // Convert the number of planets from command line arguments
    int numberOfPlanets = atoi(argv[1]);

    // Get the configuration file path from the command line argument
    char* configurationFile = argv[2];

    // Array to hold pointers to Planet objects
    Planet* planetArry[numberOfPlanets];

    // Initialize the planet array to NULL
    for (int i = 0; i < numberOfPlanets; i++) {
        planetArry[i] = NULL;
    }

    // Initialize the number of Jerries and the list to hold Jerries
    int numberOfJerries = 0;
    List* jerryArry = NULL;

    // Hash table for storing Jerries by ID
    hashTable jerryHash = NULL;

    // MultiHashTable for storing Jerries by physical characteristics
    MultiHashTable* CpMultiHash = NULL;

    // Load the configuration from the file
    status loadfile = loadConfiguration(configurationFile, numberOfPlanets, &numberOfJerries, &jerryArry, planetArry);
    if (loadfile == failure) {
        // If the configuration fails to load, print an error and clean up
        printf("A memory problem has been detected in the program \n");
        destroyAll(numberOfPlanets, &jerryArry, planetArry, &jerryHash, &CpMultiHash);
    }

    // Create MultiHashTable and HashTable for Jerries
    if (MakeCpMHashFromJerries(&jerryArry, &CpMultiHash, &numberOfJerries, &jerryHash) == failure) {
        destroyAll(numberOfPlanets, &jerryArry, planetArry, &jerryHash, &CpMultiHash);
    }

    // Start the menu-driven loop for user interaction
    do {
        printMenu();  // Display the menu options

        // Read user choice and handle invalid input
        if (scanf("%d", &choice) != 1) {
            printf("Rick this option is not known to the daycare ! \n");
            while (getchar() != '\n');  // Clear the input buffer
            choice = -1;  // Reset choice to ensure it doesn't exit the loop
            continue;  // Skip to the next iteration
        }

        // Check for leftover input (characters after a valid integer)
        char leftover;
        if (scanf("%c", &leftover) == 1 && leftover != '\n') {
            printf("Rick this option is not known to the daycare ! \n");
            while (getchar() != '\n');  // Clear the input buffer
            choice = -1;  // Reset choice to ensure it doesn't exit the loop
            continue;  // Skip to the next iteration
        }

        // Ensure the choice is within the valid range (1-9)
        if (choice < 1 || choice > 9) {
            printf("Rick this option is not known to the daycare ! \n");
            continue;  // Prompt user again
        }

        // Perform the corresponding action based on user input
        switch (choice) {
            case 1:
                // Add a new Jerry to the system
                if (addNewJerryToMain(numberOfPlanets, &numberOfJerries, &jerryArry, planetArry, &jerryHash) == failure) {
                    printf("A memory problem has been detected in the program");
                    destroyAll(numberOfPlanets, &jerryArry, planetArry, &jerryHash, &CpMultiHash);
                    exit(1);  // Exit if memory issue occurs
                }
                break;
            case 2:
                // Add a physical characteristic to an existing Jerry
                if (addPcToJerry(&jerryHash, &CpMultiHash) == failure) {
                    printf("A memory problem has been detected in the program");
                    destroyAll(numberOfPlanets, &jerryArry, planetArry, &jerryHash, &CpMultiHash);
                    exit(1);  // Exit if memory issue occurs
                }
                break;
            case 3:
                // Remove a physical characteristic from a Jerry
                if (removePcFromJerry(&jerryHash, &CpMultiHash) == failure) {
                    printf("A memory problem has been detected in the program");
                    destroyAll(numberOfPlanets, &jerryArry, planetArry, &jerryHash, &CpMultiHash);
                    exit(1);  // Exit if memory issue occurs
                }
                break;
            case 4:
                // Remove a Jerry from the system
                if (removeJerryFromMain(&jerryHash, &CpMultiHash, &numberOfJerries, &jerryArry) == failure) {
                    printf("A memory problem has been detected in the program");
                    destroyAll(numberOfPlanets, &jerryArry, planetArry, &jerryHash, &CpMultiHash);
                    exit(1);  // Exit if memory issue occurs
                }
                break;
            case 5:
                // Find and display a similar Jerry
                if (similarjerry(&jerryHash, &CpMultiHash, &numberOfJerries, &jerryArry) == failure) {
                    printf("A memory problem has been detected in the program");
                    destroyAll(numberOfPlanets, &jerryArry, planetArry, &jerryHash, &CpMultiHash);
                    exit(1);  // Exit if memory issue occurs
                }
                break;
            case 6:
                // Display the saddest Jerry based on their happiness level
                saddestJerry(&jerryHash, &CpMultiHash, &numberOfJerries, &jerryArry);
                break;
            case 7:
                // Display the available planets and Jerries
                showWhatYouGot(numberOfPlanets, &numberOfJerries, &jerryArry, planetArry, &CpMultiHash);
                break;
            case 8:
                // Let Jerries engage in an activity that affects their happiness
                letsJerryPlay(&numberOfJerries, &jerryArry);
                break;
            case 9:
                // Clean up and close the daycare
                printf("The daycare is now clean and close ! \n");
                destroyAll(numberOfPlanets, &jerryArry, planetArry, &jerryHash, &CpMultiHash);
                exit(0);  // Exit the program
                break;
            default:
                break;
        }

    } while (choice != 9);  // Continue until the user chooses to exit (option 9)

    return 0;  // Exit the program
}






