#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

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

void svz_features_reset(svz_features_t *features)
{
        int i;

	features->type = NOT_SET;
	memset(&features->bitfield, 0, IMAGE_MAX_INDEXES);
	features->colors_list = NULL;
	features->key = NULL;
	features->value = NULL;
}

void svz_features_free(svz_features_t *features)
{
        free(features);
}

int svz_features_set_type(svz_features_t *features, svz_feature_type_t type)
{
  features->type = type;  
  return 0;
}

int svz_feature_selected_pixels_select_all(svz_features_t *feature) {
  if (feature->type != SELECTED_PIXELS) {
    fprintf(stderr, "Error, selecting pixels from a non selected pixels feature type\n");
    return -1;
  }
  memset(&feature->bitfield, INT32_MAX, IMAGE_MAX_INDEXES);
}

void svz_features_debug_displayed_pixels(svz_t *svz, svz_features_t *features)
{
  size_t bitcount = 0;
  int arraypos;
  
  while (bitcount < (svz->width * svz->height)) {
    if (!(bitcount%svz->width)) {
      printf("\n");
    }

    /* printf("(%d:%d)", (bitcount/SVZ_BITFIELD_EL_SIZE), bitcount%SVZ_BITFIELD_EL_SIZE); */
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

