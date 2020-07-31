#include <stdio.h>
#include <stdlib.h>
#include "array.h"

static int
myrandom (int n)
{
  return rand () / (RAND_MAX / n + 1);
}

static int
write_pbm (char **M, int m, int n, char *outfile)
{
  FILE               *fp = fopen (outfile, "w");

  if (fp == NULL) {
    printf ("Error opening file\n");
    return 0;
  }

  fprintf (fp, "%s %i %i\n", "P1", m, n);
  fprint_matrix (fp, "%i ", M, m, n);

  fclose (fp);
  return 1;
}

static char       **
make_random_matrix (int m, int n, double f)
{
  char              **M;
  int                 i, j, k;

  make_matrix (M, m, n);
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      M[i][j] = 0;
    }
  }
  k = 0;
  while (k < f * m * n) {
    i = myrandom (m);
    j = myrandom (n);
    if (M[i][j] == 0) {
      M[i][j] = 1;
      k++;
    }
  }
  return M;
}

static void
show_usage (char *progname)
{
  printf ("%s writes an mxn random bitmap"
          "to a file named 'outfile'\n", progname);
  printf ("f: fill ratio 0.0 <= f <= 1.0 \n");
  printf ("s: integer >= 1: seeds the random number generator\n");
}

int
main (int argc, char **argv)
{
  char              **M;
  int                 m,n;
  int                 s;
  double              f;
  char               *outfile="lala";
  char               *endptr;
  int                status = EXIT_FAILURE;

  if (argc != 6){
      show_usage(argv[0]);
      return status;
  }
  m = strtol(argv[1], &endptr, 10);
  if (*endptr != '\0' || m < 1){
      show_usage(argv[0]);
      return status;
  }
  n = strtol(argv[2], &endptr, 10);
  if (*endptr != '\0' || n < 1){
      show_usage(argv[0]);
      return status;
  }
  s = strtol(argv[3], &endptr, 10);
  if (*endptr != '\0' || s < 1){
      show_usage(argv[0]);
      return status;
  }
  f = strtod(argv[4], &endptr);
  if (*endptr != '\0' || f < 0 || f > 1){
      show_usage(argv[0]);
      return status;
  }
  outfile = argv[5];

  srand (s);
  M = make_random_matrix (m, n, f);
  if (write_pbm (M, m, n, outfile) == 1)
    status = EXIT_SUCCESS;

  free_matrix(M);

  return status;
}
