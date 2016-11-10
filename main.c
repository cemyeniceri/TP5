//
// Created by Cem Yeniceri on 10/11/16.
//

#include<stdio.h>
#include<stdlib.h>

typedef struct treeNode{
    int data;
    struct treeNode *right;
    struct treeNode *left;
}TreeNode;

TreeNode *createEmptyTree(TreeNode *node, int data);
TreeNode *insert(TreeNode *rootNode, int data);
int getInput();
TreeNode *findMin(TreeNode *rootNode);
TreeNode *findMax(TreeNode *rootNode);
TreeNode *delete_data(TreeNode *rootNode, int data);
void preOrder(TreeNode *rootNode);
void postOrder(TreeNode *rootNode);
void inOrder(TreeNode *rootNode);

TreeNode *rootNode;

int main() {
    int choice;
    while (choice != 8) {


        printf("What would you like to do?\n");
        printf("1 - Insert something in the phonebook?\n");
        printf("2 - delete something from the phonebook?\n");
        printf("3 - Print out preorder ?\n");
        printf("4 - Print out postorder ?\n");
        printf("5 - Print out inorder ?\n");
        printf("6 - Return the max element selected?\n");
        printf("7 - Return the min element selected?\n");
        printf("8 - Nothing at all\n");
        printf("Enter 1 through 8: ");
        scanf("%d", &choice);


        switch (choice) {
            case 1:
                rootNode = insert(rootNode, getInput());
                break;
            case 2:
                rootNode = delete_data(rootNode, getInput());
                break;
            case 3:
                preOrder(rootNode);
                printf("\n");
                break;
            case 4:
                postOrder(rootNode);
                printf("\n");
                break;
            case 5:
                inOrder(rootNode);
                printf("\n");
                break;
            case 6:
                if(findMax(rootNode) == NULL)
                    printf("Tree is already empty");
                else
                    printf("%d\n", findMax(rootNode)->data);
                break;
            case 7:
                if(findMin(rootNode) == NULL)
                    printf("Tree is already empty");
                else
                    printf("%d\n", findMin(rootNode)->data);
                break;
            default:
                printf("\nThank you for using the phonebook\n");
                return 0;
        }
    }


    return 0;
}

TreeNode *createEmptyTree(TreeNode *node, int data){
    node = malloc(sizeof(TreeNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

TreeNode *insert(TreeNode *rootNode, int data){

    if (rootNode == NULL)
        return createEmptyTree(rootNode, data);
    else{
        if(rootNode->data > data)
            rootNode->left = insert(rootNode->left, data);
        else if(rootNode->data < data)
            rootNode->right = insert(rootNode->right, data);
        else
            printf("There is already that data in the tree \n");
        return rootNode;
    }
}

int getInput(){
    int data = 0;

    printf("Enter a number : \n");
    scanf("%d", &data);
    return data;
}

TreeNode *findMin(TreeNode *rootNode){
    if(rootNode == NULL || rootNode->left == NULL)
        return rootNode;
    else
        return findMin(rootNode->left);
}

TreeNode *findMax(TreeNode *rootNode){
    if(rootNode == NULL || rootNode->right == NULL)
        return rootNode;
    else
        return findMax(rootNode->right);
}

TreeNode *delete_data(TreeNode *rootNode, int data){
    if(rootNode == NULL){
        printf ("Tree is empty\n");
        return rootNode;
    }
    else if(rootNode->data > data)
        rootNode->left = delete_data(rootNode->left, data);
    else if(rootNode->data < data)
        rootNode->right = delete_data(rootNode->left, data);
    else{
        // node with only one child or no child
        if (rootNode->left == NULL)
        {
            TreeNode *temp = rootNode->right;
            free(rootNode);
            return temp;
        }
        else if (rootNode->right == NULL)
        {
            TreeNode *temp = rootNode->left;
            free(rootNode);
            return temp;
        }

        // node with two children: Get the inorder successor (smallest
        // in the right subtree)
        TreeNode *temp = findMin(rootNode->right);

        // Copy the inorder successor's content to this node
        rootNode->data = temp->data;

        // Delete the inorder successor
        rootNode->right = delete_data(rootNode->right, temp->data);
    }
    return rootNode;
}

void inOrder(TreeNode *rootNode)
{
    if (rootNode != NULL)
    {
        inOrder(rootNode->left);
        printf("%d ", rootNode->data);
        inOrder(rootNode->right);
    }
}

void postOrder(TreeNode *rootNode)
{
    if (rootNode != NULL)
    {
        postOrder(rootNode->left);
        postOrder(rootNode->right);
        printf("%d ", rootNode->data);
    }
}
void preOrder(TreeNode *rootNode)
{
    if (rootNode != NULL)
    {
        printf("%d ", rootNode->data);
        preOrder(rootNode->left);
        preOrder(rootNode->right);
    }
}