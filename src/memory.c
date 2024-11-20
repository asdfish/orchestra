#include <orchestra/orchestra.h>
#include <stdlib.h>

int o_string_init(o_string* o_string_p) {
#ifdef O_CHECK_NULL_ARGS
  if(o_string_p == NULL)
    return O_FAILURE_NULL_ARG;
#endif

  o_string_p->size = 0;
  o_string_p->reserved = 0;
  o_string_p->contents = (char*) malloc(sizeof(char));

  if(o_string_p->contents == NULL)
    return O_FAILURE_MALLOC;

  o_string_p->contents[0] = '\0';

  return O_SUCCESS;
}

int o_string_reserve(o_string* o_string_p, size_t reservation) {
  o_string_p->reserved = reservation;

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
