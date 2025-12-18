#ifndef BEZIER_H
#define BEZIER_H

#include <stdarg.h>

#include "matrix3d.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DIFFERENCE_VECTOR_T {
  double del_x[3];
  double del_y[3];
} DifferenceVector;

// Assumed to be cubic everywhere
typedef struct BEZIER_T {
  Point p0;
  Point p1;
  Point p2;
  Point p3;

  // quintic power basis coefficients
  double qpbc[6];
} Bezier;

double kappa();
Bezier init_bezier(Point p0, Point p1, Point p2, Point p3);
Point evaluate_bezier(const Bezier * b, double t);
double line_integral_normalize_factor(const Bezier * b);
double line_integral_unormalized(const Bezier * b, double normalize_factor, double t1, double t0);
Bezier bezier_affine_transform(const Bezier * b, const Matrix m);

#ifdef __cplusplus
}
#endif

#endif
