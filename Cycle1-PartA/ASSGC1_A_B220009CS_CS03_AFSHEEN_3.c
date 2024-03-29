//DSA LAB - Cycle 1 - Part A - Q3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// Structure to represent a patient
struct Patient { 
    char name[100];
    int priority;
    char admitTime[10];
};

// Structure to represent the priority queue
struct PriorityQueue {
    struct Patient *patients;
    int size;
};

// Function to swap two patients in the priority queue
void swap(struct Patient *a, struct Patient *b) {
    struct Patient temp = *a;
    *a = *b;
    *b = temp;
}

// Function to initialize the priority queue
struct PriorityQueue* initializePriorityQueue(int capacity) {
    struct PriorityQueue* pq = (struct PriorityQueue*)malloc(sizeof(struct PriorityQueue));
    pq->patients = (struct Patient*)malloc(capacity * sizeof(struct Patient));
    pq->size = 0;
    return pq;
}

// Function to maintain the max heap property of the priority queue
void maxHeapify(struct PriorityQueue* pq, int i) {
    int largest = i;
    int leftChild = 2 * i + 1;
    int rightChild = 2 * i + 2;

    if (leftChild < pq->size &&
        (pq->patients[leftChild].priority > pq->patients[largest].priority ||
         (pq->patients[leftChild].priority == pq->patients[largest].priority &&
          strcmp(pq->patients[leftChild].admitTime, pq->patients[largest].admitTime) < 0))) {
        largest = leftChild;
    }

    if (rightChild < pq->size &&
        (pq->patients[rightChild].priority > pq->patients[largest].priority ||
         (pq->patients[rightChild].priority == pq->patients[largest].priority &&
          strcmp(pq->patients[rightChild].admitTime, pq->patients[largest].admitTime) < 0))) {
        largest = rightChild;
    }

    if (largest != i) {
        swap(&pq->patients[i], &pq->patients[largest]);
        maxHeapify(pq, largest);
    }
}

// Function to insert a patient into the priority queue
void admitPatient(struct PriorityQueue* pq, struct Patient patient) {
    if (pq->size == 0) {
        pq->patients[0] = patient;
        pq->size++;
        return;
    }

    pq->size++;
    int i = pq->size - 1;
    pq->patients[i] = patient;

    while (i > 0 &&
           (pq->patients[(i - 1) / 2].priority < pq->patients[i].priority ||
            (pq->patients[(i - 1) / 2].priority == pq->patients[i].priority &&
             strcmp(pq->patients[(i - 1) / 2].admitTime, pq->patients[i].admitTime) < 0))) {
        swap(&pq->patients[i], &pq->patients[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Function to extract the patient with the highest priority
struct Patient treatNextPatient(struct PriorityQueue* pq) {
    if (pq->size == 0) {
        struct Patient emptyPatient;
        strcpy(emptyPatient.name, "Empty");
        emptyPatient.priority = -1;
        strcpy(emptyPatient.admitTime, "");
        return emptyPatient;
    }

    if (pq->size == 1) {
        pq->size--;
        return pq->patients[0];
    }

    struct Patient root = pq->patients[0];
    pq->patients[0] = pq->patients[pq->size - 1];
    pq->size--;
    maxHeapify(pq, 0);

    return root;
}

// Function to get the patient with the highest priority without removing them
struct Patient checkNextPatient(struct PriorityQueue* pq) {
    if (pq->size == 0) {
        struct Patient emptyPatient;
        strcpy(emptyPatient.name, "Empty");
        emptyPatient.priority = -1;
        strcpy(emptyPatient.admitTime, "");
        return emptyPatient;
    }

    return pq->patients[0];
}

// Function to find the index of a patient in the priority queue based on name and admit time
int dischargePatien(struct PriorityQueue* pq, char name[], char admitTime[]) {
    for (int i = 0; i < pq->size; i++) {
        if (strcmp(pq->patients[i].name, name) == 0 && strcmp(pq->patients[i].admitTime, admitTime) == 0) {
            return i;
        }
    }
    return -1;
}

// Function to update the priority of a patient in the priority queue
void updateConditionSeverity(struct PriorityQueue* pq, int index, int newPriority) {
    int oldPriority = pq->patients[index].priority;
    pq->patients[index].priority = newPriority;

    if (newPriority > oldPriority) {
        // Increase in priority, adjust the patient's position upwards
        while (index > 0 &&
               (pq->patients[(index - 1) / 2].priority < pq->patients[index].priority ||
                (pq->patients[(index - 1) / 2].priority == pq->patients[index].priority &&
                 strcmp(pq->patients[(index - 1) / 2].admitTime, pq->patients[index].admitTime) > 0))) {
            swap(&pq->patients[index], &pq->patients[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    } else if (newPriority < oldPriority) {
        // Decrease in priority, adjust the patient's position downwards
        maxHeapify(pq, index);
    }
    // If the priority remains the same, no further action is needed
}

// Function to remove a patient from the priority queue based on name and admit time
void removePatient(struct PriorityQueue* pq, int index) {
    updateConditionSeverity(pq, index, INT_MAX);
    treatNextPatient(pq);
}

// Function to print details of all patients in priority order
void printAllPatients(struct PriorityQueue* pq) {
    struct PriorityQueue* copyPQ = initializePriorityQueue(pq->size);

    // Copy patients from pq to copyPQ
    for (int i = 0; i < pq->size; i++) {
        copyPQ->patients[i] = pq->patients[i];
        copyPQ->size++;
    }

    // Print patients in priority order
    while (copyPQ->size > 0) {
        struct Patient patient = treatNextPatient(copyPQ);
        printf("%s %d %s\n", patient.name, patient.priority, patient.admitTime);
    }

    // Free the memory allocated for copyPQ
    free(copyPQ->patients);
    free(copyPQ);
}

int main() {
    struct PriorityQueue* pq = initializePriorityQueue(1000);

    char operation;
    while (1) {
        scanf(" %c", &operation);

        if (operation == 'a') {
            struct Patient newPatient;
            scanf("%s %d %s", newPatient.name, &newPatient.priority, newPatient.admitTime);
            admitPatient(pq, newPatient);
        } else if (operation == 't') {
            struct Patient treatedPatient = treatNextPatient(pq);
            printf("%s %d %s\n", treatedPatient.name, treatedPatient.priority, treatedPatient.admitTime);
        } else if (operation == 'c') {
            struct Patient nextPatient = checkNextPatient(pq);
            printf("%s %d %s\n", nextPatient.name, nextPatient.priority, nextPatient.admitTime);
        } else if (operation == 'd') {
            char name[100], admitTime[10];
            scanf("%s %s", name, admitTime);
            int index = dischargePatien(pq, name, admitTime);
            if (index != -1) {
                removePatient(pq, index);
            }
        } else if (operation == 'u') {
            char name[100], admitTime[10];
            int newPriority;
            scanf("%s %s %d", name, admitTime, &newPriority);
            int index = dischargePatien(pq, name, admitTime);
            if (index != -1) {
                updateConditionSeverity(pq, index, newPriority);
            }
        } else if (operation == 'p') {
            printAllPatients(pq);
        } else if (operation == 'e') {
            break;
        }
    }

    // Free the memory allocated for pq
    free(pq->patients);
    free(pq);

    return 0;
}

