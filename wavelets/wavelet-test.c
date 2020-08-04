#include <stdio.h>
#include "wavelet.h"
#include "array.h"

static void
wavelet_test_vector (int n)
{
  int                 i;
  double             *v;

  make_vector (v, n);

  for (i = 0; i < n; i++)
    v[i] = 1.0 / (i + 1);

  printf ("Original vector:\n");
  print_vector ("%8.4f ", v, n);
  putchar ('\n');

  haar_transform_vector (v, n, WT_FWD);
  printf ("Transformed vector:\n");
  print_vector ("%8.4f ", v, n);
  putchar ('\n');

  haar_transform_vector (v, n, WT_REV);
  printf ("Reconstructed vector:\n");
  print_vector ("%8.4f ", v, n);
  putchar ('\n');

  free_vector (v);
}

static void
wavelet_test_matrix (int m, int n)
{
  int                 i, j;
  double            **A;

  make_matrix (A, m, n);

  for (i = 0; i < m; i++)
    for (j = 0; j < n; j++)
      A[i][j] = 1.0 / (i + j + 1);

  printf ("Original matrix:\n");
  print_matrix ("%8.4f ", A, m, n);
  putchar ('\n');

  haar_transform_matrix (A, m, n, WT_FWD);
  printf ("Transformed matrix:\n");
  print_matrix ("%8.4f ", A, m, n);
  putchar ('\n');

  haar_transform_matrix (A, m, n, WT_REV);
  printf ("Reconstructed matrix:\n");
  print_matrix ("%8.4f ", A, m, n);
  putchar ('\n');

  free_matrix (A);
}

int
main (void)
{
  wavelet_test_vector (8);

  wavelet_test_matrix (4, 8);

  return 0;
}
