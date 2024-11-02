#include <stdio.h>

extern "C" {
  #include <tree_sitter/api.h>
  TSLanguage *tree_sitter_json();
}

int main(void){
  TSLanguage *p =tree_sitter_json();
  printf("Hello, Treesitter\n");
  return 0;
}
