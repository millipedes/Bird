#ifndef SHAPE_H
#define SHAPE_H

#include "ellipse.h"

typedef enum {
  ELLIPSE,
} ShapeType;

typedef union {
  Ellipse ellipse;
} ShapeValue;

typedef struct SHAPE_T {
  ShapeValue value;
  ShapeType type;
} Shape;

#endif
