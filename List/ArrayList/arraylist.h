typedef struct array_list {
    void **elements;
    int capacity;
    int size;
} array_list_t;

#define INITIAL_CAPACITY 10

array_list_t* new_array_list();
void* get(array_list_t *list, int index);
int find(array_list_t *list, void *element);
void insert(array_list_t *list, int index, void *value);
void push_front(array_list_t *list, void *value);
void push_back(array_list_t *list, void *value);
void delete(array_list_t *list, int index);
void make_empty(array_list_t *list);
char* to_string(array_list_t *list);