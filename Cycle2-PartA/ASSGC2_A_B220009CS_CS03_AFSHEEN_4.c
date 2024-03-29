#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct rb_tree {
    int data;
    struct rb_tree *left;
    struct rb_tree *right;
    struct rb_tree *parent;
    char color;
};

typedef struct rb_tree *node;

node createNode(int key, char color) {
    node temp = (node)malloc(sizeof(struct rb_tree));
    if (temp == NULL) {
        printf("Error creating a new node.\n");
        exit(0);
    }

    temp->data = key;
    temp->right = NULL;
    temp->left = NULL;
    temp->parent = NULL;
    temp->color = color;
    return temp;
}
void preorder(node root)
{
    if(root!=NULL)
    {
        //if(root->color!='X')
        printf("%d %c ",root->data , root->color);
        preorder(root->left);
        preorder(root->right);
    }
}

node constructTree(char s[], int *index) {
    int n = 0;
    char c = 'X';
    if(s[*index]=='\0')
    {
        return NULL;
    }
    if (s[*index] != '\0' && s[*index] != ')' && s[*index]!='(' && s[*index]!=' ' ) {     //(10 R...)
        while (s[*index] >= '0' && s[*index] <= '9') {
            n = n * 10 + (s[*index] - '0');
            (*index)++;
        }
        c = s[++(*index)]; // Move index past the color
        //(*index)++; // Move index to next character
        *index = *index + 1;
        
    }
    node root = createNode(n, c);

    if (s[*index] == '(') {
        (*index)++;
        root -> left = constructTree(s, index);
        if (root -> left != NULL) {
            (root) -> left -> parent = root;
        }

        (*index)++;
        
        root -> right = constructTree(s, index);
        if (root -> right != NULL) {
            (root) -> right -> parent = root;
        }

        (*index)++;
    }
    else if (s[*index] == ')') {
        (*index)++;
    }
        
    return root;
}


int checkRedblackTree(node root, int count) {
    // if (root == NULL) {
    //     return 1;
    // }
    int left = 1;
    int right = 1;

    if (count == 0) {
        if (root->color != 'B') {
            return 0;
        }
    }

    if (root->color == 'R') {
        if ((root->left != NULL && root->left->color == 'R') ||
            (root->right != NULL && root->right->color == 'R')) {
            return 0;
        }
    }

    left = checkRedblackTree(root->left, 1);
    right = checkRedblackTree(root->right, 1);
    return left && right;
}

int blackdepthcheck(node root, int depth) {
    if (root == NULL) {
        return depth == 0;
    }
    if (root->color == 'B') {
        depth--;
    }
    return blackdepthcheck(root->left, depth) && blackdepthcheck(root->right, depth);
}

int bstcheck(node root) {
    int left = 1;
    int right = 1;
    if (root == NULL) {
        return 1;
    }
    if (root->left != NULL) {
        if (root->left->data > root->data) {
            return 0;
        }
    }
    if (root->right != NULL) {
        if (root->right->data < root->data) {
            return 0;
        }
    }
    left = bstcheck(root->left);
    right = bstcheck(root->right);
    return left && right;
}

int rbtreecheck(node root, int bd) {
    return bstcheck(root) && checkRedblackTree(root, 0) && blackdepthcheck(root, bd);
}

int main() {
    char s[1000];
    
    scanf("%[^\n]s", s);
    //char s[] = "(10 B (4 B (2 R ()())(5 R ()()))(15 B ()()))" ;

    int index = 0;
    node root = NULL;
    root = constructTree(s, &index);
    preorder(root);

    int bheight = 0;

    node boop = root;
    while (boop != NULL) {
        if (boop->color == 'B') {
            bheight++;
        }
        boop = boop->left;
    }

    printf("%d", rbtreecheck(root, bheight));



    return 0;
}
