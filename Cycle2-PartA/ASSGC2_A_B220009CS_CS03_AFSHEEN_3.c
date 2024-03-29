//ASSGC2_A_B220009CS_CS03_AFSHEEN_3

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define colors for Red-Black Tree
#define RED 0
#define BLACK 1

// Structure for a tree node
struct node {
    int key;
    int color;
    struct node *parent, *left, *right;
};

// Function to create a new node
struct node* create_node(int key) {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    new_node->key = key;
    new_node->color = RED; // Newly inserted node is always red
    new_node->parent = new_node->left = new_node->right = NULL;
    return new_node;
}

// Function to perform left rotation
void left_rotate(struct node **root, struct node *x) {
    struct node *y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

// Function to perform right rotation
void right_rotate(struct node **root, struct node *y) {
    struct node *x = y->left;
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == NULL)
        *root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    x->right = y;
    y->parent = x;
}

// Function to fix violations after inserting a new node
void fix_violation(struct node **root, struct node *new_node) {
    struct node *parent = NULL;
    struct node *grandparent = NULL;
    while ((new_node != *root) && (new_node->color != BLACK) && (new_node->parent->color == RED)) {
        parent = new_node->parent;
        grandparent = new_node->parent->parent;
        if (parent == grandparent->left) {
            struct node *uncle = grandparent->right;
            if (uncle != NULL && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                new_node = grandparent;
            } else {
                if (new_node == parent->right) {
                    new_node = parent;
                    left_rotate(root, new_node);
                    parent = new_node->parent;
                }
                parent->color = BLACK;
                grandparent->color = RED;
                right_rotate(root, grandparent);
            }
        } else {
            struct node *uncle = grandparent->left;
            if ((uncle != NULL) && (uncle->color == RED)) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                new_node = grandparent;
            } else {
                if (new_node == parent->left) {
                    new_node = parent;
                    right_rotate(root, new_node);
                    parent = new_node->parent;
                }
                parent->color = BLACK;
                grandparent->color = RED;
                left_rotate(root, grandparent);
            }
        }
    }
    (*root)->color = BLACK;
}

// Function to insert a new node with given key
void insert_rbt(struct node** root, int key) {
    struct node *new_node = create_node(key);
    struct node *parent = NULL;
    struct node *current = *root;

    // Find parent of new_node
    while (current != NULL) {
        parent = current;
        if (key < current->key)
            current = current->left;
        else
            current = current->right;
    }

    // If the tree is empty
    if (parent == NULL) {
        *root = new_node;
    } else {
        // If new_node is smaller than parent, insert it as left child
        if (key < parent->key) {
            parent->left = new_node;
            new_node->parent = parent;
        }
        // If new_node is greater than parent, insert it as right child
        else {
            parent->right = new_node;
            new_node->parent = parent;
        }
    }
    // Fix Red-Black Tree violations after insertion
    fix_violation(root, new_node);
}

// Function to print Parenthesized Representation of the tree
void print_tree(struct node* root) {
    if (root != NULL) {
        printf("( %d ", root->key);
        if (root->color == RED)
            printf("R ");
        else
            printf("B ");
        print_tree(root->left);
        printf(" ");
        print_tree(root->right);
        printf(" )");
    } else {
        printf("( )");
    }
}

int main() {
    struct node* root = NULL;
    char command;
    int key;
    bool skipInput = false;
    do {
        scanf(" %c", &command);
        if (command == 'e')
            break;
        else if (command == '(') {
            // Skip the parenthesized representation
            skipInput = true;
            while (getchar() != ')');
        } else {
            // Read the key
            if (skipInput) {
                skipInput = false;
                continue;
            }
            ungetc(command, stdin);
            scanf("%d", &key);
            insert_rbt(&root, key);
 			print_tree(root);
 			printf("\n");

        }
    } while (1);

    print_tree(root);

    return 0;
}

