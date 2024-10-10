#include <orchestra.h>
#include <stdlib.h>

int o_string_init(o_string* o_string_p) {
#ifdef O_CHECK_NULL_ARGS
  if(o_string_p == NULL)
    return O_FAILURE_NULL_ARG;
#endif

  o_string_p->size = 0;
  o_string_p->contents = (char*) malloc(sizeof(char));

  if(o_string_p->contents == NULL)
    return O_FAILURE_MALLOC;

  return O_SUCCESS;
}

int o_string_uninit(o_string* o_string_p) {
#ifdef O_CHECK_NULL_ARGS
  if(o_string_p == NULL)
    return O_FAILURE_NULL_ARG;
#endif

  free(o_string_p->contents);
  return O_SUCCESS;
}
