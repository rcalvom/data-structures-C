#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "arraystack.h"

void push(array_stack_t *stack, void *value){
    if(stack->top == stack->capacity - 1){
        void **new_values = malloc(2 * stack->capacity * sizeof(void*));
        if(new_values == NULL){
            perror("Error in malloc.\n");
            exit(EXIT_FAILURE);
        }
        for(int i = 0; i < stack->capacity; i++){
            *(new_values + i) = *(stack->values + i);
        }
        free(stack->values);
        stack->values = new_values;
    }
    stack->top++;
    *(stack->values + stack->top) = value;
    stack->size++;
}

void* pop(array_stack_t *stack){
    if(stack->size < 1){
        perror("Trying to pop an empty stack.\n");
        exit(EXIT_FAILURE);
    }
    void* element = *(stack->values + stack->top);
    *(stack->values + stack->top) = NULL;
    stack->top--;
    stack->size--;
    return element;
}

void* peek(array_stack_t *stack){
    if(stack->size < 1){
        perror("Trying to peek an empty stack.\n");
        exit(EXIT_FAILURE);
    }else{
        return *(stack->values + stack->top);
    }
}

array_stack_t* new_stack(){
    array_stack_t *stack = (array_stack_t*) malloc(sizeof(array_stack_t));
    stack->values = malloc(INITIAL_CAPACITY * sizeof(void*));
    if(stack == NULL || stack->values == NULL){
        perror("Error in malloc.\n");
        exit(EXIT_FAILURE);
    }
    stack->top = 0;
    stack->size = 0;
    stack->capacity = INITIAL_CAPACITY;
    return stack;
}

void delete_stack(array_stack_t *stack){
    free(stack->values);
    free(stack);
}

char* toString(array_stack_t *stack){
    char *str = malloc(MAX_TOSTRING * sizeof(char));
    char *node_str = malloc(MAX_STRING_VALUE * sizeof(char));
    if(str == NULL || node_str == NULL){
        perror("Error in malloc.\n");
        exit(EXIT_FAILURE);
    }
    strcat(str, "[");
    for(int i = 1; i <= stack->size; i++){
        int value = *((int*)*(stack->values + stack->top - i));
        sprintf(node_str, "%i", value);
        strcat(str, node_str);
        if(i != stack->size){
            strcat(str, ", ");
        }
    }
    strcat(str, "]");
    return str;
}