#ifndef BST_C
#define BST_C

typedef struct Node Node;
typedef struct Tree Tree;

//Lifecycle Functions
Tree* tree_create(void (*freeNode)(void* Node),
                  void (*compareNode)(void* node1, void* node2));

void tree_destroy(Tree* tree);

//Insertion
void tree_insert(Tree* tree, void* data);

//Deletion
void tree_remove(Tree* tree, void* data);

//Helper Functions
void* get_data(Node* node); //Returns the data of the node
void tree_print(Tree* tree); 

#endif