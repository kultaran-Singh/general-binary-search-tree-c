#include <stdio.h>
#include <stdlib.h>

#include "bst.h"


typedef struct Node{
    void* data;
    Node* left;
    Node* right;
}Node;

typedef struct Tree{
    Node*  root;
    size_t size;                                       //Number of nodes
    void   (*freeNode)(void* Node);                    //Function to free a node
    int    (*compareNode)(Node* node1, Node* node2);   //Function to compare two nodes
}Tree;

//Lifecycle Functions
Tree* bst_create(void (*freeNode)(void* Node),
                 int (*compareNode)(Node* node1, Node* node2)){

    Tree* tree = (Tree*)malloc(sizeof(Tree*));

    //Configuring tree
    tree->root        = calloc(1, sizeof(Node*));
    tree->size        = 0;
    tree->freeNode    = freeNode;
    tree->compareNode = compareNode;
    
    return  tree;
}

void bst_destroy(Tree* tree){
    //This function should free all nodes and free the data inside the node, set both the pointers to NULL,
    //then free the node, then free the tree and set the tree pointer to NULL
}
//Core Functions
void bst_insert(Tree* tree, void* data){
    
    //Creating a new node
    Node* new_node = calloc(1, sizeof(Node*));
    new_node->data = data;

    //If the tree is empty
    if(tree->root->data == NULL){
        tree->root = new_node;
        tree->root->left = NULL;
        tree->root->right = NULL;
        return;
    }
    //bst_insert_rec(tree, tree->root, data);
    return;
}

//Traversal Functions
void bst_traverse_inorder(Tree* tree, void (*op)(void* data, void* context), void* context){
    bst_traverse_inorder_rec(tree->root, op, context);
    return;
}

void bst_traverse_preorder(Tree* tree, void (*op)(void* data, void* context), void* context){
    bst_traverse_postorder_rec(tree->root, op, context);
    return;
}

void bst_traverse_postorder(Tree* tree, void (*op)(void* data, void* context), void* context){
    bst_traverse_postorder_rec(tree->root, op, context);
    return;
}

//Utility Functions
void bst_print(Tree* tree){
    bst_traverse_inorder(tree, node_print_int, NULL);
    return;
}

int bst_is_valid(Tree* tree){
    if(tree == NULL){
        return 2;
    }
    int checker = 0;
    int* checkPointer = &checker;
    bst_traverse_inorder(tree, bst_validate_node, checkPointer);
    return *checkPointer;
}
//Helper Functions
void* get_data(Node* node){
    return node->data;
}

void bst_validate_node(void* node, void* checkPointer){
    //If current node is balanced then returns 0, else returns 1
    if(node == NULL || checkPointer == NULL){
        printf("Invalid check");
        return;
    }
    Node* current_node = (Node*)node;
    int* checker = (int*)checkPointer;

    if(current_node->left != NULL && current_node->left->data >= current_node->data){
        *checker = 1;
        return;
    }
    if(current_node->right != NULL && current_node->right->data <= current_node->data){
        *checker = 1;
        return;
    }
    else{
        return;
    }
}

//Recursion Helpers
void bst_traverse_inorder_rec(Node* current_node, void (*op)(void* data, void* context), void* context){
    
    if(current_node == NULL || op == NULL)
        return;
    //Visit Left node
    if(current_node->left != NULL){
        bst_traverse_inorder_rec(current_node->left, op, context);
    }
    //Visit Root node
    if(context != NULL)
        op(current_node, context);
    if(context == NULL)
        op(current_node, NULL);
    //Visit Right node
    if(current_node->right != NULL){
        bst_traverse_inorder_rec(current_node->right, op, context);
    }
    return;
}

void bst_traverse_preorder_rec(Node* current_node, void (*op)(void* data, void* context), void* context){

    if(current_node == NULL || op == NULL)
        return;
    //Visit Root node
    if(context != NULL)
        op(current_node, context);
    if(context == NULL)
        op(current_node, NULL);
    //Visit Left node
    if(current_node->left != NULL){
        bst_traverse_inorder_rec(current_node->left, op, context);
    }
    //Visit Right node
    if(current_node->right != NULL){
        bst_traverse_inorder_rec(current_node->right, op, context);
    }
    return;
}

void bst_traverse_postorder_rec(Node* current_node, void (*op)(void* data, void* context), void* context){

    if(current_node == NULL || op == NULL)
        return;
    //Visit Right node
    if(current_node->right != NULL){
        bst_traverse_inorder_rec(current_node->right, op, context);
    }
    //Visit Left node
    if(current_node->left != NULL){
        bst_traverse_inorder_rec(current_node->left, op, context);
    }
    //Visit Root node
    if(context != NULL)
        op(current_node, context);
    if(context == NULL)
        op(current_node, NULL);
    
    return;
}

/*int bst_insert_rec(Tree* tree, Node* current_node, void* insertData){
    
    if(current_node->left == NULL && current_node->right == NULL){
        int* result_current = tree->compareNode(insertData, current_node->data);
    }
    void* left_node_value    = current_node->left->data;
    void* right_node_value   = current_node->right->data;

    result_left  = tree->compareNode(insertData, left_node_value);
    result_right = tree->compareNode(insertData, right_node_value);
    //IF insertData is less than left node data but more than curent node data,
    //IF insertData is more than current node data but less than right node data.

    switch(result_left){
        case 1: //If an equivalent node already exists, return 1
            return 1;
            break;
        case 2: //If data is more than the data of left_node
            break;
        case 3: //If data is less than the data of left_node
            bst_insert_rec(tree, current_node->left, insertData);
            break;
    }
    switch(result_right){
        case 1: //If an equivalent node already exists, return 1
            return 1;
            break;
        case 2: //If data is more than the data of right_node
            bst_inser_rec(tree, current_node->right, insertData);
            break;
        case 3: //If data is less than the data of right_node
            break;
    }
    return 0;
}*/
//DEMO
void node_print_int(void* node, void* context){
    Node* n = (Node*)node;
    int* node_data = (int*)n->data;
    printf("DATA = %d\n", *node_data);
}