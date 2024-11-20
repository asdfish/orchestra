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

extern int o_string_init(o_string* o_string_p);
extern int o_string_reserve(o_string* o_string_p, size_t reservation);
extern int o_string_uninit(o_string* o_string_p);

extern int o_string_cat(o_string* o_string_p, const char* new_contents);
extern int o_string_clear(o_string* o_string_p);
extern int o_string_delete(o_string* o_string_p, size_t index, size_t length);
extern int o_string_insert(o_string* o_string_p, size_t index, const char* insert);
extern int o_string_replace_all(o_string* o_string_p, const char* query, const char* replacement);
extern int o_string_set(o_string* o_string_p, const char* new_contents);

#endif
