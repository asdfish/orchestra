#define ORCHESTRA_IMPLEMENTATION
#include <orchestra.h>
#include <stdio.h>

int main(void) {
  o_string string;
  if(o_string_init(&string) != O_SUCCESS)
    return -1;

  if(o_string_set(&string, "asdfkjlasdfj") != O_SUCCESS)
    goto o_string_uninit;
  
  printf("%s\n", string.contents);
  
  o_string_uninit(&string);
  return 0;

o_string_uninit:
  o_string_uninit(&string);
  return -1;
}
