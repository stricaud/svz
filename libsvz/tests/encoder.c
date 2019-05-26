#include <stdio.h>

#include <svz/svz.h>
#include <svz/encode.h>
#include <svz/image.h>
#include <svz/basic-shapes.h>

int main(void)
{
  svz_t *svz;

  svz = svz_new(10, 10);
  /* svz_draw_line(svz, 1, 1, 10, 10); */
  /* svz_draw_line(svz, 1, 10, 10, 1); */
  svz_draw_bresenham_circle(svz, 5, 5, 3);
  
  svz_image_pixels_debug(svz);
  
  svz_free(svz);
}
