#include "bezier.h"

#include <math.h>

// coeff of t^3
Point c3_cubric_bezier(const Bezier * curve) {
  double x = -curve->p0.x + 3 * curve->p1.x - 3 * curve->p2.x + curve->p3.x;
  double y = -curve->p0.y + 3 * curve->p1.y - 3 * curve->p2.y + curve->p3.y;
  return (Point){x, y};
}

// coeff of t^2
Point c2_cubric_bezier(const Bezier * curve) {
  double x = 3 * curve->p0.x - 6 * curve->p1.x + 3 * curve->p2.x;
  double y = 3 * curve->p0.y - 6 * curve->p1.y + 3 * curve->p2.y;
  return (Point){x, y};
}

// coeff of t^1
Point c1_cubric_bezier(const Bezier * curve) {
  double x = -3 * curve->p0.x + 3 * curve->p1.x;
  double y = -3 * curve->p0.y + 3 * curve->p1.y;
  return (Point){x, y};
}

// coeff of t^0
Point c0_cubric_bezier(const Bezier * curve) {
  return (Point){curve->p0.x, curve->p0.y};
}

Point del0(const Point c1, const Point c2, const Point c3) {
  double x = pow(c2.x, 2) - 3.0 * c3.x * c1.x;
  double y = pow(c2.y, 2) - 3.0 * c3.y * c1.y;
  return (Point){x, y};
}

Point del1(const Point c0, const Point c1, const Point c2, const Point c3) {
  double x = 2.0 * pow(c2.x, 3) - 9.0 * c3.x * c2.x * c1.x + 27.0 * pow(c3.x, 2) * c0.x;
  double y = 2.0 * pow(c2.y, 3) - 9.0 * c3.y * c2.y * c1.y + 27.0 * pow(c3.y, 2) * c0.y;
  return (Point){x, y};
}

Point u(const Point del0_instance, const Point del1_instance) {
  double discriminant_x = pow(del1_instance.x, 2) - 4.0 * pow(del0_instance.x, 3);
  // rounding errors
  if (discriminant_x < 0.0) discriminant_x = 0.0;
  double discriminant_y = pow(del1_instance.y, 2) - 4.0 * pow(del0_instance.y, 3);
  if (discriminant_y < 0.0) discriminant_y = 0.0;
  double x = cbrt((del1_instance.x + sqrt(discriminant_x)) / 2.0);
  double y = cbrt((del1_instance.y + sqrt(discriminant_y)) / 2.0);
  return (Point){x, y};
}

// Okay, being a little pedantic here, but better to be clear
double c5_quintic_line_integral() {
  return 0.0;
}

double c4_quintic_line_integral(const Point c2, const Point c3) {
  return c3.x * c2.y - c2.x * c3.y;
}

double c3_quintic_line_integral(const Point c1, const Point c3) {
  return 3.0 * (c3.x * c1.y - c3.y * c1.x);
}

double c2_quintic_line_integral(const Point c0, const Point c1,
    const Point c2, const Point c3) {
  return (c2.x * c1.y - c2.y * c1.x)
    + 2 * (c1.x * c2.y - c1.y * c2.x)
    + 3 * (c0.x * c3.y - c0.y * c3.x);
}

double c1_quintic_line_integral(const Point c0, const Point c2) {
  return 2 * (c0.x * c2.y - c0.y * c2.x);
}

double c0_quintic_line_integral(const Point c0, const Point c1) {
  return c0.x * c1.y - c0.y * c1.x;
}

// double compute_line_integral(const Bezier * curve, const Point p1, const Point p2) {
//   Point c0_instance = c0_cubric_bezier(curve);
//   Point c1_instance = c1_cubric_bezier(curve);
//   Point c2_instance = c2_cubric_bezier(curve);
//   Point c3_instance = c3_cubric_bezier(curve);
// 
//   double c0 = c0_quintic_line_integral(c0_instance, c1_instance);
//   double c1 = c1_quintic_line_integral(c0_instance, c2_instance);
//   double c2 = c2_quintic_line_integral(c0_instance, c1_instance, c2_instance,
//       c3_instance);
//   double c3 = c3_quintic_line_integral(c1_instance, c3_instance);
//   double c4 = c4_quintic_line_integral(c2_instance, c3_instance);
//   double c5 = c5_quintic_line_integral();
// 
//   Point t1 = t_at_point(curve, p1);
//   Point t2 = t_at_point(curve, p2);
// 
//   double t_start = fmin(t1.x, fmin(t1.y, fmin(t2.x, t2.y)));
//   double t_end = fmax(t1.x, fmax(t1.y, fmax(t2.x, t2.y)));
// 
//   return (
//       c5 * (pow(t_end, 6.0) - pow(t_start, 6.0)) / (5.0 + 1)
//       + c4 * (pow(t_end, 5.0) - pow(t_start, 5.0)) / (4.0 + 1)
//       + c3 * (pow(t_end, 4.0) - pow(t_start, 4.0)) / (3.0 + 1)
//       + c2 * (pow(t_end, 3.0) - pow(t_start, 3.0)) / (2.0 + 1)
//       + c1 * (pow(t_end, 2.0) - pow(t_start, 2.0)) / (1.0 + 1)
//       + c0 * (pow(t_end, 1.0) - pow(t_start, 1.0))
//       ) / 2.0;
// }

Bezier bezier_affine_transform(const Bezier * b, const Matrix m) {
  Bezier result = {0};
  result.p0 = exploit_point_mult(m, b->p0);
  result.p1 = exploit_point_mult(m, b->p1);
  result.p2 = exploit_point_mult(m, b->p2);
  result.p3 = exploit_point_mult(m, b->p3);
  return result;
}
