#ifndef CANVAS_H
#define CANVAS_H

#include <stdint.h>

#include "matrix3d.h"
#include "shape.h"

#ifdef __cplusplus
extern "C" {
#endif

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
  // coordinate transform matrix world -> viewing
  Matrix ctm;
  uint32_t len_x;
  uint32_t len_y;
  uint8_t no_channels;
} Canvas;

Canvas init_canvas(Pixel p, uint32_t len_x, uint32_t len_y, uint8_t no_channels,
    Matrix ctm);
Canvas draw_shape(Canvas c, Shape s, Pixel color);
Canvas free_canvas(Canvas c);

#ifdef __cplusplus
}
#endif

#endif
