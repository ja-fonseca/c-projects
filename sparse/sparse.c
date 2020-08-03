#include <stdio.h>
#include "sparse.h"

int sparse_find_nz(double **A, int n, int m, int *Ap)
{
    int i, j;
    int nz = 0;

    for (j = 0; j < n; j++) {
      for (i = 0; i < m; i++) {
        if (A[i][j] != 0) {
          nz++;
        }
      }
      Ap[j + 1] = nz;
    }

   return nz;
}

void
sparse_pack (double **A, int m, int n, int *Ai, double *Ax)
{
  int                 i, j, k;

  for (j = 0, k = 0; j < n; j++) {
    for (i = 0; i < m; i++) {
      if (A[i][j] != 0) {
        Ai[k] = i;
        Ax[k] = A[i][j];
        k++;
      }
    }
  }
}

void
sparse_unpack (double **A, int m, int n, int *Ap, int *Ai, double *Ax)
{
  int                 i, j, k;

  for (i = 0; i < m; i++)
    for (j = 0; j < n; j++)
      A[i][j] = 0.0;

  for (j = 0; j < n; j++) {
    for (k = Ap[j]; k < Ap[j + 1]; k++) {
      i = Ai[k];
      A[i][j] = Ax[k];
    }
  }
}
