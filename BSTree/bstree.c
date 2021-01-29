#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "bstree.h"

// TODO: finish nearest_neightbors and level_traversal methods

bstree_t* new_bstree() {
    bstree_t *tree = (bstree_t*) malloc(sizeof(bstree_t));
    tree->root = NULL;
    return tree;
}

bool empty(node_t *tree) {
    return tree == NULL;
}

void insert(bstree_t *tree, int key) {
    tree->root = insert_am(tree->root, key, NULL);
}

node_t* insert_am(node_t *tree, int key, node_t *parent) {
    if (tree == NULL) {
        node_t *new_node = (node_t*) malloc(sizeof(node_t));
        new_node->key = key;
        new_node->left_child = NULL;
        new_node->right_child = NULL;
        new_node->parent = parent;
        return new_node;
    }
    if (key < tree->key) {
        tree->left_child = insert_am(tree->left_child, key, tree);
    }
    if (key > tree->key) {
        tree->right_child = insert_am(tree->right_child, key, tree);
    }
    return tree;
}

void erase(bstree_t *tree, int key) {
    tree->root = erase_am(tree->root, key);
}

node_t* erase_am(node_t *tree, int key) {
    if (tree == NULL)
        return tree;
    if (key < tree->key) {
        tree->left_child = erase_am(tree->left_child, key);
    } else if (key > tree->key) {
        tree->right_child = erase_am(tree->right_child, key);
    } else {
        if (tree->left_child != NULL && tree->right_child != NULL) {
            node_t *node = find_min(tree->right_child);
            tree->key = node->key;
            tree->right_child = erase_am(tree->right_child, tree->key);
        } else if (tree->left_child != NULL) {
            tree = tree->left_child;
        } else {
            tree = tree->right_child;
        }
    }
    return tree;
}

node_t* find_min(node_t *tree) {
    if (tree->left_child == NULL)
        return tree;
    return find_min(tree->left_child);
}

node_t* find_max(node_t *tree) {
    if (tree->right_child == NULL)
        return tree;
    return find_max(tree->right_child);
}

bool contains(node_t *tree, int key) {
    if (tree == NULL) return false;
    if (tree->key == key) {
        return true;
    } else if (key < tree->key) {
        return contains(tree->left_child, key);
    } else if (key > tree->key) {
        return contains(tree->right_child, key);
    }
    return false;
}

bool is_leaf(node_t *node) {
    return node->left_child == NULL && node->right_child == NULL;
}

node_t* find(node_t *tree, int key) {
    if (tree->key == key) {
        return tree;
    } else if (key < tree->key && tree->left_child != NULL) {
        return find(tree->left_child, key);
    } else if (tree->right_child != NULL) {
        return find(tree->right_child, key);
    }
    return tree;
}

void make_empty(node_t *tree) {
    tree == NULL;
}

char* range_search(node_t *tree, int x, int y) {
    if (empty(tree)) return "[]";
    char* result = (char*) malloc(MAX_TOSTRING * sizeof(char));
    char* node_str = (char*) malloc(MAX_STRING_VALUE * sizeof(char));
    node_t* current = find(tree, x);
    while (current->key <= y) {
        if (current->key >= x) {
            sprintf(node_str, "%i", current->key);
            strcat(result, node_str);
            strcat(result, " ");
        }
        current = next(current);
        if (current == NULL)
            break;
    }
    strcat(result, "\n");
    return result;
}

char* nearest_neightboors(node_t *tree, int key) {
    node_t* node = find(tree, key);
    char* result = (char*) malloc(MAX_TOSTRING * sizeof(char));
    char* node_str = (char*) malloc(MAX_STRING_VALUE * sizeof(char));
    if (node->key == key) {
        if (!is_leaf(node)) {
            sprintf(node_str, "%i", find_max(node->left_child)->key);
            strcat(result, node_str);
            strcat(result, " ");
            node_t* a = next(node);
            if (a != NULL) {
                sprintf(node_str, "%i", a->key);
                strcat(result, node_str);
            }
        } else {
            return "Missing.\n";
        }
    } else {
        if (node->key < key) {
            sprintf(node_str, "%i", node->key);
            strcat(result, node_str);
            node_t* a = next(node);
            if (a != NULL) {
                sprintf(node_str, "%i", a->key);
                strcat(result, node_str);
            }
        } else {
            sprintf(node_str, "%i", node->parent->key);
            strcat(result, node_str);
            sprintf(node_str, "%i", node->key);
            strcat(result, node_str);
        }
    }
    strcat(result, "\n");
    return result;
}

