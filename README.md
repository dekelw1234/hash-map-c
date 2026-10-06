# Generic Hash Map & Multi-Value Hash Map in C

A small library of generic data structures written in C, and a command-line application that uses them.

All structures are type-agnostic: they store `void*` elements and receive the behavior they need (copy, free, print, compare, hash) as function pointers, so the same code works for any key and value type.

## Data structures

| Module | Description |
|---|---|
| `LinkedList` | Generic singly linked list |
| `KeyValuePair` | Generic key-value pair |
| `HashTable` | Hash map using separate chaining (a linked list per bucket) with modulo-based hashing |
| `MultiValueHashTable` | Hash map where each key maps to a list of values, built on top of `HashTable` |

Memory is managed manually (`malloc`/`free`). Each structure owns its elements and releases them through the callbacks it was created with.

## Example application: JerryBoree

`JerryBoreeMain.c` is an interactive "daycare" management system that loads planets and characters from a configuration file and lets the user add, find, update and remove characters through a text menu.

- A `HashTable` gives O(1) average lookup of a character by ID.
- A `MultiValueHashTable` maps each physical characteristic (e.g. `Height`, `Weight`) to all the characters that have it.

## Build and run

```bash
make
./JerryBoree <number_of_planets> configuration_file.txt
```

For example:

```bash
./JerryBoree 4 configuration_file.txt
```

## Memory checking

The project was checked for memory leaks with Valgrind:

```bash
valgrind --leak-check=full --track-origins=yes ./JerryBoree 4 configuration_file.txt < input.txt
```

`run_with_bsh.sh` generates a sample input file and runs the program under Valgrind.

## Project structure

```
Defs.h                    shared types and function-pointer typedefs
LinkedList.c/.h           generic linked list
KeyValuePair.c/.h         generic key-value pair
HashTable.c/.h            hash map (separate chaining)
MultiValueHashTable.c/.h  multi-value hash map
Jerry.c/.h                domain objects for the example app
JerryBoreeMain.c          interactive CLI application
Makefile                  build with gcc
```
