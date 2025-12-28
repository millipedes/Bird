#include "bezier.h"

#include <math.h>
#include <string.h>

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

// FNV-1a
// offset basis: 1469598103934665603
// prime: 1099511628211
uint64_t hash_point(const Point * p) {
  uint64_t hx, hy;
  memcpy(&hx, &p->x, sizeof(hx));
  memcpy(&hy, &p->y, sizeof(hy));

  uint64_t h = 1469598103934665603ULL;
  h ^= hx;
  h *= 1099511628211ULL;
  h ^= hy;
  h *= 1099511628211ULL;
  return h;
}

bool point_map_resize(PointMap * m, size_t new_cap) {
  PointMapEntry * old = m->entries;
  size_t old_cap = m->capacity;

  PointMapEntry * ne = calloc(new_cap, sizeof(PointMapEntry));
  if (!ne) {
    return false;
  }

  m->entries = ne;
  m->capacity = new_cap;
  m->size = 0;

  for (size_t i = 0; i < old_cap; i++) {
    if (old[i].used) {
      size_t j = old[i].hash % m->capacity;
      for (;;) {
        PointMapEntry *e = &m->entries[j];
        if (!e->used) {
          *e = old[i];
          m->size++;
          break;
        }
        j = (j + 1) % m->capacity;
      }
    }
  }

  free(old);
  return true;
}

PointMap init_point_map() {
  PointMap m = {0};
  m.size = 0;
  m.capacity = 16;
  m.entries = calloc(m.capacity, sizeof(PointMapEntry));
  return m;
}

bool point_map_put(PointMap * m, const Point key, const TBounds value) {
  if ((m->size + 1) * 10 >= m->capacity * 7) {
    if (!point_map_resize(m, m->capacity * 2)) {
      return false;
    }
  }

  uint64_t h = hash_point(&key);
  size_t i = h % m->capacity;

  for (;;) {
    PointMapEntry *e = &m->entries[i];

    if (!e->used) {
      e->used = true;
      e->hash = h;
      e->key = key;
      e->value = value;
      m->size++;
      return true;
    }

    if (e->hash == h && point_eq(e->key, key)) {
      e->value = value;
      return true;
    }

    i = (i + 1) % m->capacity;
  }
}

bool point_map_get(const PointMap * m, const Point key, TBounds * out) {
  if (!m->entries) {
    return false;
  }

  uint64_t h = hash_point(&key);
  size_t i = h % m->capacity;

  for (;;) {
    const PointMapEntry *e = &m->entries[i];

    if (!e->used) {
      return false;
    }

    if (e->hash == h && point_eq(e->key, key)) {
      *out = e->value;
      return true;
    }

    i = (i + 1) % m->capacity;
  }
}

void free_point_map(PointMap m) {
  if (m.entries) {
    free(m.entries);
  }
  m.entries = NULL;
  m.capacity = 0;
  m.size = 0;
}

Bezier init_bezier(Point p0, Point p1, Point p2, Point p3) {
  Bezier b = {.p0 = p0, .p1 = p1, .p2 = p2, .p3 = p3, .helper = {0}};
  DifferenceVector dv = {
    .del_x = {b.p1.x - b.p0.x, b.p2.x - b.p1.x, b.p3.x - b.p2.x},
    .del_y = {b.p1.y - b.p0.y, b.p2.y - b.p1.y, b.p3.y - b.p2.y}
  };
  b.helper.qpbc[0] = c0(&b, &dv);
  b.helper.qpbc[1] = c1(&b, &dv);
  b.helper.qpbc[2] = c2(&b, &dv);
  b.helper.qpbc[3] = c3(&b, &dv);
  b.helper.qpbc[4] = c4(&b, &dv);
  b.helper.qpbc[5] = c5(&b, &dv);
  b.helper.viewing_to_t = init_point_map();
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
    factor += b->helper.qpbc[i] / (double)(i + 1);
  }
  return 1.0 / factor;
}

double line_integral_unormalized(const Bezier * b, double normalize_factor, double t1, double t0) {
  double sum = 0.0;
  for (uint8_t i = 0; i < 6; i++) {
    sum += b->helper.qpbc[i] * (pow(t1, (double)(i + 1)) - pow(t0, (double)(i + 1))) / (i + 1);
  }
  return sum * normalize_factor;
}

Bezier bezier_affine_transform(Bezier b, const Matrix m) {
  b.p0 = exploit_point_mult(m, b.p0);
  b.p1 = exploit_point_mult(m, b.p1);
  b.p2 = exploit_point_mult(m, b.p2);
  b.p3 = exploit_point_mult(m, b.p3);
  return b;
}

void free_bezier(Bezier b) {
  free_point_map(b.helper.viewing_to_t);
}
