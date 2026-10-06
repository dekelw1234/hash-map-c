cmake_minimum_required(VERSION 3.22.1)
project(Hw3 C)

set(CMAKE_C_STANDARD 11)

add_executable(Hw3  Defs.h LinkedList.h LinkedList.c
        KeyValuePair.h
        KeyValuePair.c
        HashTable.h
        HashTable.c
        MultiValueHashTable.h
        Jerry.h
        Jerry.c
        MultiValueHashTable.c
        JerryBoreeMain.c)

