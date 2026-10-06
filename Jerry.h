#ifndef JERRY_H
#define JERRY_H

#include "Defs.h"

//struct planet
//planet has a name and 3D coordinates (x, y, z).
typedef struct Planet_s {
    char* planet_name; //name of the planet
    float x, y, z;     //coordinates of the planet
} Planet;

//struct origin of a jerry
//origin has a name and specific planet.
typedef struct Origin_s {
    char* origin_name;  //name of the origin
    Planet* birth_planet; //pointer to the planet of origin
} Origin;

//struct physical characteristic
//characteristic has a name and a value.
typedef struct PhysicalCharacteristics_s {
    char* characteristic_name; //name of the characteristic
    float value;               //value of the characteristic
} PhysicalCharacteristics;

//struct  jerry
//jerry has an id, origin, happiness level, and arry of physical characteristics ptr.
typedef struct Jerry_s {
    char* id; //id for the jerry
    Origin* origin; //jerry's origin
    int happinessLevel; //happiness level of the jerry
    PhysicalCharacteristics** pointer_physical_characteristics; //array of physical characteristics ptr
    int number_of_characteristics; //number of characteristics the jerry has
} Jerry;

//creates a new jerry and returns a pointer
//parameters: jerry's id, origin, and initial happiness level
Jerry* createJerry(char* id, char* origin, int happinessLevel,Planet* birth_planet);

//frees all memory associated with a jerry
void destroyJerry(Jerry* ptr_jerry);

//creates a new planet and returns a pointer
//parameters: planet name and its 3D coordinates (x, y, z)
Planet* creatPlanet(char* planet_name, float x, float y, float z);

//frees all memory associated with a planet
void destroyPlanet(Planet* ptrPlanet);

//creates a new physical characteristic and returns a pointer
//parameters: characteristic name and its value
PhysicalCharacteristics* creatPhysicalCharacteristics(char* characteristic_name, float value);

//frees all memory associated with a physical characteristic
void destroyPhysicalCharacteristics(PhysicalCharacteristics* ptrPhysicalCharacteristics);


//frees all memory associated with an origin
void destroyOrigin(Origin* ptrOrigin);

//checks if a physical characteristic exists for a given jerry
//parameters: pointer to the jerry and the characteristic
bool is_ability_exists(Jerry* jerry, char* ability_name);

//adds a physical characteristic to a jerry
//parameters: pointer to the jerry and the characteristic to add
status addCharacteristics(Jerry* jerry, PhysicalCharacteristics* ability_name);

//removes a physical characteristic from a jerry
//parameters: pointer to the jerry and the name of the characteristic to remove
status removeCharacteristics(Jerry* jerry, char* ability_name);

//prints all information about a jerry
status printJerry(Jerry* jerry);

//prints all information about a planet
status printPlanet(Planet* planet);



#endif //JERRY_H
