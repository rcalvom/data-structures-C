typedef struct array_list {
    int* elements;
    int capacity;
    int size;
} array_list_t;

int get(array_list_t *list, int index);
int find(array_list_t *list, int element);
void insert(array_list_t *list, int index, int value);
void delete(array_list_t *list, int index);
void make_empty(array_list_t *list);
void print_list(array_list_t *list);