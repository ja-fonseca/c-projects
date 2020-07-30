#include "array.h"
#include <stdio.h>

int
main (void)
{
  int i,j;
  int n = 10;
  double **H;

  make_matrix(H, n, n);

  for (i = 0; i < n; i++)
      for (j = 0; j < n; j++)
        H[i][j] = 1.0 / (1 + i + j);

  print_matrix("%7.3f",H,n,n);

  free_matrix(H);
}
