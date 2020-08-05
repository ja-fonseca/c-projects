#ifndef H_IMAGE_IO_H
#define H_IMAGE_IO_H
#include "pam.h"


typedef struct pam  pam_t;

typedef struct image
{
  pam_t             pam;
  double            **r;
  double            **g;
  double            **b;
} image_t;

image_t            *read_image (char *filename);

void                write_image (char *filename, image_t * img);

void                free_image (image_t * img);

#endif /* H_IMAGE_IO_H */
