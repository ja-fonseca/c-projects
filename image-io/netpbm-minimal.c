#include <stdio.h>
#include <pam.h>
#include "array.h"

int
main (int argc, char **argv)
{
  char               *infile = "lena.ascii.pgm";
  char               *outfile = "zz.pgm";
  struct pam          inpam;
  FILE               *fp;
  double            **A;
  tuple              *row;
  int                 i, j;

  pm_init (argv[0], 0);

  fp = pm_openr (infile);
  pnm_readpaminit (fp, &inpam, sizeof (inpam.tuple_type));
  printf ("image: %d x %d, depth: %d\n",
          inpam.width, inpam.height, inpam.depth);
  if (!(inpam.format == PGM_FORMAT || inpam.format == RPGM_FORMAT)) {
    fprintf (stderr, "This demo handles PGM images only\n");
    return EXIT_FAILURE;
  }

  make_matrix (A, inpam.height, inpam.width);
  row = pnm_allocpamrow (&inpam);
  for (i = 0; i < inpam.height; i++) {
    pnm_readpamrow (&inpam, row);
    for (j = 0; j < inpam.width; j++) {
      A[i][j] = row[j][0];
    }
  }
  pm_close (fp);

  for (i = 0; i < inpam.height && i < inpam.width; i++)
    A[i][i] = 0.0;

  fp = pm_openw (outfile);
  inpam.file = fp;
  inpam.plainformat = inpam.format == PGM_FORMAT ? 1 : 0;
  pnm_writepaminit (&inpam);

  for (i = 0; i < inpam.height; i++) {
    for (j = 0; j < inpam.width; j++) {
      row[j][0] = A[i][j];
    }
    pnm_writepamrow (&inpam, row);
  }
  pm_close (fp);

  free_matrix (A);
  pnm_freepamrow (row);
  return EXIT_SUCCESS;
}
