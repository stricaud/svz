#include <stdint.h>
#include <stdlib.h>

#include <svz/svz.h>
#include <svz/features.h>

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
  image->number_of_features = 1;
  //  image->data = NULL;

  svz_features_set_type(&image->features[0], DISPLAYED_PIXELS);
  
  return image;
}

void svz_free(svz_t *svz)
{
  free(svz);  
}
