#ifndef BEZIER_H
#define BEZIER_H

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "matrix3d.h"

#ifdef __cplusplus
extern "C" {
#endif

double kappa();

typedef struct DIFFERENCE_VECTOR_T {
  double del_x[3];
  double del_y[3];
} DifferenceVector;

// A little pedentic because point has the same memory layout, but I think it
// makes it more clear what is going on...
typedef struct T_BOUNDS_T {
  double t_begin;
  double t_end;
} TBounds;

typedef struct POINT_MAP_ENTRY_T {
  Point key;
  TBounds value;
  uint64_t hash;
  bool used;
} PointMapEntry;

typedef struct POINT_MAP_T {
  PointMapEntry * entries;
  size_t capacity;
  size_t size;
} PointMap;

PointMap init_point_map();
bool point_map_put(PointMap * m, const Point key, const TBounds value);
bool point_map_get(const PointMap * m, const Point key, TBounds * out);
void free_point_map(PointMap m);

// This structure is just used to store some expensive pre-computed values which
// this libary uses internally
typedef struct BEZIER_HELPER_T {
  // An unordered map from viewing space values to t values i.e.
  // pixel -> {t_begin, t_end}
  PointMap viewing_to_t;
  // quintic power basis coefficients
  double qpbc[6];
} BezierHelper;

// Assumed to be cubic everywhere
typedef struct BEZIER_T {
  BezierHelper helper;
  Point p0;
  Point p1;
  Point p2;
  Point p3;
} Bezier;

Bezier init_bezier(Point p0, Point p1, Point p2, Point p3);
Point evaluate_bezier(const Bezier * b, double t);
double line_integral_normalize_factor(const Bezier * b);
double line_integral_unormalized(const Bezier * b, double normalize_factor, double t1, double t0);
Bezier bezier_affine_transform(Bezier b, const Matrix m);
void free_bezier(Bezier b);

#ifdef __cplusplus
}
#endif

#endif
