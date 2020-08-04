#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "wavelet.h"

#define SQRT1_2 sqrt(1./2)

static int
is_power_of_two (int n)
{
  if ((n & (n - 1)) != 0)
    return 0;
  return 1;
}

static void
haar_transform_vector_forward (double *v, int n)
{
  int                 i, d;
  double              x, y;
  double              h = sqrt (n);

  for (i = 0; i < n; i++)
    v[i] /= h;

  for (d = 1; d < n; d *= 2) {
    for (i = 0; i < n; i += 2 * d) {
      x = SQRT1_2 * (v[i] + v[i + d]);
      y = SQRT1_2 * (v[i] - v[i + d]);
      v[i] = x;
      v[i + d] = y;
    }
  }
}

static void
haar_transform_vector_reverse (double *v, int n)
{
  int                 i, d;
  double              x, y;
  double              h = sqrt (n);

  for (d = n / 2; d > 0; d /= 2) {
    for (i = 0; i < n; i += 2 * d) {
      x = SQRT1_2 * (v[i] + v[i + d]);
      y = SQRT1_2 * (v[i] - v[i + d]);
      v[i] = x;
      v[i + d] = y;
    }
  }

  for (i = 0; i < n; i++)
    v[i] *= h;
}

static void
haar_transform_matrix_forward (double **A, int m, int n)
{
  int                 i, j, d;
  double              x, y;
  double              h = sqrt (m);

  for (i = 0; i < m; i++)
    haar_transform_vector_forward (A[i], n);

  for (j = 0; j < n; j++) {

    for (i = 0; i < m; i++) {
      A[i][j] /= h;
    }

    for (d = 1; d < m; d *= 2)  {
      for (i = 0; i < m; i += 2 * d) {
        x = SQRT1_2 * (A[i][j] + A[i + d][j]);
        y = SQRT1_2 * (A[i][j] - A[i + d][j]);
        A[i][j] = x;
        A[i + d][j] = y;
      }
    }

  }
}

static void
haar_transform_matrix_reverse (double **A, int m, int n)
{
  int                 i, j, d;
  double              x, y;
  double              h = sqrt (m);

  for (i = 0; i < m; i++)
    haar_transform_vector_reverse (A[i], n);

  for (j = 0; j < n; j++) {

    for (d = m / 2; d > 0; d /= 2) {
      for (i = 0; i < m; i += 2 * d) {
        x = SQRT1_2 * (A[i][j] + A[i + d][j]);
        y = SQRT1_2 * (A[i][j] - A[i + d][j]);
        A[i][j] = x;
        A[i + d][j] = y;
      }
    }

    for (i = 0; i < m; i++) {
      A[i][j] *= h;
    }
  }
}

void
haar_transform_vector (double *v, int n, int dir)
{

  if (!is_power_of_two (n)) {
    fprintf (stderr, "Vector's size must be a power of two\n");
    exit (EXIT_FAILURE);
  }

  switch (dir) {
  case WT_FWD:
    haar_transform_vector_forward (v, n);
    break;
  case WT_REV:
    haar_transform_vector_reverse (v, n);
    break;
  default:
    fprintf (stderr, "*** error in haar_transform_vector():"
             "the third argument should be either WT_FW or WT_REV\n");
    exit (EXIT_FAILURE);
  }
}

void
haar_transform_matrix (double **A, int m, int n, int dir)
{
  if (!is_power_of_two (n) || !is_power_of_two (m)) {
    fprintf (stderr, "Matrix dimesions must be a power of two\n");
    exit (EXIT_FAILURE);
  }

  switch (dir) {
  case WT_FWD:
    haar_transform_matrix_forward (A, m, n);
    break;
  case WT_REV:
    haar_transform_matrix_reverse (A, m, n);
    break;
  default:
    fprintf (stderr, "*** error in haar_transform_matrix():"
             "the third argument should be either WT_FW or WT_REV\n");
    exit (EXIT_FAILURE);
  }
}
