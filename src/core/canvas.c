#include "canvas.h"

#include <stdio.h>
#include <stdlib.h>

#include <math.h>

Canvas init_canvas(Pixel p, uint32_t len_x, uint32_t len_y, uint8_t no_channels,
    Matrix ctm) {
  Canvas c = {0};

  c.ctm = ctm;

  c.points = (Pixel **)calloc(len_y, sizeof(Pixel *));
  for (uint32_t i = 0; i < len_y; i++) {
    c.points[i] = (Pixel *)calloc(len_x, sizeof(Pixel));
  }

  for (uint32_t i = 0; i < len_y; i++) {
    for (uint32_t j = 0; j < len_x; j++) {
      c.points[i][j] = p;
    }
  }
  c.len_x = len_x;
  c.len_y = len_y;
  c.no_channels = no_channels;
  return c;
}

Canvas draw_shape(Canvas c, Shape s, Pixel color) {
  const static double t_delta = 1e-2;
  switch (s.type) {
    case ELLIPSE:
      Ellipse * e = &s.value.ellipse;
      // Set up point map
      for (uint8_t i = 0; i < QTY_ELLIPSE_CURVES; i++) {

        double t_begin = 0.0;

        for (double t = 0.0; t < 1.0; t += t_delta) {
          Point world_space = evaluate_bezier(&e->curves[i], t);
          Point canvas_space = exploit_point_mult(c.ctm, world_space);

          TBounds tmp = (TBounds){t_begin, t};
          if (!point_map_get(&e->curves[i].helper.viewing_to_t, (Point){(int)canvas_space.x, (int)canvas_space.y}, &tmp)) {
            point_map_put(&e->curves[i].helper.viewing_to_t, (Point){(int)canvas_space.x, (int)canvas_space.y}, tmp);
            t_begin = t;
          }
        }

        double normalize_factor = line_integral_normalize_factor(&e->curves[i]);

        for (uint32_t j = 0; j < c.len_y; j++) {
          for (uint32_t k = 0; k < c.len_x; k++) {
            TBounds tmp = {0.0, 0.0};
            Point p = {k, j};
            if (point_map_get(&e->curves[i].helper.viewing_to_t, p, &tmp)) {
              double line_integral = fabs(line_integral_unormalized(&e->curves[i], 100.0, tmp.t_end, tmp.t_begin));
              // printf("%f\n", line_integral);
              c.points[j][k] = (Pixel){ .rgba = { 0, (int)(255.0 * line_integral), 0, 255} };
            }
          }
        }
      }
      break;
    default:
      fprintf(stderr, "draw_shape: Attempting to draw unsupported shape with "
          "code: %d\n", s.type);
      exit(1);
  }
  return c;
}

Canvas free_canvas(Canvas c) {
  for (uint32_t i = 0; i < c.len_y; i++) {
    if (c.points[i]) {
      free(c.points[i]);
    }
  }
  if (c.points) {
    free(c.points);
  }
}
