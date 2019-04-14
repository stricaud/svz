#include <stdint.h>
#include <stdlib.h>

#include <svz/svz.h>

svz_t *svz_new(uint16_t width, uint16_t height)
{
  svz_t *image;

  image = malloc(sizeof(svz_t));
  if (!image) {
    return NULL;
  }
  
  image->width = width;
  image->height = height;
  image->options = 0;
  image->data_elements = 0;
  image->data = NULL;

  return image;
}

void svz_free(svz_t *svz)
{
  free(svz);  
}
