#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "avltree.h"

int height(avl_tree_node_t* node){
    return node == NULL ? -1 : node->height;
}

float findMin(avl_tree_node_t *root){
    avl_tree_node_t* node = root;
    while(node->left != NULL){
        node = node->left;
    }
    return node->element;
}

avl_tree_node_t* rotateWithLeftChild(avl_tree_node_t* k2){
    avl_tree_node_t* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = (height(k2->left) > height(k2->right)) ? height(k2->left) + 1 : height(k2->right) + 1;
    k1->height = (height(k1->left) > height(k2)) ? height(k2->left) + 1 : height(k2) + 1;
    return k1;
}

avl_tree_node_t* rotateWithRightChild(avl_tree_node_t* k1){
    avl_tree_node_t* k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = (height(k1->left) > height(k1->right)) ? height(k1->left) + 1 : height(k1->right) + 1;
    k2->height = (height(k2->right) > height(k1)) ? height(k2->right) + 1 : height(k1) + 1;
    return k2;
}

avl_tree_node_t* doubleWithLeftChild(avl_tree_node_t* k3){
    k3->left = rotateWithRightChild(k3->left);
    return rotateWithLeftChild(k3);
}

avl_tree_node_t* doubleWithRightChild(avl_tree_node_t* k1){
    k1->right = rotateWithLeftChild(k1->right);
    return rotateWithRightChild(k1);
}

avl_tree_node_t* balance(avl_tree_node_t* node){
    if(node == NULL){
        return node;
    }
    if(height(node->left) - height(node->right) > ALLOWED_IMBALANCE){
        if(height(node->left->left) >= height(node->left->right)){
            node = rotateWithLeftChild(node);
        }else{
            node = doubleWithLeftChild(node);
        }
    }else if(height(node->right) - height(node->left) > ALLOWED_IMBALANCE){
        if(height(node->right->right) >= height(node->right->left)){
            node = rotateWithRightChild(node);
        }else{
            node = doubleWithRightChild(node);
        }
    }
    node->height = (height(node->left) > height(node->right)) ? height(node->left) + 1 : height(node->right) + 1;
    return node;
}

avl_tree_node_t* insert_element_r(avl_tree_node_t *node, float element){
    if(node == NULL){
        avl_tree_node_t *new_node = (avl_tree_node_t*) malloc(sizeof(avl_tree_node_t));
        if(new_node == NULL){
            perror("Error in malloc.\n");
            exit(EXIT_FAILURE);
        }
        new_node->element = element;
        new_node->height = 0;
        new_node->left = NULL;
        new_node->right = NULL;
        return new_node;
    }
    if(element < node->element){
        node->left = insert_element_r(node->left, element);
    }else if(element > node->element){
        node->right = insert_element_r(node->right, element);
    }else{
        ; // Valor duplicado.
    }
    return balance(node);
}

void insert_element(avl_tree_t *tree, float element){
    tree->root = insert_element_r(tree->root, element);
}

avl_tree_node_t* remove_element_r(avl_tree_node_t *node, avl_tree_node_t *root, float element){
    if(node == NULL){
        return node; // Elemento no encontrado.
    }
    if(element < node->element){
        node->left  = remove_element_r(node->left, root, element);
    }else if(element > node->element){
        node->right = remove_element_r(node->right, root, element);
    }else if(node->left != NULL && node->right != NULL){
        node->element = findMin(node->right);
        node->right = remove_element_r(node->right, root, node->element);
    }else{
        avl_tree_node_t *temp = node;
        node = (node->left != NULL) ? node->left : node->right;
        free(temp);
    }
    return balance(node);
}

void remove_element(avl_tree_t* tree, float element){
    tree->root = remove_element_r(tree->root, tree->root, element);
}

int contains_element_r(avl_tree_node_t* node, float element){
    avl_tree_node_t *temp = node;
    while(temp != NULL){
        if(element < temp->element){
            temp = temp->left;
        }else if(element > temp->element){
            temp = temp->right;
        }else{
            return 1;
        }
    }
    return 0;
}

int contains_element(avl_tree_t* tree, float element){
    return contains_element_r(tree->root, element);
}

avl_tree_t* new_avl_tree(){
    avl_tree_t *tree = (avl_tree_t*) malloc(sizeof(avl_tree_t));
    if(tree == NULL){
        perror("Error in malloc.\n");
        exit(EXIT_FAILURE);
    }
    return tree;
}

