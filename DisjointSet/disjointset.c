#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "disjointset.h"

disjoint_set_t* new_disjoint_set(int size) {
    disjoint_set_t* dsu = (disjoint_set_t*) malloc(sizeof(disjoint_set_t));
    if (dsu == NULL) {
        perror("Error in malloc.\n");
        exit(EXIT_FAILURE);
    }
    dsu->parent = (int*) malloc(size * sizeof(int));
    dsu->rank = (int*) malloc(size * sizeof(int));
    if (dsu->parent == NULL || dsu->rank == NULL) {
        perror("Error in malloc.\n");
        exit(EXIT_FAILURE);
    }
    dsu->size = size;
    return dsu;
}

void make_set(disjoint_set_t* dsu, int i) {
    if (i < 0 || i >= dsu->size) {
        perror("Invalid index.\n");
        exit(EXIT_FAILURE);
    }
    dsu->parent[i] = i;
    dsu->rank[i] = 0;
}

int find(disjoint_set_t* dsu, int i) {
    if (i < 0 || i >= dsu->size) {
        perror("Invalid index.\n");
        exit(EXIT_FAILURE);
    }
    if (i != dsu->parent[i])
        dsu->parent[i] = find(dsu, dsu->parent[i]);
    return dsu->parent[i];
}

void merge(disjoint_set_t* dsu, int i, int j) {
    int i_id = find(dsu, i);
    int j_id = find(dsu, j);
    if (i_id == j_id) return;
    if (dsu->rank[i_id] > dsu->rank[j_id]) {
        dsu->parent[j_id] = i_id;
    } else {
        dsu->parent[i_id] = j_id;
        if (dsu->rank[i_id] == dsu->rank[j_id])
            dsu->rank[j_id] = dsu->rank[j_id] + 1;
    }
}

char* to_string(disjoint_set_t* dsu) {
    char* result = (char*) malloc(MAX_TO_STRING * sizeof(char));
    char* value = (char*) malloc(MAX_STRING_VALUE * sizeof(char));
    for (int i = 0; i < dsu->size; i++) {
        sprintf(value, "%i", i);
        strcat(result, value);
        strcat(result, ": ");
        sprintf(value, "%i", dsu->parent[i]);
        strcat(result, value);
        strcat(result, "\n");
    }
    return result;
}

/* int main() {
    disjoint_set_t* dsu = new_disjoint_set(10);
    for (int i = 0; i < 10; i++) {
        make_set(dsu, i);
    }
    merge(dsu, 1, 5);
    merge(dsu, 0, 9);
    merge(dsu, 5, 3);
    merge(dsu, 6, 0);
    merge(dsu, 9, 2);
    merge(dsu, 1, 7);
    for (int i = 0; i < 10; i++) {
        printf("%d: %d\n", i, find(dsu, i));
    }
    printf("\n");
    printf(to_string(dsu));
    return 0;
} */