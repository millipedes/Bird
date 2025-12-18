#include "canvas.h"

#include <stdlib.h>

Canvas init_canvas(Pixel p, uint32_t len_x, uint32_t len_y, uint8_t no_channels,
    Matrix ctm) {
  Canvas c = {0};

  c.ctm = ctm;

  c.points = (Pixel **)calloc(len_y, sizeof(Pixel *));
  for (uint32_t i = 0; i < len_y; i++) {
    c.points[i] = (Pixel *)calloc(len_x, sizeof(Pixel));
  }

  for (uint32_t i = 0; i < len_y; i++) {
    for (uint32_t j = 0; j < len_x; j++) {
      c.points[i][j] = p;
    }
  }
  c.len_x = len_x;
  c.len_y = len_y;
  c.no_channels = no_channels;
  return c;
}

Canvas free_canvas(Canvas c) {
  for (uint32_t i = 0; i < c.len_y; i++) {
    if (c.points[i]) {
      free(c.points[i]);
    }
  }
  if (c.points) {
    free(c.points);
  }
}
