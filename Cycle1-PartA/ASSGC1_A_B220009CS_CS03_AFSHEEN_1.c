// DSA LAB - Cycle 1 - Part A - Q1

#include <stdio.h>

// Define a structure for a stack
struct Stack {
    char characters[1000];
    int top;
};

// Function to push a character onto the stack
void push(struct Stack* stack, char value) {
    stack->top++;
    stack->characters[stack->top] = value;
}

// Function to pop a character from the stack
void pop(struct Stack* stack) {
    stack->top--;
}

// Function to check for duplicate parentheses in the given equation
int check_dup_parenthesis(char eqn[], int len) {
    struct Stack stack;
    stack.top = -1;
    int i, count, val = 0;

    for (i = 0; i < len; i++) {
        if (eqn[i] != ')') {
            push(&stack, eqn[i]);
        } else {
            count = 0;
            while (stack.characters[stack.top] != '(' && stack.top != -1) {
                count++;
                pop(&stack);
            }
            if (count == 1 || count == 0) {
                val = 1; // Duplicate parenthesis found
                break;
            }
            pop(&stack);
        }
    }

    return val;
}

// Main function
int main() {
    int len, i;
    scanf("%d", &len);

    // Array to store the equation
    char eqn[len];
    scanf("%s", eqn);

    // Check for duplicate parentheses and print the result
    printf("%d", check_dup_parenthesis(eqn, len));

    return 0;
}

