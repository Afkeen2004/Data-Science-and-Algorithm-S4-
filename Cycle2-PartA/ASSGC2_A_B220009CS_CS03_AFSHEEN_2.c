//ASSGC2_A_B220009CS_CS03_AFSHEEN_2

#include <stdio.h>
#include <stdlib.h>

struct node {
    int key;
    int val;
    struct node* left;
    struct node* right;
    int height;
};

// AVL Tree function declarations
struct node* create_node(int key, int val);
int max(int a, int b);
int height(struct node* root);
struct node* right_rot(struct node* y);
struct node* left_rot(struct node* y);
int get_bal(struct node* root);
int avl_find(struct node* root, int key);
struct node* avl_insert(struct node* root, int key, int val);
void inorder_traversal(struct node* root);
void print_elements(struct node* root);
void free_tree(struct node* root);
int avl_size(struct node* root);
int avl_empty(struct node* root);
void print_lower_bound(struct node* root, int key);

// Function to create a new node
struct node* create_node(int key, int val) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    if (temp == NULL) {
        printf("Error in memory allocation");
        exit(0);
    }

    temp->key = key;
    temp->val = val;
    temp->left = NULL;
    temp->right = NULL;
    temp->height = 1;
    return temp;
}

// Utility function to get maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Utility function to get the height of the node
int height(struct node* root) {
    if (root == NULL) {
        return 0;
    } else {
        return root->height;
    }
}

// Rotate right
struct node* right_rot(struct node* y) {
    struct node* x = y->left;
    struct node* t2 = x->right;

    x->right = y;
    y->left = t2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Rotate left
struct node* left_rot(struct node* y) {
    struct node* x = y->right;
    struct node* t2 = x->left;

    x->left = y;
    y->right = t2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Get balance factor of a node
int get_bal(struct node* root) {
    if (root == NULL) {
        return 0;
    }
    return height(root->left) - height(root->right);
}

// Find a key in the AVL Tree
int avl_find(struct node* root, int key) {
    if (root == NULL) {
        return 0;
    }
    if (root->key == key) {
        printf("%d %d\n", root->key, root->val);
        return 1;
    }
    if (key < root->key) {
        return avl_find(root->left, key);
    } else {
        return avl_find(root->right, key);
    }
}

// Insert a key-value pair into the AVL Tree
struct node* avl_insert(struct node* root, int key, int val) {
    if (root == NULL) {
        return create_node(key, val);
    }

    if (key < root->key) {
        root->left = avl_insert(root->left, key, val);
    } else if (key > root->key) {
        root->right = avl_insert(root->right, key, val);
    } else {
        // Key already exists, update the value
        root->val = val;
        return root;
    }

    root->height = max(height(root->left), height(root->right)) + 1;
    int bal = get_bal(root);

    // Perform rotations if necessary
    if (bal > 1 && key < root->left->key) {
        return right_rot(root);
    }

    if (bal < -1 && key > root->right->key) {
        return left_rot(root);
    }

    if (bal > 1 && key > root->left->key) {
        root->left = left_rot(root->left);
        return right_rot(root);
    }

    if (bal < -1 && key < root->right->key) {
        root->right = right_rot(root->right);
        return left_rot(root);
    }

    return root;
}

// Inorder traversal to print elements in ascending order
void inorder_traversal(struct node* root) {
    if (root != NULL) {
        inorder_traversal(root->left);
        printf("%d ", root->key);
        inorder_traversal(root->right);
    }
}

// Print elements in ascending order
void print_elements(struct node* root) {
    if (root == NULL) {
        printf("-1\n");
    } else {
        inorder_traversal(root);
        printf("\n");
    }
}

// Free memory allocated for the AVL tree
void free_tree(struct node* root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

// Get size of the AVL tree
int avl_size(struct node* root) {
    if (root == NULL) {
        return 0;
    } else {
        return 1 + avl_size(root->left) + avl_size(root->right);
    }
}

// Check if the AVL tree is empty
int avl_empty(struct node* root) {
    return (root == NULL) ? 1 : 0;
}

// Print the key-value pair of the first element with not less than the given key
void print_lower_bound(struct node* root, int key) {
    struct node* current = root;
    struct node* lower_bound_node = NULL;

    while (current != NULL) {
        if (current->key >= key) {
            lower_bound_node = current;
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (lower_bound_node != NULL) {
        printf("%d %d\n", lower_bound_node->key, lower_bound_node->val);
    } else {
        printf("-1\n");
    }
}

// Main function
int main() {
    struct node* root = NULL;

    char option;
    int key, val;

    while (1) {
        scanf(" %c", &option); // Added space before %c to consume whitespace characters

        if (option == 't') {
            break; // Terminate the program
        }

        switch (option) {
            case 'i':
                scanf("%d %d", &key, &val);
                root = avl_insert(root, key, val);
                break;
            case 'l':
                scanf("%d", &key);
                print_lower_bound(root, key);
                break;
            case 'f':
                scanf("%d", &key);
                if (!avl_find(root, key)) {
                    printf("-1\n");
                }
                break;
            case 's':
                printf("%d\n", avl_size(root));
                break;
            case 'e':
                printf("%d\n", avl_empty(root));
                break;
            case 'p':
                print_elements(root);
                break;
            default:
                break;        
        }
    }

    // Free memory allocated for the AVL tree
    free_tree(root);

    return 0;
}

