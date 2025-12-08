#include "matrix3d.h"

#include <math.h>

Matrix exploit_matrix_mult(const Matrix m1, const Matrix m2) {
  return (Matrix){{
    {
      m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0],
      m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1],
      m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2],
    },
    {
      m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0],
      m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1],
      m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2],
    },
    {
      m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0],
      m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1],
      m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2],
    }
  }};
}

Point exploit_point_mult(const Matrix m, const Point p) {
  return (Point){
    m.m[0][0] * p.x + m.m[0][1] * p.y + m.m[0][2],
    m.m[1][0] * p.x + m.m[1][1] * p.y + m.m[1][2]
  };
}

Matrix multiply_matrices(uint8_t no_matrices, ...) {
  va_list args;
  va_start(args, no_matrices);

  Matrix result = va_arg(args, Matrix);
  for (uint8_t i = 1; i < no_matrices; i++) {
    result = exploit_matrix_mult(result, va_arg(args, Matrix));
  }

  va_end(args);
  return result;
}

Matrix affine_translate(double x, double y) {
  return (Matrix){{
    {1, 0, x},
    {0, 1, y},
    {0, 0, 1}
  }};
}

Matrix affine_reflect() {
  return (Matrix){{
    {-1, 0, 0},
    {0,  1, 0},
    {0,  0, 1}
  }};
}

Matrix affine_scale(double x, double y) {
  return (Matrix){{
    {x, 0, 0},
    {0, y, 0},
    {0, 0, 1}
  }};
}

// double degrees_to_radians(double theta) { return theta * M_PI / 180.0; }
double degrees_to_radians(double theta) { return theta * 3.14 / 180.0; }

Matrix affine_rotate(double theta) {
  return (Matrix){{
    {cos(theta), -sin(theta), 0},
    {sin(theta),  cos(theta), 0},
    {         0,           0, 1}
  }};
}

Matrix affine_Shear(double x, double y) {
  return (Matrix){{
    {1, x, 0},
    {y, 1, 0},
    {0, 0, 1}
  }};
}
