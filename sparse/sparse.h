#ifndef H_SPARSE_H
#define H_SPARSE_H
#include "array.h"

int                 sparse_find_nz(double **A, int n, int m,
                                   int *Ap);

void                sparse_pack (double **A, int m, int n,
                                 int *Ai, double *Ax);

void                sparse_unpack (double **A, int m, int n,
                                   int *Ap, int *Ai, double *Ax);

#endif /* H_SPARSEY_H */
