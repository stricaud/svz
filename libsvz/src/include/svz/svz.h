#ifndef _SVZ_H_
#define _SVZ_H_

#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include <svz/features.h>

#define SVZ_MAGIC "SVZ1"

#define SVZ_BITFIELD_EL_SIZE 64

#define svz_set_bit(field, n) (field |= (1 << n))
#define svz_unset_bit(field, n) (field &= ~(1 << n))
#define svz_inverse_bit(field, n) (field ^= (1 << n))
#define svz_get_bit(field, n) (field & (1 << n))
#define svz_bit_index(n) (int)floor((double)n/SVZ_BITFIELD_EL_SIZE)

enum _svz_options_t {
	SVZ_OPTION_ERROR,		   
};
typedef enum _svz_options_t svz_options_t;

struct _svz_t {
  uint16_t width;
  uint16_t height;
  svz_options_t options;
  uint8_t number_of_features;
  svz_features_t features[255];
};
typedef struct _svz_t svz_t;

svz_t *svz_new(uint16_t width, uint16_t height);
void svz_free(svz_t *svz);

#endif	/* _SVZ_H_ */
