#include <tree_sitter/api.h>

#define MAX_SIZE 20

typedef struct NodeStack {
     TSNode* arr[MAX_SIZE];
     int top;
} NodeStack;
