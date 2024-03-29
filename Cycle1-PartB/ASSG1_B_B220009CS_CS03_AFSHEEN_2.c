//ASSG1_B_B220009CS_CS03_AFSHEEN_2
//menu driven function call for a binary tree made from parenthesis representation

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//defining binary tree
struct tnode {
    int key;
    struct tnode* left;
    struct tnode* right;
};

//building a binary tree
struct tnode* build_bt(char* s, int* index) {
    if (s[*index] == '\0' || s[*index] == ')') {
        (*index)++;
        return NULL;
    }

    struct tnode* new_node = (struct tnode*)malloc(sizeof(struct tnode));
    int num = 0;
    int sign = 1;

    if (s[*index] == '-') {
        sign = -1;
        (*index)++;
    }

    while (s[*index] >= '0' && s[*index] <= '9') {
        num = num * 10 + (s[*index] - '0');
        (*index)++;
    }

    new_node->key = sign * num;
    new_node->left = NULL;
    new_node->right = NULL;

    if (s[*index] == '(') {
        (*index)++;
        new_node->left = build_bt(s, index);
        (*index)++;
    }

    if (s[*index] == '(') {
        (*index)++;
        new_node->right = build_bt(s, index);
        (*index)++;
    }

    return new_node;
}

//level order traversal of binary tree
void level_Order_Traversal(struct tnode* root) {
    if (root == NULL) {
        return;
    }

    struct tnode* queue[10000];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        struct tnode* current = queue[front++];
        printf("%d ", current->key);

        if (current->left != NULL) {
            queue[rear++] = current->left;
        }

        if (current->right != NULL) {
            queue[rear++] = current->right;
        }
    }
}

//checking if the given binary tree is a BST or not
int is_BST(struct tnode* root, int min, int max) {
    if (root == NULL) {
        return 1;
    }

    if (root->key < min || root->key > max) {
        return 0;
    }

    return is_BST(root->left, min, root->key - 1) && is_BST(root->right, root->key + 1, max);
}

//calculating the sum of the BST
int max_sum_BST(struct tnode* root) {
    if (root == NULL) {
        return 0;
    }

    if (is_BST(root, INT_MIN, INT_MAX)) {
        int leftSum = max_sum_BST(root->left);
        int rightSum = max_sum_BST(root->right);
        return leftSum + rightSum + root->key;
    } else {
        int leftMaxSum = max_sum_BST(root->left);
        int rightMaxSum = max_sum_BST(root->right);
        return (leftMaxSum > rightMaxSum) ? leftMaxSum : rightMaxSum;
    }
}

//right view of a specific level
void right_view_level(struct tnode* root, int level, int* maxLevel) {
    if (root == NULL) {
        return;
    }

    if (level > *maxLevel) {
        printf("%d ", root->key);
        *maxLevel = level;
    }

    right_view_level(root->right, level + 1, maxLevel);
    right_view_level(root->left, level + 1, maxLevel);
}

//right view of binary tree
void right_view(struct tnode* root) {
    int maxLevel = 0;
    right_view_level(root, 1, &maxLevel);
}

int main() {
    char s[1000];
    scanf("%s", s);

    int index = 0;
    struct tnode* root = build_bt(s, &index);

    char command;
    while (1) {
        scanf(" %c", &command);
        if (command == 'e') {
            break;
        } else if (command == 'l') {
            level_Order_Traversal(root);
            printf("\n");
        } else if (command == 'm') {
            int maxSum = max_sum_BST(root);
            printf("%d\n", maxSum);
        } else if (command == 'r') {
            right_view(root);
            printf("\n");
        }
    }

    return 0;
}

