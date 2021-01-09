typedef struct stack_node {
    void *value;
    struct stack_node *previous;
    struct stack_node *next;
} stack_node_t;

typedef struct linked_queue{
    stack_node_t *top;
    int size;
} linked_stack_t;

#define MAX_TOSTRING 1024
#define MAX_STRING_VALUE 32

void push(linked_stack_t *stack, void *value);
void* pop(linked_stack_t *stack);
void* peek(linked_stack_t *stack);
linked_stack_t* new_stack();
void delete_stack(linked_stack_t *stack);
char* toString(linked_stack_t *stack);