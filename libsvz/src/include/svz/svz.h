#ifndef _SVZ_H_
#define _SVZ_H_

#include <stdio.h>
#include <stdint.h>

#define SVZ_MAGIC "SVZ1"

#define svz_set_bit(field, n) (field |= (1 << n))
#define svz_unset_bit(field, n) (field &= ~(1 << n))
#define svz_inverse_bit(field, n) (field ^= (1 << n))
#define svz_get_bit(field, n) (field & (1 << n))

enum _svz_options_t {
	SVZ_OPTION_ERROR,		   
};
typedef enum _svz_options_t svz_options_t;

struct _svz_data_t {
  uint8_t feature_id;
  size_t data_len;
  void *data;
};
typedef struct _svz_data_t svz_data_t;

struct _svz_t {
  uint16_t width;
  uint16_t height;
  svz_options_t options;
  uint8_t data_elements;
  svz_data_t **data;
};
typedef struct _svz_t svz_t;

svz_t *svz_new(uint16_t width, uint16_t height);
void svz_free(svz_t *svz);

#endif	/* _SVZ_H_ */
