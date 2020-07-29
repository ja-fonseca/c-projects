#include "xmalloc.h"
#include <stdio.h>

int
main (void)
{

  double             *x;

  printf ("allocating 1000 bytes\n");
  x = xmalloc (1000);
  free (x);
  printf ("memory freed\n");

  printf ("allocating 0 bytes\n");
  x = xmalloc (0);
}
