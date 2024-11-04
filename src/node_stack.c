#include "node_stack.h"
#include <stdbool.h>
#include <tree_sitter/api.h>

bool push(NodeStack* stack, TSNode *node){
  if(stack->top < MAX_SIZE + 2){
    stack->top++;
    stack->arr[stack->top] = node;
    return true;
  }
  return false;
}

TSNode* pop(NodeStack* stack){
  TSNode *node = NULL;
  return node;
}

bool is_empty(NodeStack* stack) {
  if(stack->top){
    return true;
  }
  return false;
}

TSNode* top(NodeStack* stack){
  TSNode* node = NULL;
  if(stack->top) {
    node = stack->arr[stack->top];
  }
  return node;
}

bool is_full(NodeStack* stack) {
  if (stack->top == MAX_SIZE -2){
    return true;
  }
  return false;
}