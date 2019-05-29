#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <svz/svz.h>
#include <svz/features.h>

svz_t *svz_new(uint16_t width, uint16_t height)
{
  svz_t *image;
  size_t index;

  image = malloc(sizeof(svz_t));
  if (!image) {
    return NULL;
  }
  
  image->width = width;
  image->height = height;
  image->options = 0;
  image->number_of_features = 0;
  //  image->data = NULL;

  svz_append_feature(image, DISPLAYED_PIXELS);
  svz_append_feature(image, SELECTED_PIXELS);
  
  return image;
}

void svz_free(svz_t *svz)
{
  free(svz);  
}

int svz_append_feature(svz_t *svz, svz_feature_type_t feature_type)
{
  printf("append feature\n");
  
  if (svz->number_of_features >= (SVZ_FEATURES_MAX)) {
    fprintf(stderr, "Error: reached maximum number of features (%d)\n", SVZ_FEATURES_MAX);
    return -1;
  }

  svz_features_set_type(&svz->features[svz->number_of_features], feature_type);
  svz_features_zero(svz, &svz->features[svz->number_of_features]);

  svz->number_of_features++;  
  
  return 0;
}

int svz_get_total_bits_indexes(svz_t *svz)
{
  return (svz->width * svz->height) % SVZ_BITFIELD_EL_SIZE;
}
