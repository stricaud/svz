#ifndef _SVZ_IMAGE_H_
#define _SVZ_IMAGE_H_

#include <stdint.h>

#include <svz/svz.h>
#include <svz/defs.h>

void svz_image_defines_to_stdout(void);
int svz_image_write_pixel(svz_t *svz, uint16_t x, uint16_t y);
int svz_image_write_pixel_safe(svz_t *svz, uint16_t x, uint16_t y);
void svz_image_pixels_debug(svz_t *svz);

#endif // _SVZ_IMAGE_H_
