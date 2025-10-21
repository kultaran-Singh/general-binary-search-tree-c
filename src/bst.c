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
    
    //If the tree is empty
    Node* new_node = node_create(data);
    if(tree->root->data == NULL){
        tree->root = new_node;
        tree->size++;
        return;
    }
    if((tree->compareNode(tree->root, new_node) == 1)){
        printf("Node Already Exists");
        return;
    }
        
    bst_insert_rec(tree, tree->root, new_node);
    tree->size++;
    return;
}

//Traversal Functions
void bst_traverse_inorder(Tree* tree, void (*op)(Node* data, void* context), void* context){
    bst_traverse_inorder_rec(tree->root, op, context);
    return;
}

void bst_traverse_preorder(Tree* tree, void (*op)(Node* data, void* context), void* context){
    bst_traverse_preorder_rec(tree->root, op, context);
    return;
}

void bst_traverse_postorder(Tree* tree, void (*op)(Node* data, void* context), void* context){
    bst_traverse_postorder_rec(tree->root, op, context);
    return;
}

//Utility Functions
void bst_print(Tree* tree){
    printf("Preorder:\n");
    bst_traverse_preorder(tree, node_print_int, NULL);
    printf("--------------\n");
    printf("Inorder:\n");
    bst_traverse_inorder(tree, node_print_int, NULL);
    printf("--------------\n");
    printf("Postorder:\n");
    bst_traverse_postorder(tree, node_print_int, NULL);
    printf("--------------\n");
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

size_t bst_size(Tree* tree){
    return tree->size;
}
//Helper Functions
void* get_data(Node* node){
    return node->data;
}

void bst_validate_node(Node* node, void* checkPointer){
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
void bst_traverse_inorder_rec(Node* current_node, void (*op)(Node* node, void* context), void* context){
    
    if(current_node == NULL || op == NULL)
        return;
    //Visit Left node
    bst_traverse_inorder_rec(current_node->left, op, context);
    //Visit Root node
    if(context == NULL){
        op(current_node, NULL);
    }
    else{
        op(current_node, context);
    }
    //Visit Right node
    bst_traverse_inorder_rec(current_node->right, op, context);
    return;
}

void bst_traverse_preorder_rec(Node* current_node, void (*op)(Node* node, void* context), void* context){

    if(current_node == NULL || op == NULL)
        return;
    //Visit Root node
    if(context == NULL){
        op(current_node, NULL);
    }
    else{
        op(current_node, context);
    }
    
    //Visit Left node
    bst_traverse_preorder_rec(current_node->left, op, context);
    //Visit Right node
    bst_traverse_preorder_rec(current_node->right, op, context);
    return;
}

void bst_traverse_postorder_rec(Node* current_node, void (*op)(Node* node, void* context), void* context){

    if(current_node == NULL || op == NULL)
        return;
    //Visit Left node
    bst_traverse_postorder_rec(current_node->left, op, context);
    //Visit Right node
    bst_traverse_postorder_rec(current_node->right, op, context);
    //Visit Root node
    if(context == NULL){
        op(current_node, NULL);
    }
    else{
        op(current_node, context);
    }
    return;
}

void bst_insert_rec(Tree* tree, Node* current_node, Node* new_node){
    
    int result = tree->compareNode(new_node, current_node);
    
    switch(result){
        case 1: //Equivalent Node Found
            printf("Node already exists");
            if(tree->freeNode != NULL)
                tree->freeNode(new_node);
            free(new_node);
            return;
        case 2: //If data > current_node->data
            if(current_node->right != NULL){
                bst_insert_rec(tree, current_node->right, new_node);
                return;
            }
            current_node->right = new_node;
            return;
        case 3: //If data < current_node->data
            if(current_node->left != NULL){
                bst_insert_rec(tree, current_node->left, new_node);
                return;
            }
            current_node->left = new_node;
            return;
    }
    return;
}

Node* node_create(void* data){
    Node* new_node = calloc(1, sizeof(Node*));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}
//DEMO
void node_print_int(Node* node, void* context){
    int* node_data = (int*)node->data;
    printf("DATA = %d\n", *node_data);
    if(node->left != NULL){
        printf("left exists\n");
    }
    if(node->right != NULL){
        printf("right exists\n");
    }
    return;
}
