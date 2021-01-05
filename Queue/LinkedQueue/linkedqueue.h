typedef struct node {
    float val;
    struct node *next;
} node_t;

typedef struct queue{
    struct node *head;
    struct node *tail;
    int size;
} queue_t;

void enqueue(queue_t *queue, float val);
float dequeue(queue_t *queue);
float peek(queue_t *queue);
queue_t* new_queue();
void delete_queue(queue_t *queue);
