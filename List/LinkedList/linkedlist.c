#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "linkedlist.h"

linked_list_t* new_linked_list() {
    linked_list_t *list = (linked_list_t*) malloc(sizeof(linked_list_t));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

bool empty(linked_list_t *list) {
    return list->size == 0;
}

void push_back(linked_list_t *list, void *key) {
    node_t *new_node = (node_t*) malloc(sizeof(node_t));
    if (new_node == NULL) {
        perror("Error in malloc.\n");
        exit(EXIT_FAILURE);
    }
    new_node->key = key;
    new_node->next = NULL;
    if (list->tail == NULL) {
        list->head = new_node;
        list->tail = new_node;
        new_node->prev = NULL;
    } else {
        list->tail->next = new_node;
        new_node->prev = list->tail;
        list->tail = new_node;
    }
    list->size++;
}

void* pop_back(linked_list_t *list) {
    if (list->head == NULL) {
        perror("List is empty.\n");
        return NULL;
    }
    void *key = list->tail->key;
    if (list->size == 1) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->tail = list->tail->prev;
        list->tail->next = NULL;
    }
    list->size--;
    return key;
}

void* top_back(linked_list_t *list) {
    return list->tail->key;
}

void push_front(linked_list_t *list, void *key) {
    node_t *new_node = (node_t*) malloc(sizeof(node_t));
    if (new_node == NULL) {
        perror("Error in malloc.\n");
        exit(EXIT_FAILURE);
    }
    new_node->key = key;
    new_node->prev = NULL;
    if (list->head == NULL) {
        new_node->next = NULL;
        list->head = new_node;
        list->tail = new_node;
    } else {
        list->head->prev = new_node;
        new_node->next = list->head;
        list->head = new_node;
    }
    list->size++;
}

void* pop_front(linked_list_t *list) {
    if (list->head == NULL) {
        perror("List is empty.\n");
        return NULL;
    }
    void *key = list->head->key;
    if (list->size == 1) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->head = list->head->next;
        list->head->prev = NULL;
    }
    list->size--;
    return key;
}

void* top_front(linked_list_t *list) {
    return list->head->key;
}

void insert_at(linked_list_t *list, int position, void *key) {
    if (position < 0 || position > list->size) {
        perror("Invalid position.\n");
        exit(EXIT_FAILURE);
    }
    if (position == 0) push_front(list, key);
    else if (position == list->size) push_back(list, key);
    else {
        node_t *current = list->head;
        for (int i = 1; i < position; i++) {
            current = current->next;
        }
        node_t *new_node = (node_t*) malloc(sizeof(node_t));
        new_node->key = key;
        new_node->prev = current;
        new_node->next = current->next;
        current->next->prev = new_node;
        current->next = new_node;
        list->size++;
    }
}

bool find(linked_list_t *list, void *key) {
    if (list->head == NULL)
        return false;
    node_t *current = list->head;
    while (current != NULL) {
        if (current->key == key)
            return true;
        current = current->next;
    }
    return false;
}

void erase(linked_list_t *list, void *key) {
    if (!find(list, key)) {
        perror("Key is not in the list.\n");
        return;
    }
    if (list->head->key == key) {
        list->head = list->head->next;
        list->head->prev = NULL;
        if (list->head == NULL)
            list->tail = NULL;
        return;
    }
    node_t *current = list->head;
    while (current->next->key != key) {
        current = current->next;
    }
    current->next = current->next->next;
    current->next->next->prev = current;
    list->size--;
}

int size(linked_list_t *list) {
    return list->size;
}

char* to_string(linked_list_t *list) {
    char* result = (char*) malloc(MAX_TOSTRING * sizeof(char));
    char* node_str = (char*) malloc(MAX_STRING_VALUE * sizeof(char));
    if (result == NULL || node_str == NULL) {
        perror("Error in malloc.\n");
        exit(EXIT_FAILURE);
    }
    if (list->head == NULL) {
        strcat(result, "[]\n");
    } else if (list->size == 1) {
        int value = *(int*) list->head->key;
        sprintf(node_str, "%i", value);
        strcat(result, "[");
        strcat(result, node_str);
        strcat(result, "]");
    } else {
        int value = *(int*) list->head->key;
        sprintf(node_str, "%i", value);
        strcat(result, "[");
        strcat(result, node_str);
        strcat(result, ", ");
        node_t *current = list->head->next;
        while (current->next != NULL) {
            value = *(int*) current->key;
            sprintf(node_str, "%i", value);
            strcat(result, node_str);
            strcat(result, ", ");
            current = current->next;
        }
        value = *(int*) list->tail->key;
        sprintf(node_str, "%i", value);
        strcat(result, node_str);
        strcat(result, "]\n");
    }
    return result;
}