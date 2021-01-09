#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "arrayqueue.h"

void enqueue(array_queue_t *queue, void *value){
    if((queue->rear + 1) % queue->capacity == queue->front){
        void **new_values = malloc(2 * queue->capacity * sizeof(void*));
        if(new_values == NULL){
            perror("Error in malloc.\n");
            exit(EXIT_FAILURE);
        }
        int start = (queue->front + 1) % queue->capacity;
        if(start < 2){
            for(int i = 0; i < queue->capacity - 1; i++){
                *(new_values + i) = *(queue->values + start + i);
            }
        }else{
            for(int i = 0; i < queue->capacity - start; i++){
                *(new_values + i) = *(queue->values + start + i);
            }
            for(int i = 0; i < queue->rear + 1; i++){
                *(new_values + queue->capacity - start + i) = queue->values + i;
            }
        }
        free(queue->values);
        queue->rear = queue->capacity - 2;
        queue->capacity *= 2;
        queue->front = queue->capacity - 1;
        queue->values = new_values;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    *(queue->values + queue->rear) = value;
    queue->size++;
}

void* dequeue(array_queue_t *queue){
    if(queue->size < 1){
        perror("Trying to dequeue an empty queue.\n");
        exit(EXIT_FAILURE);
    }
    queue->front = (queue->front + 1) % queue->capacity;
    void* element = *(queue->values + queue->front);
    *(queue->values + queue->front) = NULL;
    queue->size--;
    return element;
}

void* peek(array_queue_t *queue){
    if(queue->size < 1){
        perror("Trying to peek an empty queue.\n");
        exit(EXIT_FAILURE);
    }else{
        return *(queue->values + ((queue->front + 1) % queue->capacity));
    }
}

array_queue_t* new_queue(){
    array_queue_t *queue = (array_queue_t*) malloc(sizeof(array_queue_t));
    queue->values = malloc(INITIAL_CAPACITY * sizeof(void*));
    if(queue == NULL || queue->values == NULL){
        perror("Error in malloc.\n");
        exit(EXIT_FAILURE);
    }
    queue->front = 0;
    queue->rear = 0;
    queue->size = 0;
    queue->capacity = INITIAL_CAPACITY;
    return queue;
}

void delete_queue(array_queue_t *queue){
    free(queue->values);
    free(queue);
}

char* toString(array_queue_t *queue){
    char *str = malloc(MAX_TOSTRING * sizeof(char));
    char *node_str = malloc(MAX_STRING_VALUE * sizeof(char));
    if(str == NULL || node_str == NULL){
        perror("Error in malloc.\n");
        exit(EXIT_FAILURE);
    }
    strcat(str, "[");
    for(int i = 1; i <= queue->size; i++){
        int value = *((int*)*(queue->values + (queue->front + i) % queue->capacity));
        sprintf(node_str, "%i", value);
        strcat(str, node_str);
        if(i != queue->size){
            strcat(str, ", ");
        }
    }
    strcat(str, "]");
    return str;
}
