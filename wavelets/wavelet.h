#ifndef H_WAVELET_H
#define H_WAVELET_H

#define WT_FWD 0
#define WT_REV 1

void                haar_transform_vector (double *v, int n, int dir);

void                haar_transform_matrix (double **A, int m, int n, int dir);

#endif /* H_WAVELET_H */
