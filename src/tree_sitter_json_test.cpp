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
  printf("Hello, Treesitter\n");
  return 0;
}
