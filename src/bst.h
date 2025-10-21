#ifndef BST_C
#define BST_C

typedef struct Node Node;
typedef struct Tree Tree;

//Lifecycle Functions
Tree* bst_create(void (*freeNode)(void* Node),
                  int (*compareNode)(Node* node1, Node* node2));

void bst_destroy(Tree* tree);

//Core Functions
void bst_insert(Tree* tree, void* data);
void bst_remove(Tree* tree, void* data);
void* bst_search(Tree* tree, void* data);

//Traversal Functions
void bst_traverse_inorder(Tree* tree, 
                          void (*op)(void* data, void* context), 
                          void* context);

void bst_traverse_preorder(Tree* tree, 
                           void (*op)(void* data, void* context), 
                           void* context);

void bst_traverse_postorder(Tree* tree,
                            void (*op)(void* data, void* context),
                            void* context);

//Utility Functions
void* get_data(Node* node); //Returns the data of the node
size_t bst_size(Tree* tree); //Returns number of nodes
void* bst_get_min(Tree* tree);
void* bst_get_max(Tree* tree);
int bst_get_height(Tree* tree); //Returns height of tree
int bst_isBalanced(Tree* tree);
void bst_print(Tree* tree);
void node_print_int(void* node, void* context); 

//Recursion Helpers
void bst_traverse_inorder_rec(Node* current_node, 
                              void (*op)(void* data, void* context), 
                              void* context);

void bst_traverse_preorder_rec(Node* current_node, 
                               void (*op)(void* data, void* context), 
                               void* context);

void bst_traverse_postorder_rec(Node* current_node,
                                void (*op)(void* data, void* context), 
                                void* context);

int bst_insert_rec(Node* current_node, void* data);

#endif