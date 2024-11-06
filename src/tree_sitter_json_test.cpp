#include <cstdint>
#include <cstring>
#include <stdio.h>

extern "C" {
  #include <tree_sitter/api.h>
  TSLanguage *tree_sitter_json();
}

void visit_tree (TSNode node) {
  // Print the syntax tree as an S-expression.
  char *string = ts_node_string(node);
  printf("Syntax tree: %s\n", string);
  free(string);
  unsigned child_count = ts_node_child_count(node);

  for (unsigned i = 0; i < child_count; i++) {
    TSNode child_node = ts_node_child(node, i);

    visit_tree(child_node);
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
  TSNode root_node = ts_tree_root_node(tree);

  visit_tree(root_node);
  ts_tree_delete(tree);
  ts_parser_delete(parser);

  return 0;
}
