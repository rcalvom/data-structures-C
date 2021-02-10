typedef struct disjoint_set {
    int* parent;
    int* rank;
    int size;
} disjoint_set_t;

#define MAX_TO_STRING 1024
#define MAX_STRING_VALUE 32

disjoint_set_t* new_disjoint_set(int size);
void make_set(disjoint_set_t* dsu, int i);
int find(disjoint_set_t* dsu, int i);
void merge(disjoint_set_t* dsu, int i, int j);
char* to_string(disjoint_set_t* dsu);