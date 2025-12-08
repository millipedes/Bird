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

  // Ellipse e = init_ellipse(100, 100, 200, 200);
  // printf("%f %f\n", e.curves[0].p0.x, e.curves[0].p0.y);
  // printf("%f %f\n", e.curves[0].p1.x, e.curves[0].p1.y);
  // printf("%f %f\n", e.curves[0].p2.x, e.curves[0].p2.y);
  // printf("%f %f\n", e.curves[0].p3.x, e.curves[0].p3.y);
  // printf("%f %f\n", e.curves[1].p0.x, e.curves[1].p0.y);
  // printf("%f %f\n", e.curves[1].p1.x, e.curves[1].p1.y);
  // printf("%f %f\n", e.curves[1].p2.x, e.curves[1].p2.y);
  // printf("%f %f\n", e.curves[1].p3.x, e.curves[1].p3.y);
  // printf("%f %f\n", e.curves[2].p0.x, e.curves[2].p0.y);
  // printf("%f %f\n", e.curves[2].p1.x, e.curves[2].p1.y);
  // printf("%f %f\n", e.curves[2].p2.x, e.curves[2].p2.y);
  // printf("%f %f\n", e.curves[2].p3.x, e.curves[2].p3.y);
  // printf("%f %f\n", e.curves[3].p0.x, e.curves[3].p0.y);
  // printf("%f %f\n", e.curves[3].p1.x, e.curves[3].p1.y);
  // printf("%f %f\n", e.curves[3].p2.x, e.curves[3].p2.y);
  // printf("%f %f\n", e.curves[3].p3.x, e.curves[3].p3.y);
  // printf("%f\n", KAPPA);
  // Canvas c = init_canvas((Pixel){.rgba = {0, 0, 0, 255}}, 1200, 800, 4);
  // c = draw_bezier(c, &e.curves[0]);
  // c = draw_bezier(c, &e.curves[1]);
  // c = draw_bezier(c, &e.curves[2]);
  // c = draw_bezier(c, &e.curves[3]);
  // // c.points[500][500] = (Pixel){.rgba = {0, 255, 0, 255}};
  // // c.points[501][501] = (Pixel){.rgba = {0, 255, 0, 255}};
  // // c.points[502][502] = (Pixel){.rgba = {0, 255, 0, 255}};
  // // c.points[503][503] = (Pixel){.rgba = {0, 255, 0, 255}};
  // TranslationState ts_1 = write_canvas_to_png(&c, "test1.png");
  // if (ts_1.state != SUCCESS) {
  //   printf("%s\n", ts_1.msg);
  // }

  // free_canvas(c);
  return 0;
}
