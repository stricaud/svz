#include <stdio.h>

#include <svz/svz.h>
#include <svz/encode.h>
#include <svz/image.h>
#include <svz/basic-shapes.h>
#include <svz/draw-text.h>

int main(void)
{
  svz_t *svz;

  svz = svz_new(1000, 1000);

  svz_draw_line(svz, 50, 1, 45, 45);
  
  /* svz_draw_line(svz, 1, 5, 20, 5); */
  /* svz_draw_line(svz, 1, 10, 100, 1); */
  /* svz_draw_rectangle(svz, 1, 1, 5, 6); */
  svz_draw_rectangle(svz, 53, 53, 695, 693);

//   svz_draw_text(svz, "Hello, world!", 1, 15);
  svz_draw_text(svz, "Hello, World!", 1, 15);

  /* svz_draw_text(svz, "Hello, World!", 30, 10); */
  
  
  svz_draw_point(svz, 1, 1);
  svz_draw_point(svz, 2, 2);
  svz_draw_point(svz, 3, 3);
  
  /* svz_image_pixels_debug(svz); */
  svz_image_write_gif(svz, "out.gif");
  svz_encode_to_file(svz, "out.svz");

  svz_free(svz);
}
