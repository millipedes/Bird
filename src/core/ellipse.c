#include "ellipse.h"

Ellipse init_ellipse(uint32_t x_len, uint32_t y_len, uint32_t x_center,
    uint32_t y_center) {
  Ellipse result = (Ellipse){{
    // Quadrant 1: (1,0) -> (0,1)
    init_bezier((Point){1.0, 0.0}, (Point){1.0, kappa()},
        (Point){kappa(), 1.0}, (Point){0.0, 1.0}),
    // Quadrant 2: (0,1) -> (-1,0)
    init_bezier((Point){0.0, 1.0}, (Point){-kappa(), 1.0},
        (Point){-1.0, kappa()}, (Point){-1.0, 0.0}),
    // Quadrant 3: (-1,0) -> (0,-1)
    init_bezier((Point){-1.0, 0.0}, (Point){-1.0, -kappa()},
        (Point){-kappa(), -1.0}, (Point){0.0, -1.0}),
    // Quadrant 4: (0,-1) -> (1,0)
    init_bezier((Point){0.0, -1.0}, (Point){kappa(), -1.0},
        (Point){1.0, -kappa()}, (Point){1.0, 0.0})
  }};

  Matrix total_affine_transform = multiply_matrices(2,
      affine_translate(x_center, y_center),
      affine_scale(x_len, y_len));
  for (uint8_t i = 0; i < 4; i++) {
    result.curves[i] = bezier_affine_transform(&result.curves[i],
        total_affine_transform);
  } 
  return result;
}
