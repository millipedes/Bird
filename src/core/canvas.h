#ifndef CANVAS_H
#define CANVAS_H

#include <stdint.h>

#include "bezier.h"

typedef struct RGBA_PIXEL_T {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
} RGBAPixel;

typedef struct RGB_PIXEL_T {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} RGBPixel;

typedef union {
  RGBAPixel rgba;
  RGBPixel rgb;
} Pixel;

typedef struct CAVNAS_T {
  Pixel ** points;
  uint32_t len_x;
  uint32_t len_y;
  uint8_t no_channels;
} Canvas;

Canvas init_canvas(Pixel p, uint32_t len_x, uint32_t len_y, uint8_t no_channels);
Canvas draw_bezier(Canvas c, const Bezier * curve);
Canvas free_canvas(Canvas c);

#endif
