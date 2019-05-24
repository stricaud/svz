#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
