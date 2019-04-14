#ifndef _SVZ_H_
#define _SVZ_H_

#include <stdint.h>

#define SVZ_MAGIC "SVZ1"

enum _svz_options_t {
	SVZ_OPTION_ERROR,		   
};
typedef enum _svz_options_t svz_options_t;

struct _svz_data_t {
  uint8_t feature_id;
  void *data;
};
typedef struct _svz_data_t svz_data_t;

struct _svz_t {
  uint16_t width;
  uint16_t height;
  svz_options_t options;
  uint8_t data_len;
  svz_data_t **data;
};
typedef struct _svz_t svz_t;

#endif	/* _SVZ_H_ */
