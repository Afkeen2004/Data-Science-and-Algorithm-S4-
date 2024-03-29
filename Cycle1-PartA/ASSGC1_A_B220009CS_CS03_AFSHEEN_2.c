// DSA LAB - Cycle 1 - Part A - Q2

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Define a structure for a node in the linked list
struct node {
    int data;
    struct node* next;
};

// Define a structure for a linked list
struct LinkedList {
    struct node* head;
};

// Function to create a new node with the given data
struct node* create_node(int data) {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    if (new_node == NULL) {
        exit(1);  // Exit the program if memory allocation fails
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// Function to insert a new node with data at the tail of the linked list
void list_insert_tail(struct LinkedList* list, int data) {
    struct node* new_node = create_node(data);

    if (list->head == NULL) {
        list->head = new_node;
    } else {
        struct node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

// Function to delete a node at the specified index in the linked list
int list_delete_at_index(struct LinkedList* list, int index) {
    if (list->head == NULL || index < 1) {
        return -1;  // Invalid operation, return -1
    }

    if (index == 1) {
        struct node* temp = list->head;
        int data = temp->data;
        list->head = temp->next;
        free(temp);
        return data;
    }

    struct node* current = list->head;
    struct node* prev = NULL;

    for (int i = 1; current != NULL && i < index; ++i) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        return -1;  // Index out of bounds, return -1
    }

    prev->next = current->next;
    int data = current->data;
    free(current);
    return data;
}

// Function to remove duplicate nodes from the linked list
void list_remove_duplicates(struct LinkedList* list) {
    struct node* current = list->head;

    while (current != NULL) {
        struct node* ptr = current;

        while (ptr->next != NULL) {
            if (current->data == ptr->next->data) {
                struct node* temp = ptr->next;
                ptr->next = ptr->next->next;
                free(temp);
            } else {
                ptr = ptr->next;
            }
        }

        current = current->next;
    }
}

// Function to create a copy of the linked list
struct node* copy_list(struct node* head) {
    struct node* new_head = NULL;
    struct node* tail = NULL;

    struct node* current = head;
    while (current != NULL) {
        struct node* new_node = create_node(current->data);

        if (new_head == NULL) {
            new_head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }

        current = current->next;
    }

    return new_head;
}

// Function to check if a linked list is a palindrome
bool is_palindrome(struct node* head) {
    if (head == NULL || head->next == NULL) {
        return true;  // An empty list or a single node is always a palindrome
    }

    // Find the middle of the linked list using the two-pointer technique
    struct node* slow = head;
    struct node* fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Reverse the second half of the linked list
    struct node* prev = NULL;
    struct node* current = slow;
    struct node* next;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    // Compare the two halves of the linked list
    struct node* first = head;
    struct node* second = prev;

    while (second != NULL) {
        if (first->data != second->data) {
            return false;  // Not a palindrome
        }
        first = first->next;
        second = second->next;
    }

    return true;  // The linked list is a palindrome
}

// Function to display the elements of the linked list
void list_display(struct LinkedList* list) {
    struct node* cur = list->head;
    while (cur != NULL) {
        printf("%d", cur->data);
        cur = cur->next;
        if (cur != NULL) {
            printf(" ");
        }
    }
    if (list->head == NULL) {
        printf("-1");
    }
    printf("\n");
}

// Main function
int main() {
    struct LinkedList list;
    list.head = NULL;

    char command;
    int value, index;

    while (1) {
        scanf(" %c", &command);

        switch (command) {
            case 'a':
                scanf("%d", &value);
                list_insert_tail(&list, value);
                break;

            case 'r':
                scanf("%d", &index);
                value = list_delete_at_index(&list, index);
                if (value != -1) {
                    printf("%d\n", value);
                } else {
                    printf("-1\n");
                }
                break;

            case 'd':
                list_remove_duplicates(&list);
                list_display(&list);
                break;

            case 'p':
                {
                    struct node* list_copy = copy_list(list.head);
                    printf("%s\n", is_palindrome(list_copy) ? "Y" : "N");
                    // Free the copied list
                    while (list_copy != NULL) {
                        struct node* temp = list_copy;
                        list_copy = list_copy->next;
                        free(temp);
                    }
                }
                break;

            case 's':
                list_display(&list);
                break;

            case 'e':
                // Freeing memory
                while (list.head != NULL) {
                    struct node* temp = list.head;
                    list.head = list.head->next;
                    free(temp);
                }
                return 0;

            default:
                printf("-1\n");
        }
    }

    return 0;
}

