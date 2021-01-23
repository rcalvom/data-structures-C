typedef struct tree_node{
    struct tree_node* left;
    struct tree_node* right;
    float element;
    int height;
} avl_tree_node_t;

typedef struct avltree{
    avl_tree_node_t* root;
    int size;
} avl_tree_t;

#define ALLOWED_IMBALANCE 1
#define MAX_TOSTRING 1024
#define MAX_STRING_VALUE 32

void insert_element(avl_tree_t* tree, float element);
void remove_element(avl_tree_t* tree, float element);
int contains_element(avl_tree_t* tree, float element);
avl_tree_t* new_avl_tree();
void delete_avl_tree(avl_tree_t* tree);
char* toString_preorder(avl_tree_t* tree);
char* toString_inorder(avl_tree_t* tree);
char* toString_postorder(avl_tree_t* tree);
