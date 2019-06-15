#include <stdio.h>

#include <svz/svz.h>
#include <svz/decode.h>
#include <svz/image.h>

int main(void)
{
  svz_t *svz;

  svz = svz_decode_from_file("out.svz");
  svz_image_pixels_debug(svz);
  
  svz_free(svz);
}
