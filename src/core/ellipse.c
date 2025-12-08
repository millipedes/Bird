#include "ellipse.h"

#include <math.h> // for KAPPA

Ellipse init_ellipse(uint32_t x_len, uint32_t y_len, uint32_t x_center,
    uint32_t y_center) {
  Ellipse result = {{
    // Quadrant 1: (1,0) -> (0,1)
    (Bezier){
      {1.0, 0.0},
      {1.0, KAPPA},
      {KAPPA, 1.0},
      {0.0, 1.0}
    },
    // Quadrant 2: (0,1) -> (-1,0)
    (Bezier){
      {0.0, 1.0},
      {-KAPPA, 1.0},
      {-1.0, KAPPA},
      {-1.0, 0.0}
    },
    // Quadrant 3: (-1,0) -> (0,-1)
    (Bezier){
      {-1.0, 0.0},
      {-1.0, -KAPPA},
      {-KAPPA, -1.0},
      {0.0, -1.0}
    },
    // Quadrant 4: (0,-1) -> (1,0)
    (Bezier){
      {0.0, -1.0},
      {KAPPA, -1.0},
      {1.0, -KAPPA},
      {1.0, 0.0}
    }
  }};

  Matrix translate = affine_translate(x_center, y_center);
  Matrix scale = affine_scale(x_len, y_len);

  Matrix total_affine_transform = multiply_matrices(2, translate, scale);
  for (uint8_t i = 0; i < 4; i++) {
    result.curves[i] = bezier_affine_transform(&result.curves[i], total_affine_transform);
  } 
  return result;
}
