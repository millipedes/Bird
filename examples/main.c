#include <stdio.h>

#include "core/ellipse.h"
#include "core/canvas.h"
#include "impl/png_translation.h"

#include <math.h>

int main(void) {

  // Canvas c1 = init_canvas((Pixel){.rgba = {0, 0, 0, 255}}, 1200, 800, 4);

  // TranslationState ts_1 = write_canvas_to_png(&c1, "test1.png");
  // if (ts_1.state != SUCCESS) {
  //   printf("%s\n", ts_1.msg);
  // }

  // Canvas c2 = {0};
  // TranslationState ts_2 = read_png_to_canvas(&c2, "test1.png");
  // if (ts_2.state != SUCCESS) {
  //   printf("%s\n", ts_2.msg);
  // }

  // TranslationState ts_3 = write_canvas_to_png(&c2, "test2.png");
  // if (ts_3.state != SUCCESS) {
  //   printf("%s\n", ts_3.msg);
  // }

  // free_canvas(c1);
  // free_canvas(c2);

  /****************************************************************************/
  /************************Example 1 Ellipse***********************************/
  /****************************************************************************/
  Ellipse e = init_ellipse(1.0, 1.0, 0.0, 0.0);
  Canvas c = init_canvas((Pixel){.rgba = {0, 0, 0, 255}}, 1200, 800, 4,
     multiply_matrices(2,
       affine_translate(600.0, 400.0),
       affine_scale(40.0, 40.0)));
  for (uint8_t i = 0; i < 4; i++) {
    for (double t = 0; t < 1.0; t += 0.0001) {
      Point world_space = evaluate_bezier(&e.curves[i], t);
      Point canvas_space = exploit_point_mult(c.ctm, world_space);
      c.points[(int)canvas_space.y][(int)canvas_space.x] = (Pixel){.rgba = {0, 255, 0, 255}};
    }
  }

  for (int dx = -2; dx <= 2; dx++) {
    int x = 600 + dx;
    for (int y = 0; y < 800; y++) {
      c.points[y][x] = (Pixel){.rgba = {0, 255, 0, 255}};
    }
  }
  for (int dy = -2; dy <= 2; dy++) {
    int y = 400 + dy;
    for (int x = 0; x < 1200; x++) {
      c.points[y][x] = (Pixel){.rgba = {0, 255, 0, 255}};
    }
  }

  TranslationState ts_1 = write_canvas_to_png(&c, "test1.png");
  if (ts_1.state != SUCCESS) {
    printf("%s\n", ts_1.msg);
  }

  free_canvas(c);
  return 0;
}
