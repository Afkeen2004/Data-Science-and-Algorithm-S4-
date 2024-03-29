//ASSG1_C_B220009CS_CS03_AFSHEEN_1
//Hash table with chaining as a collision resolution method with a menu driven program
#include <stdio.h>
#include <stdlib.h>

// Node structure for chaining
struct Node {
    int key;
    struct Node* next;
};

// Hash table structure
struct HashTable {
    int size;
    struct Node** table;
};

// Function to create a new node
struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->next = NULL;
    return newNode;
}

// Function to create a new hash table
struct HashTable* createHashTable(int size) {
    struct HashTable* newTable = (struct HashTable*)malloc(sizeof(struct HashTable));
    newTable->size = size;
    newTable->table = (struct Node**)malloc(sizeof(struct Node*) * size);
    for (int i = 0; i < size; i++) {
        newTable->table[i] = NULL;
    }
    return newTable;
}

// Hash function to find index for key
int hashFunction(int key, int size) {
    return key % size;
}

// Function to search for a key in the hash table
int in_search(struct HashTable* hashTable, int key) {
    int index = hashFunction(key, hashTable->size);

    struct Node* current = hashTable->table[index];
    int position = 1;
    while (current != NULL && current->key != key) {
        current = current->next;
        position++;
    }
    if (current == NULL) {
        return -1;
    } else {
        return 1;
    }
}

// Function to insert key into hash table
void insert(struct HashTable* hashTable, int key) {
    int index = hashFunction(key, hashTable->size);

    struct Node* newNode = createNode(key);

    if(in_search(hashTable, key) != 1){
    // If the slot is empty
		if (hashTable->table[index] == NULL) {
		    hashTable->table[index] = newNode;
		} else {
		    // Chaining to handle collisions 
		    struct Node* current = hashTable->table[index];
		    struct Node* prev = NULL;
		    while (current != NULL && current->key < key) {
		        prev = current;
		        current = current->next;
		    }
		    if (prev == NULL) {
		        newNode->next = hashTable->table[index];
		        hashTable->table[index] = newNode;
		    } else {
		        prev->next = newNode;
		        newNode->next = current;
		    }
		}
	}else{
	printf("-1\n");
	}
}

// Function to search for a key in the hash table
void search(struct HashTable* hashTable, int key) {
    int index = hashFunction(key, hashTable->size);

    struct Node* current = hashTable->table[index];
    int position = 1;
    while (current != NULL && current->key != key) {
        current = current->next;
        position++;
    }
    if (current == NULL) {
        printf("-1\n");
    } else {
        printf("%d %d\n", index, position);
    }
}

// Function to delete a key from the hash table
void delete(struct HashTable* hashTable, int key) {
    int index = hashFunction(key, hashTable->size);

    struct Node* current = hashTable->table[index];
    struct Node* prev = NULL;
    int position = 1;
    while (current != NULL && current->key != key) {
        prev = current;
        current = current->next;
        position++;
    }
    if (current == NULL) {
        printf("-1\n");
    } else {
        if (prev == NULL) {
            hashTable->table[index] = current->next;
        } else {
            prev->next = current->next;
        }
        free(current);
        printf("%d %d\n", index, position);
    }
}

// Function to update a key in the hash table
void update(struct HashTable* hashTable, int oldKey, int newKey) {
    int index = hashFunction(oldKey, hashTable->size);
   
    if(in_search(hashTable, newKey) != 1){
		struct Node* current = hashTable->table[index];
		struct Node* prev = NULL;
		int position = 1;
		while (current != NULL && current->key != oldKey) {
		    prev = current;
		    current = current->next;
		    position++;
		}
		if (current == NULL) {
		    printf("-1\n");
		} else {
		    delete(hashTable, oldKey);
		    insert(hashTable, newKey);
		}
	}else{
	printf("-1\n");
	}
}

// Function to print elements in a chain at index in the hash table
void printElementsInChain(struct HashTable* hashTable, int index) {
    if (hashTable->table[index] == NULL) {
        printf("-1\n");
        return;
    }
    struct Node* current = hashTable->table[index];
    while (current != NULL) {
        printf("%d ", current->key);
        current = current->next;
    }
    printf("\n");
}

// Function to free memory allocated for hash table
void destroyHashTable(struct HashTable* hashTable) {
    for (int i = 0; i < hashTable->size; i++) {
        struct Node* current = hashTable->table[i];
        while (current != NULL) {
            struct Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(hashTable->table);
    free(hashTable);
}

int main() {
    int size;
    char command;
    int key, oldKey, newKey;
    struct HashTable* hashTable;

    // Input table size
    scanf("%d", &size);
    hashTable = createHashTable(size);

    while (1) {
        // Input command
        scanf(" %c", &command);
        if (command == 'e') {
            // End program
            break;
        } else if (command == 'i') {
            // Insert key
            scanf("%d", &key);
            insert(hashTable, key);
        } else if (command == 's') {
            // Search key
            scanf("%d", &key);
            search(hashTable, key);
        } else if (command == 'd') {
            // Delete key
            scanf("%d", &key);
            delete(hashTable, key);
        } else if (command == 'u') {
            // Update key
            scanf("%d %d", &oldKey, &newKey);
            update(hashTable, oldKey, newKey);
        } else if (command == 'p') {
            // Print elements in chain
            scanf("%d", &key);
            printElementsInChain(hashTable, key);
        }
    }

    // Free memory allocated for hash table
    destroyHashTable(hashTable);

    return 0;
}

