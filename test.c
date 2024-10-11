#include <orchestra.h>
#include <stdio.h>
#include <string.h>

int main(void) {
  o_string str;
  o_string_init(&str);
  o_string_set(&str, "hello world fdas worldly");
  o_string_replace_all(&str, "world", "worlds");
  o_string_replace_all(&str, "w", "wall");
  printf("%s\n",str.contents);
  o_string_uninit(&str);
  return 0;
}
