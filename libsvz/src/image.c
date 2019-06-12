#include <stdint.h>

#include <gif_lib.h>

#include <svz/svz.h>
#include <svz/image.h>
#include <svz/gif-palette.h>

#define GIF_EXP_COLORS 8

int svz_image_write_pixel(svz_t *svz, uint16_t x, uint16_t y)
{
  uint32_t pos;
  char left;
  uint64_t index;

  if ((x <= 0) || (y <= 0)) {
    fprintf(stderr, "Error: pixel position starts at 1\n");
    return -1;
  }
  
  x--; y--; 			/* We start at 1,1 not 0,0 */
  
  if (x > svz->width) {
    fprintf(stderr, "Error: given X (%d) greater than image width (%d)\n", x, svz->width);
    return -1;
  }
  if (y > svz->height) {
    fprintf(stderr, "Error: given Y (%d) greater than image height (%d)\n", x, svz->height);
    return -1;
  }
  
  pos = x * svz->width + y;
  svz_set_bit(svz->features[0].bitfield, pos);

  return 0;
}

void svz_image_pixels_debug(svz_t *svz)
{  
  size_t bitcount = 0;

  printf("number of features:%d\n", svz->number_of_features);
  for (int i = 0; i < svz->number_of_features; i++) {
    switch(svz->features[i].type) {
    case DISPLAYED_PIXELS:
      printf("\nDISPLAYED_PIXELS\n");
      svz_features_debug_displayed_pixels(svz, &svz->features[i]);
      break;
    case SELECTED_PIXELS:
      printf("\nSELECTED_PIXELS\n");
      svz_features_debug_selected_pixels(svz, &svz->features[i]);
      break;
    default:
      fprintf(stderr, "%s Error[%d]: unknown feature type: %d\n", __FUNCTION__, i, svz->features[i].type);
      break;
    }
  }
  
}

static void print_bin(uint64_t n)
{
  if (n > 1) {
    print_bin(n>>1);
  }
  printf("%d", n & 1);
}

void svz_image_defines_to_stdout(void)
{
  printf("IMAGE_MAX_WIDTH:%d\n", IMAGE_MAX_WIDTH);
  printf("IMAGE_MAX_HEIGHT:%d\n", IMAGE_MAX_HEIGHT);
  printf("IMAGE_MAX_BITS:%d\n", IMAGE_MAX_BITS);
  printf("IMAGE_MAX_INDEXES:%d\n", IMAGE_MAX_INDEXES);

}

void svz_image_write_gif(svz_t *svz, char *gif_file_path)
{
  ColorMapObject *gif_cmap = NULL;
  GifColorType *gif_color = NULL;
  GifFileType *gif_file = NULL; 
  GifPixelType pixel;
  int error;
  size_t bitcount = 0;

  gif_cmap = GifMakeMapObject(256, NULL);
  if (!gif_cmap) {
    fprintf(stderr, "Error allocating color map\n");
    return;
  }
  
  for (int i = 0; i < GIF_COLOR_COUNT; i++) {
    gif_cmap->Colors[i].Red = (unsigned char)palette[i][0];
    gif_cmap->Colors[i].Green = (unsigned char)palette[i][1];
    gif_cmap->Colors[i].Blue = (unsigned char)palette[i][2];
  }

  gif_file = EGifOpenFileName(gif_file_path, 0, &error);
  if (!gif_file) {
    fprintf(stderr, "Error creating gif file\n");
    return;
  }
  EGifSetGifVersion(gif_file, 1);
  error = EGifPutScreenDesc(gif_file, svz->width, svz->height, GIF_EXP_COLORS, 0, gif_cmap);
  error = EGifPutImageDesc(gif_file, 0, 0, svz->width, svz->height, 0, NULL);
  
  while (bitcount < (svz->width * svz->height)) {
    if (svz_get_bit(svz->features[0].bitfield, bitcount)) {
      if (svz_get_bit(svz->features[1].bitfield, bitcount)) {
	error = EGifPutPixel(gif_file, GIF_COLOR_BLACK);
      } else {
	error = EGifPutPixel(gif_file, 55);
      }
    } else {
      error = EGifPutPixel(gif_file, GIF_COLOR_WHITE);
    }
    
    bitcount++;
  }
  
  EGifSpew(gif_file);
                       
  EGifCloseFile(gif_file, &error);
  GifFreeMapObject(gif_cmap);
  /* GifFreeSavedImages(gif_file); */
  
}

