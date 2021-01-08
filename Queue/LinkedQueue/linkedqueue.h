typedef struct queue_node {
    void *value;
    struct queue_node *next;
} queue_node_t;

typedef struct linked_queue{
    queue_node_t *head;
    queue_node_t *tail;
    int size;
} linked_queue_t;

#define MAX_TOSTRING 1024
#define MAX_STRING_VALUE 32

void enqueue(linked_queue_t *queue, void *value);
void* dequeue(linked_queue_t *queue);
void* peek(linked_queue_t *queue);
linked_queue_t* new_queue();
void delete_queue(linked_queue_t *queue);
char* toString(linked_queue_t *queue);
