#include <stdbool.h>

typedef struct node {
    void *key;
    struct node *prev;
    struct node *next;
} node_t;

typedef struct linked_list {
    int size;
    struct node *head;
    struct node *tail;
} linked_list_t;

#define MAX_TOSTRING 1024
#define MAX_STRING_VALUE 32

linked_list_t* new_linked_list();
bool empty(linked_list_t *list);
void push_back(linked_list_t *list, void *key);
void* pop_back(linked_list_t *list);
void* top_back(linked_list_t *list);
void push_front(linked_list_t *list, void *key);
void* pop_front(linked_list_t *list);
void* top_front(linked_list_t *list);
void insert_at(linked_list_t *list, int position, void *key);
bool find(linked_list_t *list, void *key);
void erase(linked_list_t *list, void *key);
int size(linked_list_t *list);
char* to_string(linked_list_t *list);