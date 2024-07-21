#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define TABLE_SIZE 10
 
// Structure to store key-value pairs
typedef struct Entry {
    char key[256];
    char value[256];
    struct Entry* next; // For handling collisions using chaining
} Entry;
 
// Hash table
Entry* hashTable[TABLE_SIZE];
 
// Hash function
unsigned int hash(char* key) {
    unsigned long int hashValue = 0;
    int i = 0;
 
    while (key[i] != '\0') {
        hashValue = (hashValue << 8) + key[i];
        i++;
    }
 
    return hashValue % TABLE_SIZE;
}
 
// Initialize hash table
void initializeTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }
}
 
// Insert key-value pair
void insert(char* key, char* value) {
    unsigned int index = hash(key);
    Entry* newEntry = (Entry*)malloc(sizeof(Entry));
    strcpy(newEntry->key, key);
    strcpy(newEntry->value, value);
    newEntry->next = hashTable[index];
    hashTable[index] = newEntry;
}
 
// Search for a key
char* search(char* key) {
    unsigned int index = hash(key);
    Entry* entry = hashTable[index];
 
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }
 
    return NULL;
}
 
// Delete a key-value pair
void delete(char* key) {
    unsigned int index = hash(key);
    Entry* entry = hashTable[index];
    Entry* prev = NULL;
 
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            if (prev == NULL) {
                hashTable[index] = entry->next;
            } else {
                prev->next = entry->next;
            }
            free(entry);
            return;
        }
        prev = entry;
        entry = entry->next;
    }
}
 
// Print the hash table
void printTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Entry* entry = hashTable[i];
        if (entry != NULL) {
            printf("Index %d: ", i);
            while (entry != NULL) {
                printf("(%s: %s) -> ", entry->key, entry->value);
                entry = entry->next;
            }
            printf("NULL\n");
        }
    }
}
 
int main() {
    initializeTable();
 
    // Inserting key-value pairs
    insert("name", "Alice");
    insert("age", "30");
    insert("city", "New York");
 
    // Searching for values
    printf("Search for 'name': %s\n", search("name"));
    printf("Search for 'age': %s\n", search("age"));
    printf("Search for 'city': %s\n", search("city"));
 
    // Deleting a key-value pair
    delete("age");
    printf("Search for 'age' after deletion: %s\n", search("age"));
 
    // Print hash table
    printTable();
 
    return 0;
}