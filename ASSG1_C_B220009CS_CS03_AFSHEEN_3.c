//ASSG1_C_B220009CS_CS03_AFSHEEN_3
//perform various functions with student information as a menu driven program 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Define the structure for each node in the hash table
struct Student {
    char name[10000];
    char roll_Number[8];
    char branch[3];
    int age;
    struct Student *next;
};

// Function to get ASCII value of a character
int get_Ascii(char c) {
    return c;
}

// Function to compute hash value for a given student
int compute_Hash(struct Student *student) {
    int i = 0, sum = 0;
    for (i = 0; student->name[i] != '\0'; i++) {
        sum += get_Ascii(student->name[i]);
    }
    return (sum + student->age) % 4;
}

// Function to create a new student node
struct Student *create_Student(char name[], char roll_Number[], char branch[], int age) {
    struct Student *new_Student = (struct Student *)malloc(sizeof(struct Student));
    strcpy(new_Student->name, name);
    strcpy(new_Student->roll_Number, roll_Number);
    strcpy(new_Student->branch, branch);
    new_Student->age = age;
    new_Student->next = NULL;
    return new_Student;
}

// Function to insert a student into the hash table
void insert(struct Student *hash_Table[], char name[], char roll_Number[], char branch[], int age) {
    struct Student *new_Student = create_Student(name, roll_Number, branch, age);
    int index = compute_Hash(new_Student);
    if (hash_Table[index] == NULL) {
        hash_Table[index] = new_Student;
    } else {
        struct Student *ptr = hash_Table[index];
        while (ptr->next != NULL) {
            ptr = ptr->next;
        }
        ptr->next = new_Student;
    }
}

// Function to count and print students in a group
void count(struct Student *hash_Table[], int index) {
    int count = 0;
    struct Student *ptr = hash_Table[index];
    while (ptr != NULL) {
        count++;
        ptr = ptr->next;
    }
    printf("%d ", count);
    ptr = hash_Table[index];
    while (ptr != NULL) {
        printf("%s ", ptr->name);
        ptr = ptr->next;
    }
}

// Function to print students belonging to a particular branch
void print_By_Branch(struct Student *hash_Table[], int index, char branch[]) {
    if (hash_Table[index] == NULL) {
        printf("-1");
        return;
    }
    struct Student *ptr = hash_Table[index];
    int count = 0;
    while (ptr != NULL) {
        if ((strcmp(branch, "cs") == 0 || strcmp(branch, "CS") == 0) && (strcmp(ptr->branch, "CS") == 0 || strcmp(ptr->branch, "cs") == 0)) {
            printf("%s ", ptr->name);
            count++;
        }
        if ((strcmp(branch, "ec") == 0 || strcmp(branch, "EC") == 0) && (strcmp(ptr->branch, "EC") == 0 || strcmp(ptr->branch, "ec") == 0)) {
            printf("%s ", ptr->name);
            count++;
        }
        if ((strcmp(branch, "ee") == 0 || strcmp(branch, "EE") == 0) && (strcmp(ptr->branch, "EE") == 0 || strcmp(ptr->branch, "ee") == 0)) {
            printf("%s ", ptr->name);
            count++;
        }
        if ((strcmp(branch, "ce") == 0 || strcmp(branch, "CE") == 0) && (strcmp(ptr->branch, "CE") == 0 || strcmp(ptr->branch, "ce") == 0)) {
            printf("%s ", ptr->name);
            count++;
        }
        ptr = ptr->next;
    }
    if (ptr == NULL && count == 0) {
        printf("-1");
        return;
    }
}

int main() {
    struct Student *hash_Table[4];
    int i = 0;
    char name[10000], roll_Number[8], branch[3], branchCode[2], branchIndex[3];
    int age, group, n;

    // Initialize hash table to NULL
    for (i = 0; i < 4; i++) {
        hash_Table[i] = NULL;
    }

    // Input the number of students
    scanf("%d", &n);

    // Input student details and insert into hash table
    for (i = 0; i < n; i++) {
        scanf("%s %7s%2s", name, roll_Number, branch);
        scanf("%d", &age);
        insert(hash_Table, name, roll_Number, branch, age);
    }

    // Command processing loop
    while (1) {
        scanf("%s", branchCode);
        if (strcmp(branchCode, "e") == 0) {
            break;
        }
        if (strcmp(branchCode, "c") == 0) {
            scanf("%d", &group);
            count(hash_Table, group);
            printf("\n");
        }
        if (strcmp(branchCode, "0") == 0) {
            scanf("%s", branchIndex);
            print_By_Branch(hash_Table, 0, branchIndex);
            printf("\n");
        }
        if (strcmp(branchCode, "1") == 0) {
            scanf("%s", branchIndex);
            print_By_Branch(hash_Table, 1, branchIndex);
            printf("\n");
        }
        if (strcmp(branchCode, "2") == 0) {
            scanf("%s", branchIndex);
            print_By_Branch(hash_Table, 2, branchIndex);
            printf("\n");
        }
        if (strcmp(branchCode, "3") == 0) {
            scanf("%s", branchIndex);
            print_By_Branch(hash_Table, 3, branchIndex);
            printf("\n");
        }
    }

    return 0;
}

