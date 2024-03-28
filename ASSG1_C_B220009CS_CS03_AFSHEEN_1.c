//ASSG1_C_B220009CS_CS03_AFSHEEN_1
//From given integer arrays A and B and find their union, intersection and set difference as a menu driven program

#include <stdio.h>
#include <stdbool.h>

#define HASH_TABLE_SIZE 200

typedef struct {
    int size;
    int table[HASH_TABLE_SIZE];
} HashTable;

int hash_function(int key) {
    return key % HASH_TABLE_SIZE;
}

void initialize_table(HashTable *ht) {
    ht->size = 0;
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        ht->table[i] = -1;
    }
}

void insert(HashTable *ht, int key) {
    int index = hash_function(key);
    while (ht->table[index] != -1) {
        index = (index + 1) % HASH_TABLE_SIZE;
    }
    ht->table[index] = key;
    ht->size++;
}

bool contains(HashTable *ht, int key) {
    int index = hash_function(key);
    while (ht->table[index] != -1) {
        if (ht->table[index] == key) {
            return true;
        }
        index = (index + 1) % HASH_TABLE_SIZE;
    }
    return false;
}

// Calculates the union of two sets
void union_func(int A[], int m, int B[], int n) {
    HashTable ht;
    initialize_table(&ht);

    for (int i = 0; i < m; i++) {
        if (!contains(&ht, A[i])) {
            printf("%d ", A[i]);
            insert(&ht, A[i]);
        }
    }
    for (int i = 0; i < n; i++) {
        if (!contains(&ht, B[i])) {
            printf("%d ", B[i]);
            insert(&ht, B[i]);
        }
    }
    printf("\n");
}

// Calculates the intersection of two sets
void intersection(int A[], int m, int B[], int n) {
    HashTable ht;
    initialize_table(&ht);
    int c = 0;

    for (int i = 0; i < n; i++) {
        insert(&ht, B[i]);
    }
    for (int i = 0; i < m; i++) {
        if (contains(&ht, A[i])) {
            printf("%d ", A[i]);
            c= 1;
            ht.size--; // To avoid duplicate printing in case of multiple occurrences of the same element in B
            // Remove element from hash table to ensure unique printing
            int index = hash_function(A[i]);
            while (ht.table[index] != A[i]) {
                index = (index + 1) % HASH_TABLE_SIZE;
            }
            ht.table[index] = -1;
        }
    }
    if(c == 0) printf("-1");
    printf("\n");
}

// Calculates the set difference of two sets
void set_difference(int A[], int m, int B[], int n) {
    HashTable ht;
    initialize_table(&ht);
    int c = 0;

    for (int i = 0; i < n; i++) {
        insert(&ht, B[i]);
    }
    for (int i = 0; i < m; i++) {
        if (!contains(&ht, A[i])) {
            printf("%d ", A[i]);
            c = 1;
        }
    }
    if(c == 0) printf("-1");
    printf("\n");
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    int A[m], B[n];
    for (int i = 0; i < m; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &B[i]);
    }

    char option, array1, array2;
    while (scanf(" %c %c %c", &option, &array1, &array2) == 3) {
        if (option == 'u') {
            if (array1 == 'A' && array2 == 'B') {
                union_func(A, m, B, n);
            } else if (array1 == 'B' && array2 == 'A') {
                union_func(B, n, A, m);
            }
        } else if (option == 'i') {
            if (array1 == 'A' && array2 == 'B') {
                intersection(A, m, B, n);
            } else if (array1 == 'B' && array2 == 'A') {
                intersection(B, n, A, m);
            }
        } else if (option == 's') {
            if (array1 == 'A' && array2 == 'B') {
                set_difference(A, m, B, n);
            } else if (array1 == 'B' && array2 == 'A') {
                set_difference(B, n, A, m);
            }
        } else if (option == 'e') {
            break;
        }
    }

    return 0;
}
