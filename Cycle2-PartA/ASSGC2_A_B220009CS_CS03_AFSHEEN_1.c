//ASSGC2_A_B220009CS_CS03_AFSHEEN_1

#include <stdio.h>
#include <stdlib.h>

int rr = 0;
int lr = 0;

struct node {
    int data;
    struct node* left;
    struct node* right;
    int height;
};

struct node* create_node(int val) {
    struct node* temp = (struct node*) malloc (sizeof(struct node));
    if (temp == NULL) {
        printf("Error in memory allocation\n");
        exit(EXIT_FAILURE);
    }
    
    temp->data = val;
    temp->left = NULL;
    temp->right = NULL;
    temp->height = 1;
    return temp;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(struct node* root) {
    if (root == NULL) {
        return 0;
    } else {
        return root->height;
    }
}

int get_bal(struct node* root) {
    if (root == NULL) {
        return 0;
    }
    return height(root->left) - height(root->right);
}

struct node* right_rot(struct node* y) {
    struct node* x = y->left;
    struct node* t2 = x->right;

    x->right = y;
    y->left = t2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

struct node* left_rot(struct node* y) {
    struct node* x = y->right;
    struct node* t2 = x->left;

    x->left = y;
    y->right = t2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

struct node* avl_insert(struct node* root, int key) {
    if (root == NULL) {
        return create_node(key);
    }

    if (key < root->data) {
        root->left = avl_insert(root->left, key);
    } else if (key > root->data) {
        root->right = avl_insert(root->right, key);
    } else {
        // Duplicate keys are not allowed in AVL trees
        return root;
    }

    root->height = max(height(root->left), height(root->right)) + 1;
    int bal = get_bal(root);

    // Perform rotations if necessary
    if (bal > 1 && key < root->left->data) {
    	rr++;
        return right_rot(root);
    }
        
    if (bal < -1 && key > root->right->data) {
    	lr++;
        return left_rot(root);
    }
        
    if (bal > 1 && key > root->left->data) {
		lr++;
		rr++;
        root->left = left_rot(root->left);
        return right_rot(root);
    }
        
    if (bal < -1 && key < root->right->data) {
		lr++;
		rr++;
        root->right = right_rot(root->right);
        return left_rot(root);
    }

    return root;
}

int avl_find(struct node* root, int key, int arr[], int *index) {
    if (root == NULL) {
        return 0;
    }

    if (root->data == key) {
        arr[(*index)++] = root->data;
        return 1;
    }

    if (avl_find(root->left, key, arr, index)) {
        arr[(*index)++] = root->data;
        return 1;
    }

    if (avl_find(root->right, key, arr, index)) {
        arr[(*index)++] = root->data;
        return 1;
    }

    return 0;
}


void print_array(int arr[], int size) {
    for (int i = size - 1; i >= 0; i--) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void find_and_print_values(struct node* root, int key) {
    int arr[100];
    int index = 0;

    if (avl_find(root, key, arr, &index)) {
        print_array(arr, index);
    } else {
        printf("-1");
    }
}

void avl_preorder(struct node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        avl_preorder(root->left);
        avl_preorder(root->right);
    }
}

void avl_free(struct node* root) {
    if (root != NULL) {
        avl_free(root->left);
        avl_free(root->right);
        free(root);
    }
}

int main() {
 	struct node* root = NULL;
    char op;
    int key;
    
    int l = 0, r = 0; // Initialize l and r

    while (1) {
        scanf(" %c", &op); // added space before %c to consume newline character
        if (op == 'e')
            break;

        switch (op) {
            case 'i':
                scanf("%d", &key);
                root = avl_insert(root, key);
                break;
            case 'x':
                scanf("%d", &key);
                find_and_print_values(root, key);
                printf("\n");
                break;
            case 'p':
                avl_preorder(root);
                printf("\n");
                break;
            case 's':
                printf("%d %d\n", lr, rr); // removed unnecessary argument
                break;
        }
    }

    avl_free(root);

    return 0;
}