void delete_avl_tree_r(avl_tree_node_t *node){
    if(node->left == NULL && node->right == NULL){
        free(node);
        return;
    }
    if(node->left != NULL){
        delete_avl_tree_r(node->left);
    }
    if(node->right != NULL){
        delete_avl_tree_r(node->right);
    }

}

void delete_avl_tree(avl_tree_t* tree){
    if(tree->root == NULL){
        return;
    }
    delete_avl_tree_r(tree->root);
    free(tree);
    return;    
}

void toString_preorder_r(avl_tree_node_t *node, char *str){
    if(node == NULL){
        return;
    }
    char *node_str = (char*) malloc(MAX_STRING_VALUE * sizeof(char) + 1);
    if(node_str == NULL){
        perror("Error in malloc.\n");
        exit(EXIT_FAILURE);
    }
    sprintf(node_str, "%f", node->element);
    strcat(str, node_str);
    strcat(str, ", ");
    free(node_str);
    toString_preorder_r(node->left, str);
    toString_preorder_r(node->right, str);
    return;
}

char* toString_preorder(avl_tree_t* tree){
    char *str = (char*) malloc(MAX_TOSTRING * sizeof(char) + 1);
    if(str == NULL){
        perror("Error in malloc.\n");
        exit(EXIT_FAILURE);
    }
    strcat(str, "[");
    toString_preorder_r(tree->root, str);
    *(str + strlen(str) - 2) = ']';
    *(str + strlen(str) - 1) = '\0';
    return str;
}

void toString_inorder_r(avl_tree_node_t *node, char *str){
    if(node == NULL){
        return;
    }
    toString_inorder_r(node->left, str);
    char *node_str = (char*) malloc(MAX_STRING_VALUE * sizeof(char) + 1);
    if(node_str == NULL){
        perror("Error in malloc.\n");
        exit(EXIT_FAILURE);
    }
    sprintf(node_str, "%f", node->element);
    strcat(str, node_str);
    strcat(str, ", ");
    free(node_str);
    toString_inorder_r(node->right, str);
    return;
}

char* toString_inorder(avl_tree_t* tree){
    char *str = (char*) malloc(MAX_TOSTRING * sizeof(char) + 1);
    if(str == NULL){
        perror("Error in malloc.\n");
        exit(EXIT_FAILURE);
    }
    strcat(str, "[");
    toString_inorder_r(tree->root, str);
    *(str + strlen(str) - 2) = ']';
    *(str + strlen(str) - 1) = '\0';
    return str;
}

void toString_postorder_r(avl_tree_node_t *node, char *str){
    if(node == NULL){
        return;
    }
    toString_postorder_r(node->left, str);
    toString_postorder_r(node->right, str);
    char *node_str = (char*) malloc(MAX_STRING_VALUE * sizeof(char) + 2);
    if(node_str == NULL){
        perror("Error in malloc.\n");
        exit(EXIT_FAILURE);
    }
    sprintf(node_str, "%f", node->element);
    strcat(str, node_str);
    strcat(str, ", ");
    free(node_str);
    return;
}

char* toString_postorder(avl_tree_t* tree){
    char *str = (char*) malloc(MAX_TOSTRING * sizeof(char) + 1);
    if(str == NULL){
        perror("Error in malloc.\n");
        exit(EXIT_FAILURE);
    }
    strcat(str, "[");
    toString_postorder_r(tree->root, str);
    *(str + strlen(str) - 2) = ']';
    *(str + strlen(str) - 1) = '\0';
    return str;
}

/*int main(){
    avl_tree_t *tree = new_avl_tree();
    insert_element(tree, 1.0);
    insert_element(tree, 2.0);
    insert_element(tree, 3.0);
    insert_element(tree, 4.0);
    insert_element(tree, 5.0);
    insert_element(tree, 6.0);
    insert_element(tree, 7.0);
    insert_element(tree, 8.0);
    insert_element(tree, 9.0);
    insert_element(tree, 10.0);
    insert_element(tree, 11.0);
    insert_element(tree, 12.0);
    insert_element(tree, 13.0);
    insert_element(tree, 14.0);
    insert_element(tree, 15.0);

    printf("%i\n", contains_element(tree, 10.0));
    printf("%i\n", contains_element(tree, 16.0));

    remove_element(tree, 10.0);
    remove_element(tree, 4.0);

    printf("%i\n", contains_element(tree, 10.0));
    printf("%i\n", contains_element(tree, 3.0));

    printf("%s\n", toString_preorder(tree));
    printf("%s\n", toString_inorder(tree));
    printf("%s\n", toString_postorder(tree));

    delete_avl_tree(tree);
    return 0;
}*/

