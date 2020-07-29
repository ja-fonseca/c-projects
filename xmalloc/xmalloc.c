#include <stdio.h>
#include "xmalloc.h"

void               *
malloc_or_exit (size_t nbytes, const char *file, int line)
{
  void               *x;
  if (((x = malloc (nbytes)) == NULL) || (nbytes == 0)) {
    fprintf (stderr, "%s:line %d: malloc() of %zu bytes failed\n", file, line,
             nbytes);
  }

  return x;
}
