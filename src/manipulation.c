#include <orchestra_internal.h>
#include <string.h>

int o_string_cat(o_string* o_string_p, const char* new_contents) {
#ifdef O_CHECK_NULL_ARGS
  if(o_string_p == NULL || new_contents == NULL)
    return O_FAILURE_NULL_ARG;
#endif

  size_t contents_length = strlen(o_string_p->contents);
  size_t new_contents_length = strlen(new_contents);

  if(new_contents_length == 0)
    return O_SUCCESS;

  if(o_string_realloc(o_string_p, contents_length + new_contents_length) != O_SUCCESS)
    return O_FAILURE_REALLOC;

  strcpy(o_string_p->contents + contents_length, new_contents);

  return O_SUCCESS;
}

int o_string_delete(o_string* o_string_p, size_t index, size_t length) {
#ifdef O_CHECK_NULL_ARGS
  if(o_string_p == NULL)
    return O_FAILURE_NULL_ARG;
#endif

  if(length == 0)
    return O_SUCCESS;

  size_t contents_length = strlen(o_string_p->contents);

  if(o_string_realloc(o_string_p, contents_length - length) != O_SUCCESS)
    return O_FAILURE_REALLOC;

  strcpy(o_string_p->contents + index, o_string_p->contents + index + length);

  return O_SUCCESS;
}

int o_string_insert(o_string* o_string_p, size_t index, const char* insert) {
#ifdef O_CHECK_NULL_ARGS
  if(o_string_p == NULL || insert == NULL)
    return O_FAILURE_NULL_ARG;
#endif

  size_t insert_length = strlen(insert);
  if(insert_length == 0)
    return O_SUCCESS;

  if(o_string_realloc(o_string_p, insert_length) != O_SUCCESS)
    return O_FAILURE_REALLOC;

  strcpy(o_string_p->contents + index + insert_length, o_string_p->contents + index);
  strncpy(o_string_p->contents + index, insert, insert_length);

  return O_SUCCESS;
}

int o_string_set(o_string* o_string_p, const char* new_contents) {
#ifdef O_CHECK_NULL_ARGS
  if(o_string_p == NULL || new_contents == NULL)
    return O_FAILURE_NULL_ARG;
#endif

  size_t new_contents_length = strlen(new_contents); 

  if(new_contents_length == 0)
    return O_SUCCESS;

  if(o_string_realloc(o_string_p, new_contents_length) != O_SUCCESS)
    return O_FAILURE_REALLOC;

  strcpy(o_string_p->contents, new_contents);
  return O_SUCCESS;
}
