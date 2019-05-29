#ifndef _SVZ_FEATURES_H_
#define _SVZ_FEATURES_H_

#include <stdint.h>
#include <stdlib.h>

#include <svz/defs.h>

typedef struct _svz_t svz_t;

#define SVZ_DISPLAYED_PIXELS_INDEX 0 /* Pixels are *always* on the first position */
#define SVZ_SELECTED_PIXELS_INDEX 1 /* Selected Pixels are *always* on the second position */

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
        int bitfield[IMAGE_MAX_INDEXES];
        char *colors_list;
        char *key;
        char *value;
};
typedef struct _svz_features_t svz_features_t;

svz_features_t *svz_features_new(void);
void svz_features_free(svz_features_t *features);  
int svz_features_set_type(svz_features_t *features, svz_feature_type_t type);
void svz_features_debug_displayed_pixels(svz_t *svz, svz_features_t *features);
void svz_features_debug_selected_pixels(svz_t *svz, svz_features_t *features);
void svz_features_zero(svz_t *svz, svz_features_t *features);

#endif // _SVZ_FEATURES_H_
