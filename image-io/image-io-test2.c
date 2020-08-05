#include <stdio.h>
#include "image-io.h"

int main (int argc, char **argv)
{
    int i,j;
    double avg;
    image_t *img ;

    /* Check arguments */
    if (argc != 3){
        fprintf(stderr, "Usage: %s infile outfile \n", argv[0]);
        fprintf(stderr, "Reads PPM from infile and converts it"
                "to gray scaled pgm, the result is written to outfile\n");
        return EXIT_FAILURE;
    }

    /* Initialize  libnetpbm library*/
    pm_init(argv[0], 0);

    /* Read infile, allocate space for image object, check
     * for ppm input  and print some data if ppm file is provided */
    img = read_image(argv[1]);
    if (img->pam.format == PGM_FORMAT || img->pam.format == RPGM_FORMAT){
        fprintf (stderr, "error: expected PPM image as input\n");
        exit (EXIT_FAILURE);
    }
    printf("image is %dx%d pixels, depth=%d, maxval=%d\n",
           img->pam.height, img->pam.width,
           img->pam.depth, (int) img->pam.maxval);

    /* Change to rpgm format */
    img->pam.format = RPGM_FORMAT;
    img->pam.depth = 1;

    /* Replace G value by weighted-average of the RGB values */
    for (i = 0; i < img->pam.height; i++) {
      for (j = 0; j < img->pam.width; j++) {
        avg = (77 * img->r[i][j] +
               150 * img->g[i][j] + 29 * img->b[i][j]) / 256.0 ;
        img->g[i][j] = (int)(0.5 + avg);
      }
    }

    /* Write modified image to outfile */
    write_image(argv[2], img);

    /* Free allocated memory*/
    free_image(img);

    return EXIT_SUCCESS;
}
