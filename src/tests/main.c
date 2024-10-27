#include <orchestra.h>
#include <stdio.h>

int main(void) {
  /*{*/
  /*  o_string str;*/
  /*  o_string_init(&str);*/
  /*  o_string_uninit(&str);*/
  /*}*/
  /**/
  /*{*/
  /*  o_string str;*/
  /*  o_string_init(&str);*/
  /**/
  /*  o_string_set(&str, "hello world");*/
  /**/
  /*  o_string_uninit(&str);*/
  /*}*/
  /**/
  {
    o_string str;
    o_string_init(&str);
    
    o_string_set(&str, "hello world");

    for(unsigned int i = 0; i < 100; i ++)
      o_string_insert(&str, 0, "a");

    printf("%s\n", str.contents);

    o_string_uninit(&str);
  }

  return 0;
}
