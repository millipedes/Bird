#include <gtest/gtest.h>

#include "core/bezier.h"
#include "core/ellipse.h"

constexpr static auto delta_factor = 1e-6;
constexpr static auto normalized_integral = 1.0;

TEST(bezier_line_integral, increments_0) {
  auto e = init_ellipse(1.0, 1.0, 0.0, 0.0);
  for (uint8_t i = 0; i < 4; i++) {
    auto normalize_factor = line_integral_normalize_factor(&e.curves[i]);
    auto line_integral = line_integral_unormalized(&e.curves[i], normalize_factor, 1.0, 0.0);
    ASSERT_NEAR(line_integral, normalized_integral, delta_factor);
  }
  free_ellipse(e);
}

TEST(bezier_line_integral, increments_1) {
  auto e = init_ellipse(1.0, 1.0, 0.0, 0.0);
  for (uint8_t i = 0; i < 4; i++) {
    auto normalize_factor = line_integral_normalize_factor(&e.curves[i]);
    double line_integral = 0.0;
    line_integral += line_integral_unormalized(&e.curves[i], normalize_factor, 0.5, 0.0);
    line_integral += line_integral_unormalized(&e.curves[i], normalize_factor, 1.0, 0.5);
    ASSERT_NEAR(line_integral, normalized_integral, delta_factor);
  }
  free_ellipse(e);
}

TEST(bezier_line_integral, increments_2) {
  auto e = init_ellipse(1.0, 1.0, 0.0, 0.0);
  for (uint8_t i = 0; i < 4; i++) {
    auto normalize_factor = line_integral_normalize_factor(&e.curves[i]);
    double line_integral = 0.0;
    line_integral += line_integral_unormalized(&e.curves[i], normalize_factor, 0.33, 0.0);
    line_integral += line_integral_unormalized(&e.curves[i], normalize_factor, 0.66, 0.33);
    line_integral += line_integral_unormalized(&e.curves[i], normalize_factor, 1.0, 0.66);
    ASSERT_NEAR(line_integral, normalized_integral, delta_factor);
  }
  free_ellipse(e);
}

TEST(bezier_line_integral, increments_3) {
  auto e = init_ellipse(1.0, 1.0, 0.0, 0.0);
  for (uint8_t i = 0; i < 4; i++) {
    auto normalize_factor = line_integral_normalize_factor(&e.curves[i]);
    double line_integral = 0.0;
    line_integral += line_integral_unormalized(&e.curves[i], normalize_factor, 0.25, 0.0);
    line_integral += line_integral_unormalized(&e.curves[i], normalize_factor, 0.50, 0.25);
    line_integral += line_integral_unormalized(&e.curves[i], normalize_factor, 0.75, 0.50);
    line_integral += line_integral_unormalized(&e.curves[i], normalize_factor, 1.0, 0.75);
    ASSERT_NEAR(line_integral, normalized_integral, delta_factor);
  }
  free_ellipse(e);
}

TEST(bezier_line_integral, increments_4) {
  auto e = init_ellipse(1.0, 1.0, 0.0, 0.0);
  for (uint8_t i = 0; i < 4; i++) {
    auto normalize_factor = line_integral_normalize_factor(&e.curves[i]);
    double line_integral = 0.0;
    double delta_t = 1e-4;
    for (double t = delta_t; t < 1.0; t += delta_t) {
      line_integral += line_integral_unormalized(&e.curves[i], normalize_factor, t, t - delta_t);
    }
    ASSERT_NEAR(line_integral, normalized_integral, delta_factor);
  }
  free_ellipse(e);
}
