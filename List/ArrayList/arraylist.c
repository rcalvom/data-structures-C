#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "arraylist.h"

int get(array_list_t *list, int index) {
    if (index < 0 || index > list->size - 1) {
        perror("Invalid index.\n");
        exit(EXIT_FAILURE);
    }
    return list->elements[index];
}

int find(array_list_t *list, int element) {
    for (int i = 0; i < list->size; i++)
        if (list->elements[i] == element)
            return i;
    return -1;
}

void insert(array_list_t *list, int index, int value) {
    if (index < 0 || index > list->size) {
        perror("Invalid index.\n");
        exit(EXIT_FAILURE);
    }
    if (list->size == list->capacity) {
        int *new_array = malloc(2 * list->capacity * sizeof(int));
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
    list->elements = malloc(list->capacity * sizeof(int));
    list->size = 0;
}

void print_list(array_list_t *list) {
    if (list->size == 0) {
        printf("[]\n");
        return;
    }
    if (list->size == 1) {
        printf("[%d]", list->elements[0]);
        return;
    }
    for (int i = 0; i < list->size; i++) {
        if (i == 0) printf("[%d, ", list->elements[i]);
        else if (i == list->size - 1) printf("%d]\n", list->elements[i]);
        else printf("%d, ", list->elements[i]);
    }
}