#include <stdint.h>

#include <svz/svz.h>
#include <svz/image.h>

void _draw_bresenham_line_low(svz_t *svz, int x1, int y1, int x2, int y2)
{
  int dx = x2 - x1;
  int dy = y2 - y1;
  int D, yi, y;
  
  yi = 1;
  if (dy < 0) {
      yi = -1;
      dy = -dy;
  }
  D = 2*dy - dx;
  y = y1;

  for (int x = x1; x <= x2; x++) {
    svz_image_write_pixel(svz, x, y);
    if (D > 0) {
      y = y + yi;
      D = D - 2*dx;
    }
    D = D + 2*dy;
  }
}

void _draw_bresenham_line_high(svz_t *svz, int x1, int y1, int x2, int y2)
{
  int dx = x2 - x1;
  int dy = y2 - y1;
  int D, xi, x;
  
  xi = 1;
  if (dx < 0) {
    xi = -1;
    dx = -dx;
  }
  D = 2*dx - dy;
  x = x1;

  for (int y = y1; y <= y2; y++) {
    svz_image_write_pixel(svz, x, y);
    if (D > 0) {
      x = x + xi;
      D = D - 2*dy;
    }
    D = D + 2*dx;
  }
}

void svz_draw_bresenham_line(svz_t *svz, int x1, int y1, int x2, int y2) {
  if (abs(y2 - y1) < abs(x2 - x1)) {
    if (x1 > x2) {
      _draw_bresenham_line_low(svz, x2, y2, x1, y1);
    } else {
      _draw_bresenham_line_low(svz, x1, y1, x2, y2);
    }
  } else {
    if (y1 > y2) {
      _draw_bresenham_line_high(svz, x2, y2, x1, y1);
    } else {
      _draw_bresenham_line_high(svz, x1, y1, x2, y2);
    }
  }
}

void svz_draw_bresenham_buggyfast_line(svz_t *svz, int x1, int y1, int x2, int y2)
{
  int dx = x2 - x1;
  int dy = y2 - y1;
  int D = 2 * dy - dx;
  int y = y1;

  for (int x = x1; x <= x2; x++) {
    svz_image_write_pixel(svz, x, y);
    if (D > 0) {
      y++;
      D = D - 2*dx;
    }
    D = D + 2*dy;
  }

}

void svz_draw_line(svz_t *svz, int x1, int y1, int x2, int y2)
{
  svz_draw_bresenham_line(svz, x1, y1, x2, y2);
}

void _draw_bresenham_circle_subsequence_points(svz_t *svz, int xc, int yc, int x, int y)
{
  svz_image_write_pixel(svz, xc+x, yc+y);
  svz_image_write_pixel(svz, xc-x, yc+y);
  svz_image_write_pixel(svz, xc+x, yc-y);
  svz_image_write_pixel(svz, xc-x, yc-y);
  
  svz_image_write_pixel(svz, xc+y, yc+x);
  svz_image_write_pixel(svz, xc-y, yc+x);
  svz_image_write_pixel(svz, xc+y, yc-x);
  svz_image_write_pixel(svz, xc-y, yc-x);  
}

void svz_draw_bresenham_circle(svz_t *svz, int xc, int yc, int r)
{
  int x = 0;
  int y = r;
  int D = 3 - 2 * r;
  _draw_bresenham_circle_subsequence_points(svz, xc, yc, x, y);
  while (y >= x) {
    x++;
    if (D > 0) {
      y--;
      D = D + 4 * (x - y) + 10;
    } else {
      D = D + 4 * x + 6;
    }
    _draw_bresenham_circle_subsequence_points(svz, xc, yc, x, y);    
  }
}

void svz_draw_circle(svz_t *svz, int x, int y, int r)
{
  svz_draw_bresenham_circle(svz, x, y, r);
}
