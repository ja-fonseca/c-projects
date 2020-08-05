#include <stdio.h>
#include "image-io.h"

int main (int argc, char **argv)
{
    image_t *img ;

    /* Check arguments */
    if (argc != 3){
        fprintf(stderr, "Usage: %s infile outfile \n", argv[0]);
        fprintf(stderr, "Reads PGM or PPM from infile, "
                "writes identical image to outfile\n");
        return EXIT_FAILURE;
    }

    /* Initialize  libnetpbm library*/
    pm_init(argv[0], 0);

    /* Read infile, allocate space for image object
     * and print some data */
    img = read_image(argv[1]);
    printf("image is %dx%d pixels, depth=%d, maxval=%d\n",
           img->pam.height, img->pam.width,
           img->pam.depth, (int) img->pam.maxval);

    /* Write same image back to outfile*/
    write_image(argv[2], img);

    /* Free allocated memory*/
    free_image(img);

    return EXIT_SUCCESS;
}
