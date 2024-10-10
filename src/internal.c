#include <orchestra_internal.h>
#include <stdlib.h>

int o_string_realloc(o_string* o_string_p, size_t new_size) {
#ifdef O_CHECK_NULL_ARGS
  if(o_string_p == NULL)
    return O_FAILURE_NULL_ARG;
#endif

  if(new_size == o_string_p->size || (new_size <= o_string_p->reserved && o_string_p->size == o_string_p->reserved))
    return O_SUCCESS;

  size_t size = new_size <= o_string_p->reserved ? o_string_p->reserved : new_size;

  void* result = realloc(o_string_p->contents, size + 1);
  if(result == NULL)
    return O_FAILURE_REALLOC;

  o_string_p->size = size;

  return O_SUCCESS;
}
