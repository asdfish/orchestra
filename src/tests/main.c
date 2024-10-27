#include <orchestra.h>
#include <stdio.h>

void test_init(void) {
  o_string str;
  o_string_init(&str);
  printf("%s\n", str.contents);
  o_string_uninit(&str);
}

void test_set(void) {
  o_string str;
  o_string_init(&str);

  o_string_set(&str, "hello world");

  printf("%s\n", str.contents);

  o_string_uninit(&str);
}

void test_insert(void) {
  o_string str;
  o_string_init(&str);

  o_string_set(&str, "hello world");

  for(unsigned int i = 0; i < 100; i ++)
    o_string_insert(&str, 0, "a");

  printf("%s\n", str.contents);

  o_string_uninit(&str);
}

void test_insert_char_array(void) {
  o_string str;
  o_string_init(&str);

  o_string_set(&str, "hello world");

  for(unsigned int i = 0; i < 1000; i ++) {
    char insert[2] = " \0";
    insert[0] = 'a';
    o_string_insert(&str, 0, insert);
  }

  printf("%s\n", str.contents);

  o_string_uninit(&str);
}

int main(void) {
  test_insert_char_array();
  return 0;
}
