#include "bezier.h"

#include <math.h>
#include <stdint.h>

double kappa() {
  return 4.0 / 3.0 * (sqrt(2.0) - 1.0);
}

double c5(const Bezier * b, const DifferenceVector * dv) {
  return 3.0 * (dv->del_x[2] * b->p3.y - dv->del_y[2] * b->p3.x);
}

double c4(const Bezier * b, const DifferenceVector * dv) {
  return 3.0 / 5.0 * (2.0 * (dv->del_x[1] * b->p3.y - dv->del_y[1] * b->p3.x)
      + 3.0 * (dv->del_x[2] * b->p2.y - dv->del_y[2] * b->p2.x));
}

double c3(const Bezier * b, const DifferenceVector * dv) {
  return 3.0 / 10.0 * (
              (dv->del_x[0] * b->p3.y - dv->del_y[0] * b->p3.x)
      + 6.0 * (dv->del_x[1] * b->p2.y - dv->del_y[1] * b->p2.x)
      + 3.0 * (dv->del_x[2] * b->p1.y - dv->del_y[2] * b->p1.x));
}

double c2(const Bezier * b, const DifferenceVector * dv) {
  return 3.0 / 10.0 * (
        3.0 * (dv->del_x[0] * b->p2.y - dv->del_y[0] * b->p2.x)
      + 6.0 * (dv->del_x[1] * b->p1.y - dv->del_y[1] * b->p1.x)
      +       (dv->del_x[2] * b->p0.y - dv->del_y[2] * b->p0.x));
}

double c1(const Bezier * b, const DifferenceVector * dv) {
  return 3.0 / 5.0 * (
        3.0 * (dv->del_x[0] * b->p1.y - dv->del_y[0] * b->p1.x)
      + 2.0 * (dv->del_x[1] * b->p0.y - dv->del_y[1] * b->p0.x));
}

double c0(const Bezier * b, const DifferenceVector * dv) {
  return 3.0 * (dv->del_x[0] * b->p0.y - dv->del_y[0] * b->p0.x);
}

Bezier init_bezier(Point p0, Point p1, Point p2, Point p3) {
  Bezier b = {.p0 = p0, .p1 = p1, .p2 = p2, .p3 = p3, .qpbc = {0}};
  DifferenceVector dv = {
    .del_x = {b.p1.x - b.p0.x, b.p2.x - b.p1.x, b.p3.x - b.p2.x},
    .del_y = {b.p1.y - b.p0.y, b.p2.y - b.p1.y, b.p3.y - b.p2.y}
  };
  b.qpbc[0] = c0(&b, &dv);
  b.qpbc[1] = c1(&b, &dv);
  b.qpbc[2] = c2(&b, &dv);
  b.qpbc[3] = c3(&b, &dv);
  b.qpbc[4] = c4(&b, &dv);
  b.qpbc[5] = c5(&b, &dv);
  return b;
}

Point evaluate_bezier(const Bezier * b, double t) {
  double x = pow((1.0 - t), 3.0) * b->p0.x
    + 3.0 * pow((1.0 - t), 2.0) * t * b->p1.x
    + 3.0 * (1.0 - t) * pow(t, 2.0) * b->p2.x
    + pow(t, 3.0) * b->p3.x;
  double y = pow((1.0 - t), 3.0) * b->p0.y
    + 3.0 * pow((1.0 - t), 2.0) * t * b->p1.y
    + 3.0 * (1.0 - t) * pow(t, 2.0) * b->p2.y
    + pow(t, 3.0) * b->p3.y;
  return (Point){x, y};
}

double line_integral_normalize_factor(const Bezier * b) {
  double factor = 0.0;
  for (uint8_t i = 0; i < 6; i++) {
    factor += b->qpbc[i] / (double)(i + 1);
  }
  return 1.0 / factor;
}

double line_integral_unormalized(const Bezier * b, double normalize_factor, double t1, double t0) {
  double sum = 0.0;
  for (uint8_t i = 0; i < 6; i++) {
    sum += b->qpbc[i] * (pow(t1, (double)(i + 1)) - pow(t0, (double)(i + 1))) / (i + 1);
  }
  return sum * normalize_factor;
}

Bezier bezier_affine_transform(const Bezier * b, const Matrix m) {
  return init_bezier(exploit_point_mult(m, b->p0),
      exploit_point_mult(m, b->p1),
      exploit_point_mult(m, b->p2),
      exploit_point_mult(m, b->p3));
}
