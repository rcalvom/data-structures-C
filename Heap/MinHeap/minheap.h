typedef struct min_heap{
    float *values;
    int size;
    int capacity;
} min_heap_t;

#define INITIAL_CAPACITY 8
#define MAX_TOSTRING 1024
#define MAX_STRING_VALUE 32

void enqueue(min_heap_t* heap, float element);
float dequeue(min_heap_t* heap);
float peek(min_heap_t* heap);
min_heap_t* new_min_heap();
void delete_min_heap(min_heap_t* heap);
char* toString(min_heap_t* heap);