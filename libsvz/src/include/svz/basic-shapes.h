#ifndef _SVZ_BASIC_SHAPES_H_
#define _SVZ_BASIC_SHAPES_H_

void svz_draw_bresenham_line(svz_t *svz, int x1, int y1, int x2, int y2);
void svz_draw_line(svz_t *svz, int x1, int y1, int x2, int y2);
void svz_draw_bresenham_circle(svz_t *svz, int xc, int yc, int r);
void svz_draw_circle(svz_t *svz, int xc, int yc, int r);
void svz_draw_rectangle(svz_t *svz, int x, int y, int width, int height);

#endif	/* _SVZ_BASIC_SHAPES_H_ */
