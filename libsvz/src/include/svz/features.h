#ifndef _SVZ_FEATURES_H_
#define _SVZ_FEATURES_H_

#include <stdint.h>
#include <stdlib.h>

enum _svz_feature_id_t {
        DISPLAYED_PIXELS,
	SELECTED_PIXELS,
	COLOR_FOR_PIXELS, // Using bitfields to allow one color
	COLOR256_FOR_PIXELS, // Using an array of char to map each color by pixel order
	KEY_VALUE,
	NOT_SET,
};
typedef enum _svz_feature_id_t svz_feature_id_t;

struct _svz_features_t {
        svz_feature_id_t feature_id;
        uint64_t bitfield;
        char *colors_list; 
        char *key;
        char *value;
};
typedef struct _svz_features_t svz_features_t;

svz_features_t *svz_features_new(void);
void svz_features_free(svz_features_t *features);  

#endif // _SVZ_FEATURES_H_
