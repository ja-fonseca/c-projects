#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "image-io.h"
#include "wavelet.h"

static int
prune_matrix (double **A, int m, int n, double rel_err)
{
  int                 i, j;
  int                 nzeroed;
  double              a;
  double              threshold;
  double              min, max;
  double              abs_err2;
  double              norm2, cutnorm2;
  double              eps = 1e-6;

  min = max = fabs (A[0][0]);
  norm2 = 0.0;
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      a = fabs (A[i][j]);
      min = (a < min) ? a : min;
      max = (a > max) ? a : max;
      norm2 += a * a;
    }
  }

  abs_err2 = norm2 * pow (rel_err, 2.);
  while ((max - min) >= eps * sqrt (abs_err2)) {
    threshold = 0.5 * (max + min);
    cutnorm2 = 0.0;
    for (i = 0; i < m; i++) {
      for (j = 0; j < n; j++) {
        a = fabs (A[i][j]);
        cutnorm2 += (a < threshold) ? a * a : 0.;
      }
    }
    if (cutnorm2 > abs_err2)
      max = threshold;
    else if (cutnorm2 < abs_err2)
      min = threshold;
  }

  nzeroed = 0;
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      if (fabs (A[i][j]) < threshold) {
        A[i][j] = 0.;
        nzeroed++;
      }
    }
  }

  return nzeroed;
}

static inline double
three_point_rmse (double r, double g, double b)
{
  return (r * r + g * g + b * b) / 3.0;
}

static int
prune_rgb_matrices (double **R, double **G, double **B,
                    int m, int n, double rel_err)
{
  int                 i, j;
  int                 nzeroed;
  double              a;
  double              threshold;
  double              min, max;
  double              abs_err2;
  double              norm2, cutnorm2;
  double              eps = 1e-6;

  min = max = three_point_rmse (R[0][0], G[0][0], B[0][0]);
  norm2 = 0.0;
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      a = three_point_rmse (R[i][j], G[i][j], B[i][j]);
      min = (a < min) ? a : min;
      max = (a > max) ? a : max;
      norm2 += a * a;
    }
  }

  abs_err2 = norm2 * pow (rel_err, 2.);
  while ((max - min) >= eps * sqrt (abs_err2)) {
    threshold = 0.5 * (max + min);
    cutnorm2 = 0.0;
    for (i = 0; i < m; i++) {
      for (j = 0; j < n; j++) {
        a = three_point_rmse (R[i][j], G[i][j], B[i][j]);
        cutnorm2 += (a < threshold) ? a * a : 0.;
      }
    }
    if (cutnorm2 > abs_err2)
      max = threshold;
    else if (cutnorm2 < abs_err2)
      min = threshold;
  }

  nzeroed = 0;
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      a = three_point_rmse (R[i][j], G[i][j], B[i][j]);
      if (a < threshold) {
        R[i][j] = G[i][j] = B[i][j] = 0.;
        nzeroed++;
      }
    }
  }

  return nzeroed;
}

static void
clip_matrix (double **A, int m, int n, int M)
{
  int                 i, j;

  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      if (A[i][j] < 0)
        A[i][j] = 0;
      else if (A[i][j] > M)
        A[i][j] = M;
      else
        A[i][j] = (int) (0.5 + A[i][j]);
    }
  }
}

static void
reduce_pgm_image (image_t * img, double rel_err)
{
  int                 zero_count;
  int                 m = img->pam.height;
  int                 n = img->pam.width;
  int                 M = img->pam.maxval;

  haar_transform_matrix (img->g, m, n, WT_FWD);
  zero_count = prune_matrix (img->g, m, n, rel_err);
  haar_transform_matrix (img->g, m, n, WT_REV);
  clip_matrix (img->g, m, n, M);
  printf ("Zeroed %d of %d wavelet coefficients, %d remaning\n",
          zero_count, m * n, m * n - zero_count);
}

static void
reduce_ppm_image (image_t * img, double rel_err)
{
  int                 zero_count;
  int                 m = img->pam.height;
  int                 n = img->pam.width;
  int                 M = img->pam.maxval;

  haar_transform_matrix (img->r, m, n, WT_FWD);
  haar_transform_matrix (img->g, m, n, WT_FWD);
  haar_transform_matrix (img->b, m, n, WT_FWD);
  zero_count = prune_rgb_matrices (img->r, img->g, img->b, m, n, rel_err);
  haar_transform_matrix (img->r, m, n, WT_REV);
  haar_transform_matrix (img->g, m, n, WT_REV);
  haar_transform_matrix (img->b, m, n, WT_REV);
  clip_matrix (img->r, m, n, M);
  clip_matrix (img->g, m, n, M);
  clip_matrix (img->b, m, n, M);

  printf ("Zeroed %d of %d wavelet coefficients, %d remaning\n",
          zero_count, m * n, m * n - zero_count);
}

static void
show_usage (char *progname)
{
  fprintf (stderr, "Usage: %s rel_err infile outfile \n", progname);
  fprintf (stderr, "1. Reads PPM or PPM image from  infile\n"
           "2. Applies the Haar wavelet transform\n"
           "3. Set as many of the smallest wavelet coefficients to zero\n"
           "   while keeping the relative (L2) error under rel_err\n"
           "4. Reconstructs iamge with the truncated coefficients\n"
           "   and writes to outfile\n");
}

int
main (int argc, char **argv)
{
  char               *infile, *outfile, *endptr;
  double              rel_err;
  image_t            *img;
  pam_t              *pam;

  /* Check arguments */
  if (argc != 4) {
    show_usage (argv[0]);
    return EXIT_FAILURE;
  }

  rel_err = strtod (argv[1], &endptr);
  if (*endptr != '\0' || rel_err < 0.0 || rel_err > 1.0) {
    show_usage (argv[0]);
    fprintf (stderr, "*** rel_err should be in (0,1)\n");
    return EXIT_FAILURE;
  }
  infile = argv[2];
  outfile = argv[3];

  /* Initialize  libnetpbm library */
  pm_init (argv[0], 0);
  img = read_image (infile);
  pam = &img->pam;
  if (pam->format == PGM_FORMAT || pam->format == RPGM_FORMAT)
    reduce_pgm_image (img, rel_err);
  else if (pam->format == PPM_FORMAT || pam->format == RPPM_FORMAT)
    reduce_ppm_image (img, rel_err);
  else {
    fprintf (stderr, "Neither a PGM nor a PPM file provided \n");
    return EXIT_FAILURE;
  }

  write_image (outfile, img);
  free_image (img);

  return EXIT_SUCCESS;
}
