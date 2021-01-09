typedef struct array_stack{
    void **values;
    int top;
    int size;
    int capacity;
} array_stack_t;

#define INITIAL_CAPACITY 8
#define MAX_TOSTRING 1024
#define MAX_STRING_VALUE 32

void push(array_stack_t *stack, void *value);
void* pop(array_stack_t *stack);
void* peek(array_stack_t *stack);
array_stack_t* new_stack();
void delete_stack(array_stack_t *stack);
char* toString(array_stack_t *stack);
