#include <svz/features.h>

svz_features_t *svz_features_new(void)
{
        svz_features_t *features;
	features = malloc(sizeof(svz_features_t));
	if (!features) {
	  return NULL;
	}
	features->feature_id = NOT_SET;
	features->bitfield = 0;
	features->colors_list = NULL;
	features->key = NULL;
	features->value = NULL;
}

void svz_features_free(svz_features_t *features)
{
        free(features);
}
