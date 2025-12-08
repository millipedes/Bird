#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <stdint.h>

#include "bezier.h"

typedef struct ELLIPSE_T {
  Bezier curves[4];
} Ellipse;

Ellipse init_ellipse(uint32_t x_len, uint32_t y_len, uint32_t x_center,
    uint32_t y_center);

#endif
