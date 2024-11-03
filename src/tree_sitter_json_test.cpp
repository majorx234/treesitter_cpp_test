#include <cstdint>
#include <cstring>
#include <stdio.h>

extern "C" {
  #include <tree_sitter/api.h>
  TSLanguage *tree_sitter_json();
}

int main(void){
  const char *source_code = "{\"example\":{\"array1\":[1, null],\"array2\":[2, null],\"some_property\":{\"value1\":12,\"value2\":13}}}";

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
  TSNode root_node = ts_tree_root_node(tree);

    // Print the syntax tree as an S-expression.
  char *string = ts_node_string(root_node);
  printf("Syntax tree: %s\n", string);

  uint32_t nchildren_root = ts_node_child_count(root_node);

  for (uint32_t i = 0;i<nchildren_root;i++){
    TSNode child_node = ts_node_child(root_node,i);
    char *child_string = ts_node_string(root_node);
    printf("  ");
    printf("%s\n", child_string);
    uint32_t nchildren_child = ts_node_child_count(child_node);
    printf("has %d children\n",nchildren_child);
    for (uint32_t j = 0;j<nchildren_child;j++){
      TSNode childchild_node = ts_node_child(child_node,i);
      char *childchild_string = ts_node_string(root_node);
      printf("    ");
      printf("%s\n", childchild_string);
      free(childchild_string);
    }
    free(child_string);
  }
  // Free all of the heap-allocated memory.
  free(string);
  ts_tree_delete(tree);
  ts_parser_delete(parser);

  return 0;
}
