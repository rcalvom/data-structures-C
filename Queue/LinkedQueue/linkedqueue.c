#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "linkedqueue.h"

void enqueue(linked_queue_t *queue, void *value) {
    if(queue->size == 0){
        queue->tail->value = value;
    }else{
        queue->tail->next = (queue_node_t *) malloc(sizeof(queue_node_t));
        if(queue->tail->next == NULL){
            perror("Error in malloc.\n");
            exit(EXIT_FAILURE);
        }
        queue->tail = queue->tail->next;
        queue->tail->value = value;
        queue->tail->next = NULL;
    }
    queue->size++;
}

void* dequeue(linked_queue_t *queue) {
    void *val = NULL;
    if(queue->size < 1){
        perror("Trying to dequeue an empty queue.\n");
        exit(EXIT_FAILURE);
    }else if(queue->size == 1){
        val = queue->head->value;
        queue->head->value = NULL;
    }else{
        queue_node_t *node = queue->head;
        queue->head = queue->head->next;
        val = node->value;
        free(node);
    }
    queue->size--;
    return val;
}

void* peek(linked_queue_t *queue) {
    if(queue->size == 0){
        perror("Trying to peek an empty queue.\n");
        exit(EXIT_FAILURE);
    }else{
        return queue->head->value;
    }
}

linked_queue_t* new_queue(){
    linked_queue_t *queue = (linked_queue_t*) malloc(sizeof(linked_queue_t));
    queue->head = (queue_node_t *) malloc(sizeof(queue_node_t));
    if(queue == NULL|| queue->head == NULL){
        perror("Error in malloc.\n");
        exit(EXIT_FAILURE);
    }
    queue->tail = queue->head;
    queue->head->next = NULL;
    queue->tail->next = NULL;
    queue->size = 0;
    return queue;
}

void delete_queue(linked_queue_t *queue){
    queue_node_t *node1 = queue->head;
    queue_node_t *node2 = queue->head->next;
    while(node2 != NULL){
        free(node1);
        node1 = node2;
        node2 = node2->next;
    }
    free(queue);
}

char* toString(linked_queue_t *queue){
    char* str = malloc(MAX_TOSTRING * sizeof(char));
    strcat(str, "[");
    queue_node_t *node = queue->head;
    char* node_str = malloc(MAX_STRING_VALUE * sizeof(char));
    for(int i = 1; i <= queue->size; i++){
        int node_value = *((int *)(node->value));
        sprintf(node_str, "%i", node_value);
        strcat(str, node_str);
        if(i != queue->size){
            strcat(str, ", ");
        }
        node = node->next;
    }
    strcat(str, "]");
    free(node_str);
    return str;
}