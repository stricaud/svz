#include <stdio.h>
#include <string.h>

#include <svz/svz.h>
#include <svz/image.h>

#include <ft2build.h>
#include FT_FREETYPE_H

int draw_bitmap(svz_t *svz, int max_height, int actual_top, FT_Bitmap *bitmap, FT_Int x, FT_Int y)
{
	FT_Int  i, j, p, q;
	FT_Int  x_max = x + bitmap->width;
	FT_Int  y_max = y + bitmap->rows;
	unsigned char ch;
	int padding = 0;

 	x++; y++;

	if (!bitmap->rows) { return 0; } // We have a space

	for ( j = y, q = 0; j < y_max; j++, q++ )
	{
		for ( i = x, p = 0; i < x_max; i++, p++ ){
			ch = bitmap->buffer[q * bitmap->width + p];
			if (ch) {
			  if (max_height != actual_top) {
			    padding = max_height - actual_top;
			  }
			  svz_image_write_pixel(svz, i, j+padding);
			} 
		}
	}
	
	return 0;
}

int svz_draw_text(svz_t *svz, char *str, int x, int y)
{
  FT_Library ft2lib;
  FT_Error error;
  FT_Face face;
  FT_UInt char_index;
  int pen_x, pen_y;
  int max_height = 0;
  
  size_t strlength;

  
  error = FT_Init_FreeType(&ft2lib);
  if (error) {
    fprintf(stderr, "Error Loading FreeType2 Library\n");
    return -1;
  }

  error = FT_New_Face(ft2lib, "/usr/share/fonts/gnu-free/FreeSans.ttf", 0, &face);
  if (error) {
    fprintf(stderr, "Error loading font\n");
    return -1;
  }

  error = FT_Set_Pixel_Sizes(face, 15 /* pixel width */, 15 /* pixel height*/);
  /* if (error) { */
  /*   fprintf(stderr, "Error Setting Pixel Size\n"); */
  /*   return -1; */
  /* } */
  /* error = FT_Set_Char_Size(face, 0, 16 * 64, 50 /\* horizontal dpi *\/, 0 /\* vertical dpi*\/); */
  /* error = FT_Set_Char_Size(face, 24, 24, 100 /\* horizontal dpi *\/, 100 /\* vertical dpi*\/); */
  if (error) {
    fprintf(stderr, "Error Setting Char Size\n");
    return -1;
  }

  strlength = strlen(str);

  // Get the max glyph length
  for (int i = 0; i < strlength; i++) {
    char_index = FT_Get_Char_Index(face, str[i]);

    error = FT_Load_Glyph(face, char_index,  FT_LOAD_DEFAULT);
    if (error) {
      fprintf(stderr, "Error Loading Glyph\n");
      return -1;
    }

    error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
    if (error) {
      fprintf(stderr, "Error Rendering Glyph\n");
      return -1;
    }

    if (face->glyph->bitmap_top > max_height) {
      max_height = face->glyph->bitmap_top;
    }
  }

  pen_x = x;
  pen_y = y;
  for (int i = 0; i < strlength; i++) {
    char_index = FT_Get_Char_Index(face, str[i]);

    error = FT_Load_Glyph(face, char_index,  FT_LOAD_DEFAULT);
    if (error) {
      fprintf(stderr, "Error Loading Glyph\n");
      return -1;
    }

    error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
    if (error) {
      fprintf(stderr, "Error Rendering Glyph\n");
      return -1;
    }

    /* printf("drawing %c (top:%d) (rows:%d) (mah:%d)\n", str[i], face->glyph->bitmap_top, face->glyph->bitmap.rows); */
    draw_bitmap(svz, max_height, face->glyph->bitmap.rows, &face->glyph->bitmap,
		pen_x + face->glyph->bitmap_left,
		pen_y + face->glyph->bitmap_top - face->glyph->bitmap.rows);

    pen_x += (face->glyph->advance.x >> 6) + 1;
    pen_y += (face->glyph->advance.y >> 6);
  }

  
  FT_Done_Face(face);
  FT_Done_FreeType(ft2lib);
  
  return 0;
}
