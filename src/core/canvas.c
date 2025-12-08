#include "canvas.h"

#include <math.h>
#include <stdlib.h>

Canvas init_canvas(Pixel p, uint32_t len_x, uint32_t len_y, uint8_t no_channels) {
  Canvas c = {0};
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

// Canvas draw_bezier(Canvas c, const Bezier * curve) {
//   for (int i = min_y; i < max_y; i++) {
//     for (int j = min_x; j < max_x; j++) {
//       Point p1 = {(double)j, (double)i};
//       Point p2 = {(double)(j+1), (double)(i+1)};
//       double coverage_fraction = fabs(compute_line_integral(curve, p1, p2) / compute_line_integral(curve, curve->p0, curve->p3));
//       if (coverage_fraction >= 0 && coverage_fraction <= 1.0) {
//         c.points[i][j].rgba = (RGBAPixel){
//           (uint8_t)(255.0 * coverage_fraction),
//           (uint8_t)(255.0 * coverage_fraction),
//           (uint8_t)(255.0 * coverage_fraction),
//           255};
//       }
//     }
//   }
//   for (double i = 0; i < 1.0; i += 0.001) {
//     double x = pow(1 - i, 3) * curve->p0.x + 3 * pow(1 - i, 2) * i * curve->p1.x + 3 * (1 - i) * pow(i, 2) * curve->p2.x + pow(i, 3) * curve->p3.x;
//     double y = pow(1 - i, 3) * curve->p0.y + 3 * pow(1 - i, 2) * i * curve->p1.y + 3 * (1 - i) * pow(i, 2) * curve->p2.y + pow(i, 3) * curve->p3.y;
//     c.points[(int)x][(int)y].rgba = (RGBAPixel){0, 255, 0, 255};
//   }
//   return c;
// }

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
