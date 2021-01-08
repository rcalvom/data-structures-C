typedef struct array_queue{
    void **values;
    int front;
    int rear;
    int size;
    int capacity;
} array_queue_t;

#define INITIAL_CAPACITY 8
#define MAX_TOSTRING 1024
#define MAX_STRING_VALUE 32

void enqueue(array_queue_t *queue, void *value);
void* dequeue(array_queue_t *queue);
void* peek(array_queue_t *queue);
array_queue_t* new_queue();
void delete_queue(array_queue_t *queue);
char* toString(array_queue_t *queue);