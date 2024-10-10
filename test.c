#include <orchestra.h>
#include <stdio.h>

int main(void) {
  o_string str;
  o_string_init(&str);
  o_string_set(&str, "hello");
  o_string_cat(&str, " world");
  o_string_delete(&str, 0, 1);
  o_string_insert(&str, 0, "s");
  printf("%s\n",str.contents);
  o_string_uninit(&str);
  return 0;
}
