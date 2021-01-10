#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "arraylist.h"

array_list_t* new_array_list() {
    array_list_t *list = (array_list_t*) malloc(sizeof(array_list_t));
    list->elements = malloc(INITIAL_CAPACITY * sizeof(void*));
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
        void **new_array = malloc(2 * list->capacity * sizeof(void*));
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

void delete(array_list_t *list, int index) {
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
    list->elements = malloc(list->capacity * sizeof(void*));
    list->size = 0;
}

char* to_string(array_list_t *list) {
    return NULL;
}

void print_list(array_list_t *list) {
    if (list->size == 0) {
        printf("[]\n");
        return;
    }
    if (list->size == 1) {
        printf("[%d]", *(int*) list->elements[0]);
        return;
    }
    for (int i = 0; i < list->size; i++) {
        if (i == 0) printf("[%d, ", *(int*) list->elements[i]);
        else if (i == list->size - 1) printf("%d]\n", *(int*) list->elements[i]);
        else printf("%d, ", *(int*) list->elements[i]);
    }
}