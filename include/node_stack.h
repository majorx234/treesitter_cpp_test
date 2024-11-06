#include <tree_sitter/api.h>

#define MAX_SIZE 50

typedef struct NodeStack {
     TSNode* arr[MAX_SIZE];
     int top;
} NodeStack;

bool push(NodeStack* stack, TSNode *node);
TSNode* pop(NodeStack* stack);
bool is_empty(NodeStack* stack);
bool is_full(NodeStack* stack);
