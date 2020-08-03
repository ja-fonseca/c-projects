#include <stdio.h>
#include "sparse.h"

int
main (void)
{
  int                 nz;
  int                 m = 4;
  int                 n = 5;
  int                *Ap;
  int                *Ai;
  double             *Ax;
  double            **A;

  make_matrix (A, 4, 5);
  A[0][0] = 0., A[0][1] = 7., A[0][2] = 0., A[0][3] = 0., A[0][4] = 1.;
  A[1][0] = 0., A[1][1] = 4., A[1][2] = 0., A[1][3] = 3., A[1][4] = 0.;
  A[2][0] = 6., A[2][1] = 6., A[2][2] = 5., A[2][3] = 1., A[2][4] = 4.;
  A[3][0] = 5., A[3][1] = 5., A[3][2] = 0., A[3][3] = 0., A[3][4] = 0.;

  printf ("The sparse matrix is:\n");
  print_matrix ("%1.0f   ", A, 4, 5);

  make_vector (Ap, n + 1);
  nz = sparse_find_nz(A, n, m, Ap);
  printf ("matrix is m x n = %i x %i, nz = %i\n\n", m, n, nz);

  make_vector (Ai, nz);
  make_vector (Ax, nz);

  sparse_pack (A, m, n, Ai, Ax);

  printf ("Ap = ");
  print_vector ("%i ", Ap, n + 1);

  printf ("Ai = ");
  print_vector ("%i ", Ai, nz);

  printf ("Ax = ");
  print_vector ("%1.0f   ", Ax, nz);

  free_vector (Ap);
  free_vector (Ai);
  free_vector (Ax);
  free_matrix (A);
}
