#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <svz/svz.h>
#include <svz/features.h>

svz_features_t *svz_features_new(void)
{
        svz_features_t *features;
	features = malloc(sizeof(svz_features_t));
	if (!features) {
	  return NULL;
	}
	/* features->type = NOT_SET; */
	/* features->bitfield = 0; */
	/* features->colors_list = NULL; */
	/* features->key = NULL; */
	/* features->value = NULL; */
	return features;
}

void svz_features_free(svz_features_t *features)
{
        free(features);
}

int svz_features_set_type(svz_features_t *features, svz_feature_type_t type)
{
  features->type = type;  
}

void svz_features_debug_displayed_pixels(svz_t *svz, svz_features_t *features)
{
  size_t bitcount = 0;

  while (bitcount < (svz->width * svz->height)) {
    if (!(bitcount%svz->width)) {
      printf("\n");
    }
    
    if (svz_get_bit(features->bitfield, bitcount)) {
      printf("1");
    } else {
      printf("0");
    }
    
    bitcount++;
  }
  printf("\n");

}

void svz_features_debug_selected_pixels(svz_t *svz, svz_features_t *features)
{
  svz_features_debug_displayed_pixels(svz, features);
}

void svz_features_zero(svz_t *svz, svz_features_t *features)
{
  int total_indexes = svz_get_total_bits_indexes(svz);
  memset(features->bitfield, 0, IMAGE_MAX_INDEXES * SVZ_BITFIELD_EL_SIZE);
}
