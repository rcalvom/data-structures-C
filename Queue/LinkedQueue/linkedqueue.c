#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "linkedqueue.h"

void enqueue(queue_t *queue, float val) {
    if(queue->size == 0){
        queue->tail->val = val;
    }else{
        queue->tail->next = (node_t *) malloc(sizeof(node_t));
        if(queue->tail->next == NULL){
            perror("Error in malloc.\n");
            exit(EXIT_FAILURE);
        }
        queue->tail = queue->tail->next;
        queue->tail->val = val;
        queue->tail->next = NULL;
    }
    queue->size++;
}

float dequeue(queue_t *queue) {
    float val = 0.0f;
    if(queue->size < 1){
        perror("Trying to dequeue an empty queue.\n");
        exit(EXIT_FAILURE);
    }else if(queue->size == 1){
        val = queue->head->val;
        queue->head->val = 0.0f;
    }else{
        node_t *node = queue->head;
        queue->head = queue->head->next;
        val = node->val;
        free(node);
    }
    queue->size--;
    return val;
}

float peek(queue_t *queue) {
    if(queue->size == 0){
        perror("Trying to peek an empty queue.\n");
        exit(EXIT_FAILURE);
    }else{
        return queue->head->val;
    }
}

queue_t* new_queue(){
    queue_t *queue = (queue_t*) malloc(sizeof(queue_t));
    queue->head = (node_t *) malloc(sizeof(node_t));
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

void delete_queue(queue_t *queue){
    node_t *node1 = queue->head;
    node_t *node2 = queue->head->next;
    while(node2 != NULL){
        free(node1);
        node1 = node2;
        node2 = node2->next;
    }
    free(queue);
}