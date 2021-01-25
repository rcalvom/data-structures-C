#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "arraylist.h"

array_list_t* new_array_list() {
    array_list_t *list = (array_list_t*) malloc(sizeof(array_list_t));
    list->elements = (void**) malloc(INITIAL_CAPACITY * sizeof(void*));
    list->capacity = INITIAL_CAPACITY;
    list->size = 0;
    return list;
}

void* get(array_list_t *list, int index) {
    if (index < 0 || index > list->size - 1) {
        perror("Invalid index.\n");
        exit(EXIT_FAILURE);
    }
    return list->elements[index];
}

int find(array_list_t *list, void *element) {
    for (int i = 0; i < list->size; i++)
        if (list->elements[i] == element)
            return i;
    return -1;
}

void insert(array_list_t *list, int index, void *value) {
    if (index < 0 || index > list->size) {
        perror("Invalid index.\n");
        exit(EXIT_FAILURE);
    }
    if (list->size == list->capacity) {
        void **new_array = (void**) malloc(2 * list->capacity * sizeof(void*));
        for (int i = 0; i < list->size; i++) {
            new_array[i] = list->elements[i];
        }
        list->capacity *= 2;
        list->elements = new_array;
    }
    for (int i = list->size; i >= index; i--) {
        list->elements[i] = list->elements[i - 1];
    }
    list->elements[index] = value;
    list->size++;
}

void push_front(array_list_t *list, void *value) {
    insert(list, 0, value);
}

void push_back(array_list_t *list, void *value) {
    insert(list, list->size, value);
}

void remove(array_list_t *list, int index) {
    if (index < 0 || index > list->size - 1) {
        perror("Invalid index.\n");
        exit(EXIT_FAILURE);
    }
    if (list->size == 0) {
        perror("The list is empty.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = index; i < list->size; i++) {
        list->elements[i] = list->elements[i + 1];
    }
    list->size--;
}

void make_empty(array_list_t *list) {
    free(list->elements);
    list->elements = (void**) malloc(list->capacity * sizeof(void*));
    list->size = 0;
}

char* to_string(array_list_t *list) {
    char* result = (char*) malloc(MAX_TOSTRING * sizeof(char));
    char* node_str = (char*) malloc(MAX_STRING_VALUE * sizeof(char));
    if (result == NULL || node_str == NULL) {
        perror("Error in malloc.\n");
        exit(EXIT_FAILURE);
    }
    if (list->size == 0) {
        strcat(result, "[]\n");
    } else if (list->size == 1) {
        int value = *(int*) list->elements[0];
        sprintf(node_str, "%i", value);
        strcat(result, "[");
        strcat(result, node_str);
        strcat(result, "]");
    } else {
        strcat(result, "[");
        for (int i = 0; i < list->size; i++) {
            int value = *(int*) list->elements[i];
            sprintf(node_str, "%i", value);
            strcat(result, node_str);
            if (i != list->size - 1) {
                strcat(result, ", ");
            } else {
                strcat(result, "]\n");
            }
        }
    }
    return result;
}