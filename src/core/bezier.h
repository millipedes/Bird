#ifndef BEZIER_H
#define BEZIER_H

#include <stdarg.h>

#include "matrix3d.h"

#define KAPPA 4.0 / 3.0 * (sqrt(2) - 1)

// Assumed to be cubic everywhere
typedef struct BEZIER_T {
  Point p0;
  Point p1;
  Point p2;
  Point p3;
} Bezier;

double compute_line_integral(const Bezier * curve, const Point p1, const Point p2);
Bezier bezier_affine_transform(const Bezier * b, const Matrix m);

#endif
