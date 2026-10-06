CC = gcc
CFLAGS = -Wall -g
TARGET = JerryBoree
OBJS = JerryBoreeMain.o LinkedList.o KeyValuePair.o HashTable.o Jerry.o MultiValueHashTable.o

# Rule to build the final executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Rule to compile JerryBoreeMain.c into object file
JerryBoreeMain.o: JerryBoreeMain.c LinkedList.h KeyValuePair.h HashTable.h Jerry.h MultiValueHashTable.h
	$(CC) $(CFLAGS) -c JerryBoreeMain.c

# Rule to compile LinkedList.c into object file
LinkedList.o: LinkedList.c LinkedList.h
	$(CC) $(CFLAGS) -c LinkedList.c

# Rule to compile KeyValuePair.c into object file
KeyValuePair.o: KeyValuePair.c KeyValuePair.h
	$(CC) $(CFLAGS) -c KeyValuePair.c

# Rule to compile HashTable.c into object file
HashTable.o: HashTable.c HashTable.h LinkedList.h KeyValuePair.h
	$(CC) $(CFLAGS) -c HashTable.c

# Rule to compile Jerry.c into object file
Jerry.o: Jerry.c Jerry.h
	$(CC) $(CFLAGS) -c Jerry.c

# Rule to compile MultiValueHashTable.c into object file
MultiValueHashTable.o: MultiValueHashTable.c MultiValueHashTable.h HashTable.h
	$(CC) $(CFLAGS) -c MultiValueHashTable.c

# Clean rule to remove generated files
clean:
	rm -f $(TARGET) $(OBJS)

