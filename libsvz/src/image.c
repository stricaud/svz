#include <stdint.h>

#include <svz/svz.h>
#include <svz/image.h>

int svz_image_write_pixel(svz_t *svz, uint16_t x, uint16_t y)
{
  uint32_t pos;
  char left;
  uint64_t index;

  if (x > svz->width) {
    fprintf(stderr, "Error: given X (%d) greater than image width (%d)\n", x, svz->width);
    return -1;
  }
  if (y > svz->height) {
    fprintf(stderr, "Error: given Y (%d) greater than image height (%d)\n", x, svz->height);
    return -1;
  }
  
  pos = (svz->width * (y - 1)) + x;
  index = svz_bit_index(pos);
  left = pos - (index * SVZ_BITFIELD_EL_SIZE);

  printf("%s: x=%d, y=%d, pos=%ld,index=%d,left=%d\n", __FUNCTION__, x, y, pos, index, left);
  
  svz_set_bit(svz->features[0].bitfield[index], left);
  
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
  while (bitcount < (svz->width * svz->height)) {
    if (!(bitcount%svz->width)) {
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

}
