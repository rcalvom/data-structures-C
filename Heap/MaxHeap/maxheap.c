#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "maxheap.h"

void enqueue(max_heap_t* heap, float element){
    if(heap->size + 1 == heap->capacity){
        float *new_values = (float*) malloc(2 * heap->capacity * sizeof(float));
        if(new_values == NULL){
            perror("Error in malloc.\n");
            exit(EXIT_FAILURE);
        }
        for(int i = 1; i <= heap->size; i++){
            *(new_values + i) = *(heap->values + i);
        }
        free(heap->values);
        heap->values = new_values;
        heap->capacity *= 2;
    }
    if(heap->size == 0){
        *(heap->values + 1) = element;
    }else{
        *(heap->values + heap->size + 1) = element;
        int index = heap->size + 1;
        while(*(heap->values + index / 2) < *(heap->values + index) && index > 1){
            float temp = *(heap->values + index / 2);
            *(heap->values + index / 2) = *(heap->values + index);
            *(heap->values + index) = temp;            
            index /= 2;
        }
    }
    heap->size++;
}

float dequeue(max_heap_t* heap){
    float element = *(heap->values + 1);
    *(heap->values + 1) = *(heap->values + heap->size);
    int index = 1;
    while(2 * index + 1 < heap->size){
        if(*(heap->values + index) < *(heap->values + 2 * index) || *(heap->values + index) < *(heap->values + 2 * index + 1)){
            if(*(heap->values + 2 * index) > *(heap->values + 2 * index + 1)){
                float temp = *(heap->values + index);
                *(heap->values + index) = *(heap->values + 2 * index);
                *(heap->values + 2 * index) = temp;
                index = 2 * index;
            }else{
                float temp = *(heap->values + index);
                *(heap->values + index) = *(heap->values + 2 * index + 1);
                *(heap->values + 2 * index + 1) = temp;
                index = 2 * index + 1;
            }
        }
    }
    heap->size--;
    return element;
}

float peek(max_heap_t* heap){
    return *(heap->values + 1);
}

max_heap_t* new_max_heap(){
    max_heap_t *heap = (max_heap_t*) malloc(sizeof(max_heap_t));
    heap->values = (float*) malloc(INITIAL_CAPACITY * sizeof(float));
    if(heap == NULL || heap->values == NULL){
        perror("Error in malloc.\n");
        exit(EXIT_FAILURE);
    }    
    heap->size = 0;
    heap->capacity = INITIAL_CAPACITY;
    return heap;
}

void delete_max_heap(max_heap_t* heap){
    free(heap->values);
    free(heap);
}

char* toString(max_heap_t* heap){
    char *str = (char*) malloc(MAX_TOSTRING * sizeof(char) + 1);
    char *node_str = (char*) malloc(MAX_STRING_VALUE * sizeof(char) + 2);
    if(str == NULL || node_str == NULL){
        perror("Error in malloc.\n");
        exit(EXIT_FAILURE);
    }
    strcat(str, "[");
    for(int i = 1; i <= heap->size; i++){
        sprintf(node_str, "%f", *(heap->values + i));
        strcat(str, node_str);
        if(i != heap->size){
            strcat(str, ", ");
        }
    }
    strcat(str, "]");
    free(node_str);
    return str;
}

int main(){
    max_heap_t *heap = new_max_heap();

    for(int i = 1; i <= 10; i++){
        enqueue(heap, (float)i);
    }

    printf("%s\n", toString(heap));

    printf("%f\n", dequeue(heap));

    printf("%s\n", toString(heap));

    printf("%f\n", dequeue(heap));

    printf("%s\n", toString(heap));

    printf("%f\n", dequeue(heap));

    printf("%s\n", toString(heap));

    delete_max_heap(heap);

    return 0;

}