//ASSG1_B_B220009CS_CS03_AFSHEEN_2
//menu driven function call for a binary tree made from parenthesis representation

#include <stdio.h>
#include <stdlib.h>

//defining binary tree
struct btNode {
    int data;
    struct btNode* left;
    struct btNode* right;
};

//create node func for binary tree
struct btNode* createbtNode(int data) {
    struct btNode* newbtNode = (struct btNode*)malloc(sizeof(struct btNode));
    newbtNode->data = data;
    newbtNode->left = newbtNode->right = NULL;
    return newbtNode;
}

//building a binary tree
struct btNode* buildBST(char representation[], int* index) {
    if (representation[*index] == '\0') {
        return NULL;
    }

    if (representation[*index] == '(') {
        (*index)++;
    }

    if (representation[*index] == ')') {
        (*index)++;
        return NULL;
    }

    int value = 0;
    int isNegative = 0;

    if (representation[*index] == '-') {
        isNegative = 1;
        (*index)++;
    }

    while (representation[*index] >= '0' && representation[*index] <= '9') {
        value = value * 10 + (representation[*index] - '0');
        (*index)++;
    }

    if (isNegative) {
        value = -value;
    }

    struct btNode* root = createbtNode(value);

    if (representation[*index] == '(') {
        (*index)++;
        root->left = buildBST(representation, index);
    }

    if (representation[*index] == '(') {
        (*index)++;
        root->right = buildBST(representation, index);
    }

    if (representation[*index] == ')') {
        (*index)++;
    }

    return root;
}


//print values from BST in the specified range
void Print_Range_Values(struct btNode* root, int k1, int k2) {
    if (root == NULL) {
        return;
    }

    Print_Range_Values(root->left, k1, k2);

    if (root->data >= k1 && root->data <= k2) {
        printf("%d ", root->data);
    }

    Print_Range_Values(root->right, k1, k2);
}

//print ancestors for given key from BSTss
int Ancestors(struct btNode* root, int key) {
    if (root == NULL) {
        return 0;
    }

    if (root->data == key) {
    }
    if (root->data > key) {
        Ancestors(root->left, key);
        printf("%d ", root->data);
    } else {
        Ancestors(root->right, key);
        printf("%d ", root->data);
    }

    return 0;
}

//main func
int main() {
    char representation[100];
    scanf("%s", representation);

    int index = 0;
    struct btNode* root = buildBST(representation, &index);

    char choice;
    do {
        scanf(" %c", &choice);

        if (choice == 'p') {
            int k1, k2;
            scanf("%d %d", &k1, &k2);
            Print_Range_Values(root, k1, k2);
            printf("\n");
        } else if (choice == 'a') {
            int key;
            scanf("%d", &key);
            Ancestors(root, key);
            printf("\n");
        } else if (choice == 'e') {
            break;
        } else {
            printf("Invalid choice. Please enter p, a, or e.\n");
        }
    } while (1);

    return 0;
}
