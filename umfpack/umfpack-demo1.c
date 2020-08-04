#include <stdio.h>
#include "sparse.h"
#include <suitesparse/umfpack.h>

int
main (void)
{
  int                 nz;
  int                 n = 5;
  int                *Ap;
  int                *Ai;
  double             *b, *x, *Ax;
  double            **A;
  void              *Symbolic, *Numeric;

  /* Allocate and populate matrix for demo1 */
  make_matrix (A, n, n);
  A[0][0] = 2., A[0][1] = 3.,  A[0][2] = 0.,  A[0][3] = 0., A[0][4] = 0.;
  A[1][0] = 3., A[1][1] = 0.,  A[1][2] = 4.,  A[1][3] = 0., A[1][4] = 6.;
  A[2][0] = 0., A[2][1] = -1., A[2][2] = -3., A[2][3] = 2., A[2][4] = 0.;
  A[3][0] = 0., A[3][1] = 0.,  A[3][2] = 1.,  A[3][3] = 0., A[3][4] = 0.;
  A[4][0] = 0., A[4][1] = 4.,  A[4][2] = 2.,  A[4][3] = 0., A[4][4] = 1.;

  printf ("The sparse matrix is:\n");
  print_matrix ("%2.0f   ", A, 4, 5);

  /* Allocate and populate RHS */
  make_vector(b,n);
  b[0] = 8., b[1] = 45., b[2] = -3., b[3] = 3., b[4] = 19.;

  /* Storage for solution vector */
  make_vector(x,n);


  /* CSS objects */
  make_vector (Ap, n + 1);
  nz = sparse_find_nz(A, n, n, Ap);
  printf ("matrix is m x n = %i x %i, nz = %i\n\n", n, n, nz);
  make_vector (Ai, nz);
  make_vector (Ax, nz);

  sparse_pack (A, n, n, Ai, Ax);

  printf ("Ap = ");
  print_vector ("%i ", Ap, n + 1);
  printf ("Ai = ");
  print_vector ("%i ", Ai, nz);
  printf ("Ax = ");
  print_vector ("%1.0f   ", Ax, nz);

  /* UMFPACK call */
  umfpack_di_symbolic(n, n, Ap, Ai, Ax, &Symbolic, NULL, NULL);
  umfpack_di_numeric (Ap, Ai, Ax, Symbolic, &Numeric, NULL, NULL);
  umfpack_di_solve (UMFPACK_A, Ap, Ai, Ax, x, b, Numeric, NULL, NULL);

  /* Print computed solution */
  printf ("\nx = ");
  print_vector("%1.0f ", x,n);

  /* Free used memory */
  umfpack_di_free_symbolic(&Symbolic);
  umfpack_di_free_numeric(&Numeric);

  free_vector (Ap);
  free_vector (Ai);
  free_vector (Ax);
  free_vector (b);
  free_vector (x);
  free_matrix (A);
}
