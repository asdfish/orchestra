#ifndef ORCHESTRA_H
#define ORCHESTRA_H

/*#define O_CHECK_NULL_ARGS*/

#define O_FAILURE_MALLOC -1
#define O_FAILURE_REALLOC -2
#define O_FAILURE_NULL_ARG -3

#define O_SUCCESS 0

#include <stddef.h>

typedef struct {
  char* contents;
  size_t reserved;
  size_t size;
} o_string;

extern int o_string_init(o_string* restrict o_string_p);
extern int o_string_reserve(o_string* restrict o_string_p, size_t reservation);
extern int o_string_uninit(o_string* restrict o_string_p);

extern int o_string_cat(o_string* restrict o_string_p, const char* new_contents);
extern int o_string_clear(o_string* restrict o_string_p);
extern int o_string_delete(o_string* restrict o_string_p, size_t index, size_t length);
extern int o_string_insert(o_string* restrict o_string_p, size_t index, const char* insert);
extern int o_string_replace_all(o_string* restrict o_string_p, const char* query, const char* replacement);
extern int o_string_set(o_string* restrict o_string_p, const char* new_contents);

#ifdef ORCHESTRA_IMPLEMENTATION
#include <limits.h>
#include <stdlib.h>
#include <string.h>

static int o_string_realloc(o_string* restrict o_string_p, size_t new_size);

static int o_string_realloc(o_string* restrict o_string_p, size_t new_size) {
#ifdef O_CHECK_NULL_ARGS
  if(o_string_p == NULL)
    return O_FAILURE_NULL_ARG;
#endif

  if(new_size == o_string_p->size || (new_size <= o_string_p->reserved && o_string_p->size == o_string_p->reserved))
    return O_SUCCESS;

  size_t size = new_size <= o_string_p->reserved ? o_string_p->reserved : new_size;

  char* result = (char*) realloc(o_string_p->contents, size + 1);
  if(result == NULL)
    return O_FAILURE_REALLOC;

  o_string_p->contents = result;

  o_string_p->size = size;

  return O_SUCCESS;
}

int o_string_init(o_string* restrict o_string_p) {
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
int o_string_reserve(o_string* restrict o_string_p, size_t reservation) {
  o_string_p->reserved = reservation;

  return O_SUCCESS;
}
int o_string_uninit(o_string* restrict o_string_p) {
#ifdef O_CHECK_NULL_ARGS
  if(o_string_p == NULL)
    return O_FAILURE_NULL_ARG;
#endif

  free(o_string_p->contents);
  return O_SUCCESS;
}

int o_string_cat(o_string* restrict o_string_p, const char* new_contents) {
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

  /*strcpy(o_string_p->contents + contents_length, new_contents);*/
  strcat(o_string_p->contents, new_contents);

  return O_SUCCESS;
}
int o_string_clear(o_string* restrict o_string_p) {
#ifdef O_CHECK_NULL_ARGS
  if(o_string_p == NULL)
    return O_FAILURE_NULL_ARG;
#endif

  if(o_string_realloc(o_string_p, 0) != O_SUCCESS)
    return O_FAILURE_REALLOC;

  o_string_p->contents[0] = '\0';

  return O_SUCCESS;
}
int o_string_delete(o_string* restrict o_string_p, size_t index, size_t length) {
#ifdef O_CHECK_NULL_ARGS
  if(o_string_p == NULL)
    return O_FAILURE_NULL_ARG;
#endif

  if(length == 0)
    return O_SUCCESS;

  size_t contents_length = strlen(o_string_p->contents);

  if(o_string_realloc(o_string_p, contents_length - length) != O_SUCCESS)
    return O_FAILURE_REALLOC;

  char* footer = o_string_p->contents + index + length;

  memcpy(o_string_p->contents + index, footer, strlen(footer) + 1);

  return O_SUCCESS;
}
int o_string_insert(o_string* restrict o_string_p, size_t index, const char* insert) {
#ifdef O_CHECK_NULL_ARGS
  if(o_string_p == NULL || insert == NULL)
    return O_FAILURE_NULL_ARG;
#endif

  size_t insert_length = strlen(insert);
  if(insert_length == 0)
    return O_SUCCESS;

  if(o_string_realloc(o_string_p, o_string_p->size + insert_length) != O_SUCCESS)
    return O_FAILURE_REALLOC;

  char* insert_location = o_string_p->contents + index;
  size_t insert_location_length = strlen(insert_location);

  memcpy(insert_location + insert_length, insert_location, insert_location_length + 1);
  memcpy(insert_location, insert, insert_length);

  return O_SUCCESS;
}
int o_string_replace_all(o_string* restrict o_string_p, const char* query, const char* replacement) {
#ifdef O_CHECK_NULL_ARGS
  if(o_string_p == NULL || query == NULL || replacement == NULL)
    return O_FAILURE_NULL_ARG;
#endif

  size_t query_length = strlen(query);
  if(query_length == 0)
    return O_SUCCESS;

  if(strstr(o_string_p->contents, query) == NULL)
    return O_SUCCESS;

  char* contents_pointer = o_string_p->contents;
  while((contents_pointer = strstr(contents_pointer, query)) != NULL) {
    size_t index = contents_pointer - o_string_p->contents;
    if(o_string_delete(o_string_p, index, query_length) != O_SUCCESS)
      return O_FAILURE_REALLOC;
    if(o_string_insert(o_string_p, index, replacement) != O_SUCCESS)
      return O_FAILURE_REALLOC;

    contents_pointer += query_length;
  }

  return O_SUCCESS;
}
int o_string_set(o_string* restrict o_string_p, const char* new_contents) {
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
#endif // ORCHESTRA_IMPL

#endif // ORCHESTRA_H
