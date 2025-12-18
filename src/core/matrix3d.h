#ifndef MATRIX_H
#define MATRIX_H

#include <stdarg.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct POINT_T {
  double x;
  double y;
} Point;

typedef struct {
  double m[3][3];
} Matrix;

Matrix exploit_matrix_mult(const Matrix m1, const Matrix m2);
Point exploit_point_mult(const Matrix m, const Point p);
Matrix multiply_matrices(uint8_t no_matrices, ...);

Matrix affine_translate(double x, double y);
Matrix affine_reflect_x();
Matrix affine_reflect_y();
Matrix affine_scale(double x, double y);
Matrix affine_rotate(double theta);
Matrix affine_Shear(double x, double y);

#ifdef __cplusplus
}
#endif

#endif