node_t* right_ancestor(node_t *node) {
    if (node->parent == NULL)
        return NULL;
    if (node->key < node->parent->key)
        return node->parent;
    return right_ancestor(node->parent);
}

node_t* next(node_t *node) {
    if (node->right_child != NULL)
        return find_min(node->right_child);
    return right_ancestor(node);
}

int height(node_t *tree) {
    if (tree == NULL)
        return 0;
    return 1 + MAX(height(tree->left_child), height(tree->right_child));
}

int size(node_t *tree) {
    if (tree == NULL)
        return 0;
    return 1 + size(tree->left_child) + size(tree->right_child);
}

/*void print_level_traversal(node_t *tree) {
    printf(level_traversal(tree));
}

char* level_traversal(node_t *tree) {
    if (tree == NULL) return "";
    char* result = (char*) malloc(MAX_TOSTRING * sizeof(char));
    char* node_str = (char*) malloc(MAX_STRING_VALUE * sizeof(char));
    linked_queue_t* queue = new_queue();
    enqueue(queue, tree);
    while (queue->size > 0) {
        node_t* node = dequeue(queue);
        sprintf(node_str, "%i", node->key);
        strcat(result, node_str);
        strcat(result, " ");
        if (node->left_child != NULL) {
            enqueue(queue, node->left_child);
        }
        if (node->right_child != NULL) {
            enqueue(queue, node->right_child);
        }
    }
    strcat(result, "\n");
    return result;
}*/

void print_in_order_traversal(node_t *tree) {
    char* result = (char*) malloc(MAX_TOSTRING * sizeof(char));
    char* node_str = (char*) malloc(MAX_STRING_VALUE * sizeof(char));
    result = in_order_traversal(tree, result, node_str);
    strcat(result, "\n");
    printf(result);
}

char* in_order_traversal(node_t *tree, char *res, char *node_str) {
    if (tree == NULL)
        return res;
    res = in_order_traversal(tree->left_child, res, node_str);
    sprintf(node_str, "%i", tree->key);
    strcat(res, node_str);
    strcat(res, " ");
    res = in_order_traversal(tree->right_child, res, node_str);
    return res;
}

void print_pre_order_traversal(node_t *tree) {
    char* result = (char*) malloc(MAX_TOSTRING * sizeof(char));
    char* node_str = (char*) malloc(MAX_STRING_VALUE * sizeof(char));
    result = pre_order_traversal(tree, result, node_str);
    strcat(result, "\n");
    printf(result);
}

char* pre_order_traversal(node_t *tree, char *res, char *node_str) {
    if (tree == NULL)
        return res;
    sprintf(node_str, "%i", tree->key);
    strcat(res, node_str);
    strcat(res, " ");
    res = pre_order_traversal(tree->left_child, res, node_str);
    res = pre_order_traversal(tree->right_child, res, node_str);
    return res;
}

void print_post_order_traversal(node_t *tree) {
    char* result = (char*) malloc(MAX_TOSTRING * sizeof(char));
    char* node_str = (char*) malloc(MAX_STRING_VALUE * sizeof(char));
    result = post_order_traversal(tree, result, node_str);
    strcat(result, "\n");
    printf(result);
}

char* post_order_traversal(node_t *tree, char *res, char *node_str) {
    if (tree == NULL)
        return res;
    res = post_order_traversal(tree->left_child, res, node_str);
    res = post_order_traversal(tree->right_child, res, node_str);
    sprintf(node_str, "%i", tree->key);
    strcat(res, node_str);
    strcat(res, " ");
    return res;
}

int main() {
    bstree_t* tree = new_bstree();
    if (empty(tree->root)) printf("Empty\n");
    insert(tree, 20);
    insert(tree, 10);
    insert(tree, 26);
    insert(tree, 5);
    insert(tree, 17);
    insert(tree, 41);
    insert(tree, 22);
    insert(tree, 23);
    insert(tree, 15);
    if (empty(tree->root)) printf("Empty\n");
    print_in_order_traversal(tree->root);
    erase(tree, 26);
    print_in_order_traversal(tree->root);
    printf("%d\n", find_min(tree->root)->key);
    printf("%d\n", find_max(tree->root)->key);
    if (contains(tree->root, 41)) printf("41 exists\n");
    node_t *node = find(tree->root, 15);
    if (node != NULL) printf("15 found\n");
    if (is_leaf(tree->root)) printf("Root is leaf\n");
    if (is_leaf(node)) printf("15 is leaf\n");
    printf(range_search(tree->root, 16, 28));
    printf(nearest_neightboors(tree->root, 20));
    printf("%d\n", height(tree->root));
    printf("%d\n", size(tree->root));
    return 0;
}