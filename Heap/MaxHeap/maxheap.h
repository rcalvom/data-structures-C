typedef struct max_heap{
    float *values;
    int size;
    int capacity;
} max_heap_t;

#define INITIAL_CAPACITY 8
#define MAX_TOSTRING 1024
#define MAX_STRING_VALUE 32

void enqueue(max_heap_t* heap, float element);
float dequeue(max_heap_t* heap);
float peek(max_heap_t* heap);
max_heap_t* new_max_heap();
void delete_max_heap(max_heap_t* heap);
char* toString(max_heap_t* heap);