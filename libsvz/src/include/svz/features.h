#ifndef _SVZ_FEATURES_H_
#define _SVZ_FEATURES_H_

#include <stdint.h>
#include <stdlib.h>

#include <svz/defs.h>

enum _svz_feature_type_t {
        DISPLAYED_PIXELS,
	SELECTED_PIXELS,
	COLOR_FOR_PIXELS, // Using bitfields to allow one color
	COLOR256_FOR_PIXELS, // Using an array of char to map each color by pixel order
	KEY_VALUE,
	NOT_SET,
};
typedef enum _svz_feature_type_t svz_feature_type_t;

struct _svz_features_t {
        svz_feature_type_t type;
        uint64_t bitfield[IMAGE_MAX_INDEXES];
        char *colors_list;
        char *key;
        char *value;
};
typedef struct _svz_features_t svz_features_t;

svz_features_t *svz_features_new(void);
void svz_features_free(svz_features_t *features);  
int svz_features_set_type(svz_features_t *features, svz_feature_type_t type);

#endif // _SVZ_FEATURES_H_
