#include <stdio.h>

#include <svz/svz.h>
#include <svz/image.h>

int main(void)
{
  svz_t *svz;

  printf("%d->%d\n", 42, svz_bit_index(42));
  printf("%d->%d\n", 63, svz_bit_index(63));
  printf("%d->%d\n", 82, svz_bit_index(82));
  
  svz_image_defines_to_stdout();
  svz = svz_new(10, 10);
  /* svz_image_write_pixel(svz, 0,0); */
  svz_image_write_pixel(svz, 3,3);
  svz_image_write_pixel(svz, 5,5);
  svz_image_write_pixel(svz, 7,9);
  svz_image_write_pixel(svz, 10,10);
  svz_image_pixels_debug(svz);
  svz_free(svz);
}
