#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <stdio.h>

extern "C" {
  #include <tree_sitter/api.h>
  #include "node_stack.h"
  TSLanguage *tree_sitter_json();
}

void visit_tree_recursive (TSNode node) {
  // Print the syntax tree as an S-expression.
  char *string = ts_node_string(node);
  printf("Syntax tree: %s\n", string);
  free(string);
  unsigned child_count = ts_node_child_count(node);

  for (unsigned i = 0; i < child_count; i++) {
    TSNode child_node = ts_node_child(node, i);

    visit_tree_recursive(child_node);
  }
}

void visit_tree_iterative(TSTree * tree){
  TSNode* node = (TSNode*)malloc(sizeof(TSNode));
  *node = ts_tree_root_node(tree);
  NodeStack node_stack = {
    .arr = {0},
    .top = 0
  };
  NodeStack to_delete = {
    .arr = {0},
    .top = 0
  };;

  push(&node_stack, node);

  printf("startloop\n");
  while(!is_empty(&node_stack)){
    TSNode* node = pop(&node_stack);
    if(node == NULL){
      printf("error: node_stack empty\n");
      break;
    }
    char *string = ts_node_string(*node);
    printf("Syntax tree1: %s\n", string);
    free(string);

    unsigned child_count = ts_node_child_count(*node);
    for (unsigned i = 0; i < child_count; i++) {
        TSNode* child_node = (TSNode*)malloc(sizeof(TSNode));
        *child_node =  ts_node_child(*node, i);
        push(&node_stack, child_node);
    }
    push(&to_delete, node);
  }

  printf("clean up \n");

  // clean up
  while(!is_empty(&to_delete)){
    TSNode* delete_node = pop(&to_delete);
    if(delete_node == NULL){
      printf("error: delete node_stack empty\n");
      break;
    }
    free(delete_node);
  }
}

int main(void){
  //const char *source_code = "{\"example\":{\"array1\":[1, null],\"array2\":[2, null],\"some_property\":{\"value1\":12,\"value2\":13}}}";

  const char *source_code = "{\"example\":[1, null]}";
  TSLanguage *p = tree_sitter_json();
  TSParser * parser = ts_parser_new();
  ts_parser_set_language(parser, tree_sitter_json());
  TSTree * tree = ts_parser_parse_string(
    parser,
    NULL,
    source_code,
    strlen(source_code)
  );

  // Get the root node of the syntax tree.
  visit_tree_iterative(tree);
  printf("finished iterative traversal\n");
  TSNode root_node = ts_tree_root_node(tree);

  visit_tree_recursive(root_node);
  printf("finished recursive traversal\n");
  ts_tree_delete(tree);
  ts_parser_delete(parser);

  return 0;
}
