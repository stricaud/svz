#include <stdint.h>

#include <svz/svz.h>
#include <svz/image.h>

int svz_image_write_pixel(svz_t *svz, uint16_t x, uint16_t y)
{
  uint64_t pos;

  pos = x + y;
  
  /* svz_set_bit(svz->features[0].bitfield, 30); */
  
  return 0;
}

int svz_image_write_pixel_safe(svz_t *svz, uint16_t x, uint16_t y)
{
  if ((x <= svz->width) || (y <= svz->height)) {
    return -1;
  }
  
  svz_image_write_pixel(svz, x, y);
  
  return 0;
}

void svz_image_pixels_debug(svz_t *svz)
{
  uint16_t w;
  uint16_t h;
  char bit;
  size_t bitcount = 0;
  size_t index = 0;
  
  uint64_t n = svz->features[0].bitfield[index];
  while (bitcount < IMAGE_MAX_BITS) {
    if (!(bitcount%IMAGE_MAX_WIDTH)) {
      printf("\n");
    }
    if (!(bitcount%64)) {
      index++;
      n = svz->features[0].bitfield[index];      
    }
    if (n & 1) {
      printf("1");
    } else {
      printf("0");
    }    
    n >>= 1;
    bitcount++;
  }
  printf("\n");
}

void svz_image_defines_to_stdout(void)
{
  printf("IMAGE_MAX_WIDTH:%d\n", IMAGE_MAX_WIDTH);
  printf("IMAGE_MAX_HEIGHT:%d\n", IMAGE_MAX_HEIGHT);
  printf("IMAGE_MAX_BITS:%d\n", IMAGE_MAX_BITS);
  printf("IMAGE_MAX_INDEXES:%d\n", IMAGE_MAX_INDEXES);
  printf("IMAGE_BITS ARRAY SIZE:%d\n", IMAGE_BITS_ARRAY_SIZE);

}
