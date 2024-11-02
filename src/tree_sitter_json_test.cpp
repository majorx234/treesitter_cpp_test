#include <cstring>
#include <stdio.h>

extern "C" {
  #include <tree_sitter/api.h>
  TSLanguage *tree_sitter_json();
}

int main(void){
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
  TSNode root_node = ts_tree_root_node(tree);

    // Print the syntax tree as an S-expression.
  char *string = ts_node_string(root_node);
  printf("Syntax tree: %s\n", string);

  // Free all of the heap-allocated memory.
  free(string);
  ts_tree_delete(tree);
  ts_parser_delete(parser);

  return 0;
}
