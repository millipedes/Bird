#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <stdint.h>

#include "bezier.h"

#ifdef __cplusplus
extern "C" {
#endif

#define QTY_ELLIPSE_CURVES 4

typedef struct ELLIPSE_T {
  Bezier curves[QTY_ELLIPSE_CURVES];
} Ellipse;

Ellipse init_ellipse(uint32_t x_len, uint32_t y_len, uint32_t x_center,
    uint32_t y_center);
void free_ellipse(Ellipse e);

#ifdef __cplusplus
}
#endif

#endif
