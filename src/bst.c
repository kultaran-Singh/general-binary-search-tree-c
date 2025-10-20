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
    void   (*compareNode)(void* node1, void* node2);   //Function to compare two nodes
}Tree;

//Lifecycle Functions
Tree* tree_create(void (*freeNode)(void* Node),
                  void (*compareNode)(void* node1, void* node2)){

    Tree* tree = (Tree*)malloc(sizeof(Tree*));

    //Configuring tree
    tree->root        = calloc(1, sizeof(Node*));
    tree->size        = 0;
    tree->freeNode    = freeNode;
    tree->compareNode = compareNode;
    
    return  tree;
    
}