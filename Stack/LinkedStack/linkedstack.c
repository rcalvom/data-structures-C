#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "linkedstack.h"

void push(linked_stack_t *stack, void *value){
    if(stack->size < 1){
        stack->top->value = value;
    }else{
        stack_node_t *node = (stack_node_t*) malloc(sizeof(stack_node_t));
        if(node == NULL){
            perror("Error in malloc.\n");
            exit(EXIT_FAILURE);
        }
        node->value = value;
        node->previous = stack->top;
        node->next = NULL;
        stack->top->next = node;
        stack->top = node;
    }
    stack->size++;
}

void* pop(linked_stack_t *stack){
    void *element = NULL;
    if(stack->size < 1){
        perror("Trying to pop an empty stack.\n");
        exit(EXIT_FAILURE);
    }else if(stack->size == 1){
        element = stack->top->value;
        stack->top->value = NULL;
    }else{
        stack_node_t *node = stack->top;
        stack->top = stack->top->previous;
        element = node->value;
        free(node);
    }
    stack->size--;
    return element;
}

void* peek(linked_stack_t *stack){
    if(stack->size == 0){
        perror("Trying to peek an empty stack.\n");
        exit(EXIT_FAILURE);
    }else{
        return stack->top->value;
    }
}

linked_stack_t* new_stack(){
    linked_stack_t *stack = (linked_stack_t*) malloc(sizeof(linked_stack_t));
    stack->top = (stack_node_t*) malloc(sizeof(stack_node_t));
    if(stack == NULL|| stack->top == NULL){
        perror("Error in malloc.\n");
        exit(EXIT_FAILURE);
    }
    stack->top->previous = NULL;
    stack->top->next = NULL;
    stack->size = 0;
    return stack;
}

void delete_stack(linked_stack_t *stack){
    stack_node_t *node1 = stack->top;
    stack_node_t *node2 = stack->top->next;
    while(node2 != NULL){
        free(node1);
        node1 = node2;
        node2 = node2->next;
    }
    free(node1);
    free(stack);
}

char* toString(linked_stack_t *stack){
    char* str = malloc(MAX_TOSTRING * sizeof(char));
    char* node_str = malloc(MAX_STRING_VALUE * sizeof(char));
    if(str == NULL || node_str == NULL){
        perror("Error in malloc.\n");
        exit(EXIT_FAILURE);
    }
    stack_node_t *node = stack->top;
    strcat(str, "[");
    for(int i = 1; i <= stack->size; i++){
        int node_value = *((int *)(node->value));
        sprintf(node_str, "%i", node_value);
        strcat(str, node_str);
        if(i != stack->size){
            strcat(str, ", ");
        }
        node = node->previous;

    }
    strcat(str, "]");
    free(node_str);
    return str;
}