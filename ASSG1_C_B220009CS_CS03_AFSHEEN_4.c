//ASSG1_C_B220009CS_CS03_AFSHEEN_4
//Open addressing to handle collisions - three ways - Linear Probing, Quadratic Probing and Double Hashing
#include <stdio.h>
#include <stdlib.h>

// Function to check if a number is prime
int isPrime(int n) {
    if (n <= 1) {
        return 0;
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

// Function to find the largest prime less than n
int largestPrimeLessThanN(int n) {
    for (int i = n - 1; i >= 2; i--) {
        if (isPrime(i)) {
            return i;
        }
    }
    return -1;
}

// Function for linear probing
void linearProbing(int keys[], int n, int m) {
    int table[m];
    int collisions = 0;
    for (int i = 0; i < m; i++) {
        table[i] = -1; // Initialize table with -1 (indicating empty)
    }

    for (int j = 0; j < n; j++) {
        int key = keys[j];
        int i = 0;
        int in;
        
        while (i < m){
            in = (key + i) % m;
            if (table[in] == -1){
                table[in] = key;
                printf("%d ", in);
                break;
            }else{
                collisions++;
                i++;
            }
        }
    }
    printf("\n%d\n", collisions);
}

// Function for quadratic probing
void quadraticProbing(int keys[], int n, int m) {
    int table[m];
    int collisions = 0;
    for (int i = 0; i < m; i++) {
        table[i] = -1; // Initialize table with -1 (indicating empty)
    }

    for (int i = 0; i < n; i++) {
        int key = keys[i];
        int index = key % m;
        int j = 0;
        while (table[(index + j * j) % m] != -1) {
            collisions++;
            j++;
        }
        table[(index + j * j) % m] = key;
        printf("%d ", (index + j * j) % m);
    }
    printf("\n%d\n", collisions);
}

// Function for double hashing
void doubleHashing(int keys[], int n, int m) {
    int table[m];
    int collisions = 0;
    int R = largestPrimeLessThanN(m);

    for (int i = 0; i < m; i++) {
        table[i] = -1; // Initialize table with -1 (indicating empty)
    }

    for (int i = 0; i < n; i++) {
        int key = keys[i];
        int index = key % m;
        int h2 = R - (key % R);
        int j = 0;
        while (table[(index + j * h2) % m] != -1) {
            collisions++;
            j++;
        }
        table[(index + j * h2) % m] = key;
        printf("%d ", (index + j * h2) % m);
    }
    
    printf("\n%d\n", collisions);
}

//main function
int main() {
    int m;
    scanf("%d", &m);

    int keys[1000];
    int n = 0;

    while (scanf("%d", &keys[n]) != EOF) {
        n++;
    }
    
    linearProbing(keys, n, m);
    
    quadraticProbing(keys, n, m);
    
    doubleHashing(keys, n, m);

    return 0;
}

