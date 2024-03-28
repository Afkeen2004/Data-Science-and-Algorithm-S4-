//ASSG1_B_B220009CS_CS03_AFSHEEN_1
//menu driven function call for a binary tree made from inorder and preorder

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//defining binary tree
struct btree {
    int val;
    struct btree* left;
    struct btree* right;
};

//create node function for binary tree
struct btree* create_node(int value) {
    struct btree* node = (struct btree*)malloc(sizeof(struct btree));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
     
    node->val = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

//building a binary tree
struct btree* build_tree(int inorder[], int preorder[], int start, int end, int* prein) {
    if (start > end) {
        return NULL;
    }

    struct btree* root = create_node(preorder[*prein]);

    int inin;
    for (inin = start; inin <= end; inin++) {
        if (inorder[inin] == root->val) {
            break;
        }
    }

    (*prein)++;
    
    root->left = build_tree(inorder, preorder, start, inin - 1, prein);
    root->right = build_tree(inorder, preorder, inin + 1, end, prein);

    return root;
}

//printing the postorder of the tree
void post_order(struct btree* root) {
    if (root == NULL) {
        return;
    }

    post_order(root->left);
    post_order(root->right);
    printf("%d ", root->val);
}

//printing the zigzag traversal of the tree
void zig_zag_traversal(struct btree* root) {
    if (root == NULL) {
        return;
    }

    struct btree* curlevel[2][100000];
    int curtop[2] = {-1, -1};
    int current = 0;
    struct btree* stack[2][100000];
    int top[2] = {-1, -1};

    curlevel[current][++curtop[current]] = root;

    while (curtop[current] != -1) {
        struct btree* node = curlevel[current][curtop[current]--];

        printf("%d ", node->val);

        if (current == 0) {
            if (node->left) curlevel[1][++curtop[1]] = node->left;
            if (node->right) curlevel[1][++curtop[1]] = node->right;
        } else {
            if (node->right) curlevel[0][++curtop[0]] = node->right;
            if (node->left) curlevel[0][++curtop[0]] = node->left;
        }

        if (curtop[current] == -1) {
            current = 1 - current;
        }
    }
}

//printing the max element for every level 
void level_max(struct btree* root) {
    if (root == NULL) {
        return;
    }

    struct btree* queue[100000];
    int front = -1, rear = -1;
    int level = 0;

    queue[++rear] = root;
    queue[++rear] = NULL;

    int maxAtLevel = INT_MIN;

    while (front != rear) {
        struct btree* node = queue[++front];

        if (node == NULL) {
            printf("%d ", maxAtLevel);
            maxAtLevel = INT_MIN;
            if (queue[front + 1] != NULL) {
                queue[++rear] = NULL;
            }
            continue;
        }

        if (node->val > maxAtLevel) {
            maxAtLevel = node->val;
        }

        if (node->left) {
            queue[++rear] = node->left;
        }
        if (node->right) {
            queue[++rear] = node->right;
        }
    }
}

//finding the height of binary tree
int height(struct btree* root) {
    if (root == NULL) {
        return 0;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return 1 + ((leftHeight > rightHeight) ? leftHeight : rightHeight);
}

//finding the diameter of the binary tree
int diameter(struct btree* root) {
    if (root == NULL) {
        return 0;
    }

    int rootDiameter = height(root->left) + height(root->right) + 1;
    int leftDiameter = diameter(root->left);
    int rightDiameter = diameter(root->right);

    return ((leftDiameter > rightDiameter) ? (leftDiameter > rootDiameter ? leftDiameter : rootDiameter)
                                           : (rightDiameter > rootDiameter ? rightDiameter : rootDiameter));
}

//calculating the sum of left leaf sum of the binary tree
int left_leaf_sum(struct btree* root) {
    if (root == NULL) {
        return 0;
    }

    if (root->left != NULL && root->left->left == NULL && root->left->right == NULL) {
        return root->left->val + left_leaf_sum(root->right);
    }

    return left_leaf_sum(root->left) + left_leaf_sum(root->right);
}

//main function with menu option
int main() {
    int n;
    scanf("%d", &n);

    int inorder[n], preorder[n];

    for (int i = 0; i < n; i++) {
        scanf("%d", &inorder[i]);
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &preorder[i]);
    }

    int prein = 0;
    struct btree* root = build_tree(inorder, preorder, 0, n - 1, &prein);

    char option;
    while (1) {
        scanf(" %c", &option);

        switch (option) {
            case 'p':
                post_order(root);
                printf("\n");
                break;
            case 'z':
                zig_zag_traversal(root);
                printf("\n");
                break;
            case 'm':
                level_max(root);
                printf("\n");
                break;
            case 'd':
                printf("%d\n", diameter(root));
                break;
            case 's':
                printf("%d\n", left_leaf_sum(root));
                break;
            case 'e':
                return 0;
            default:
                printf("Invalid option\n");
                break;
        }
    }
}

