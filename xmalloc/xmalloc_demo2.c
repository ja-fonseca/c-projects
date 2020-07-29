#include "xmalloc.h"
#include <stdio.h>

int
main (void)
{

  int                 k = 0;

  for (k = 0;; k++) {
    double             *x = xmalloc (1000000000);
    if (x != NULL)
      printf ("%i: 1000000000 bytes allocated\n", k);
    else
      break;
  }
}
