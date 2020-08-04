#include <stdio.h>
#include <suitesparse/umfpack.h>
#include "array.h"

static void error_and_exit(int status, const char *file, int line)
{
    fprintf(stderr, "*** file is %s, line %d: ", file, line);
    switch (status) {
    case UMFPACK_ERROR_out_of_memory:
        fprintf(stderr, "out of memory!\n");
        break;
    case UMFPACK_WARNING_singular_matrix:
        fprintf(stderr, "matrix is singular!\n");
        break;
    default:
        fprintf(stderr, "UMFPACK error code %d\n", status);
    }
    exit(EXIT_FAILURE);
}

int
main (void)
{
  int                 n = 5, N = 20;
  int                 k = 0;
  int                 status;
  int                *Ap, *Ai, *Ti, *Tj;
  double             *b, *x, *Ax, *Tx;
  void              *Symbolic, *Numeric;

  /* Allocate and populate RHS */
  make_vector(b,n);
  b[0] = 8., b[1] = 45., b[2] = -3., b[3] = 3., b[4] = 19.;

  /* Storage for solution vector */
  make_vector(x,n);

  /* Triplet form of the matrix from demo1 */
  make_vector(Ti, N);
  make_vector(Tj, N);
  make_vector(Tx, N);

  Ti[k] = 0, Tj[k] = 0, Tx[k] = 2.0, k++;
  Ti[k] = 1, Tj[k] = 0, Tx[k] = 3.0, k++;
  Ti[k] = 0, Tj[k] = 1, Tx[k] = 3.0, k++;
  Ti[k] = 2, Tj[k] = 1, Tx[k] = -1.0, k++;
  Ti[k] = 4, Tj[k] = 1, Tx[k] = 4.0, k++;
  Ti[k] = 1, Tj[k] = 2, Tx[k] = 4.0, k++;
  Ti[k] = 2, Tj[k] = 2, Tx[k] = -3.0, k++;
  Ti[k] = 3, Tj[k] = 2, Tx[k] = 1.0, k++;
  Ti[k] = 4, Tj[k] = 2, Tx[k] = 2.0, k++;
  Ti[k] = 2, Tj[k] = 3, Tx[k] = 2.0, k++;
  Ti[k] = 1, Tj[k] = 4, Tx[k] = 6.0, k++;
  Ti[k] = 4, Tj[k] = 4, Tx[k] = 1.0, k++;

  /* Translate to CCS format using UMFPACK function */
  make_vector(Ap, n + 1);
  make_vector(Ai, N);
  make_vector(Ax, N);

  status = umfpack_di_triplet_to_col(n, n, N, Ti, Tj, Tx,
                                     Ap, Ai, Ax, NULL);
  if (status != UMFPACK_OK)
      error_and_exit(status, __FILE__, __LINE__);

  /* UMFPACK calls */
  status = umfpack_di_symbolic(n, n, Ap, Ai, Ax, &Symbolic, NULL, NULL);
  if (status != UMFPACK_OK)
      error_and_exit(status, __FILE__, __LINE__);

  status = umfpack_di_numeric (Ap, Ai, Ax, Symbolic, &Numeric, NULL, NULL);
  if (status != UMFPACK_OK)
      error_and_exit(status, __FILE__, __LINE__);

  status = umfpack_di_solve (UMFPACK_A, Ap, Ai, Ax, x, b, Numeric, NULL, NULL);
  if (status != UMFPACK_OK)
      error_and_exit(status, __FILE__, __LINE__);

  /* Print computed solution */
  printf ("Solution vector x = ");
  print_vector("%1.0f ", x,n);

  /* Free used memory */
  umfpack_di_free_symbolic(&Symbolic);
  umfpack_di_free_numeric(&Numeric);

  free_vector (Ap);
  free_vector (Ai);
  free_vector (Ax);
  free_vector (Ti);
  free_vector (Tj);
  free_vector (Tx);
  free_vector (b);
  free_vector (x);
}
