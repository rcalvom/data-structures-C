#include <stdbool.h>

typedef struct node {
    int key;
    struct node *left_child;
    struct node *right_child;
    struct node *parent;
} node_t;

typedef struct bstree {
    struct node *root;
} bstree_t;

#define MAX_TOSTRING 1024
#define MAX_STRING_VALUE 32
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

bstree_t* new_bstree();
bool empty(node_t *tree);
void insert(bstree_t *tree, int key);
node_t* insert_am(node_t *tree, int key, node_t *parent);
void erase(bstree_t *tree, int key);
node_t* erase_am(node_t *tree, int key);
node_t* find_min(node_t *tree);
node_t* find_max(node_t *tree);
bool contains(node_t *tree, int key);
bool is_leaf(node_t *node);
node_t* find(node_t *tree, int key);
void make_empty(node_t *tree);
char* range_search(node_t *tree, int x, int y);
char* nearest_neighbors(node_t *tree, int key);
node_t* right_ancestor(node_t *node);
node_t* next(node_t *node);
int height(node_t *tree);
int size(node_t *tree);
void print_level_traversal(node_t *tree);
char* level_traversal(node_t *tree);
void print_in_order_traversal(node_t *tree);
char* in_order_traversal(node_t *tree, char *res, char *node_str);
void print_pre_order_traversal(node_t *tree);
char* pre_order_traversal(node_t *tree, char *res, char *node_str);
void print_post_order_traversal(node_t *tree);
char* post_order_traversal(node_t *tree, char *res, char *node_str);