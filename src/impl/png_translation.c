#include "png_translation.h"

#include <stdbool.h>
#include <stdlib.h>

#include <png.h>

void error_translation_state(png_structp png_ptr, png_const_charp msg) {
  TranslationState * translation_state = (TranslationState *)png_get_error_ptr(png_ptr);
  translation_state->msg = (const char *)msg;
  translation_state->state = ERROR;
}

void warning_translation_state(png_structp png_ptr, png_const_charp msg) {
  TranslationState * translation_state = (TranslationState *)png_get_error_ptr(png_ptr);
  translation_state->msg = (const char *)msg;
  translation_state->state = WARNING;
}

TranslationState write_canvas_to_png(const Canvas * c, const char * file_name) {
  FILE * fp = fopen(file_name, "wb");
  TranslationState result = (TranslationState){"Success", SUCCESS};

  if (!fp) {
    result.msg = "read_png_to_canvas: Unable to open file";
    result.state = ERROR;
    return result;
  }

  png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING,
      (png_voidp)(&result),
      error_translation_state,
      warning_translation_state);

  png_infop info_ptr = png_create_info_struct(png_ptr);
  png_init_io(png_ptr, fp);
  png_set_IHDR(png_ptr, info_ptr,
      c->len_x, c->len_y,
      PNG_HEADER_SIZE,
      c->no_channels == 3 ? PNG_COLOR_TYPE_RGB : PNG_COLOR_TYPE_RGBA,
      PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
  png_write_info(png_ptr, info_ptr);

  for (uint32_t i = 0; i < c->len_y; i++) {
    png_bytep row = (png_bytep)calloc(c->len_x * c->no_channels,
        sizeof(png_byte));
    for(uint32_t j = 0; j < c->len_x; j++) {
      if (c->no_channels == 3) {
        row[3 * j] = (png_byte)c->points[i][j].rgb.r;
        row[3 * j + 1] = (png_byte)c->points[i][j].rgb.g;
        row[3 * j + 2] = (png_byte)c->points[i][j].rgb.b;
      } else {
        row[4 * j] = (png_byte)c->points[i][j].rgba.r;
        row[4 * j + 1] = (png_byte)c->points[i][j].rgba.g;
        row[4 * j + 2] = (png_byte)c->points[i][j].rgba.b;
        row[4 * j + 3] = (png_byte)c->points[i][j].rgba.a;
      }
    }
    png_write_row(png_ptr, row);
    free(row);
    row = NULL;
  }

  png_write_end(png_ptr, info_ptr);
  png_destroy_write_struct(&png_ptr, &info_ptr);
  fclose(fp);
  return result;
}

TranslationState read_png_to_canvas(Canvas * c, Matrix ctm, const char * file_name) {
  FILE *fp = fopen(file_name, "rb");
  unsigned char header[PNG_HEADER_SIZE] = {0};
  size_t number = PNG_HEADER_SIZE;
  TranslationState result = (TranslationState){"Success", SUCCESS};
  if (!fp) {
    result.msg = "read_png_to_canvas: Unable to open file";
    result.state = ERROR;
    return result;
  }

  if (fread(header, 1, number, fp) != number) {
    result.msg = "read_png_to_canvas: Unable to read 8 byte signature";
    result.state = ERROR;
    return result;
  }

  bool is_png = (png_sig_cmp(header, 0, number) == 0);
  if (!is_png) {
    result.msg = "read_png_to_canvas: PNG signature not recognized";
    result.state = ERROR;
    return result;
  }

  png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
      (png_voidp)(&result),
      error_translation_state,
      warning_translation_state);

  if (!png_ptr || result.state != SUCCESS) {
    return result;
  }

  png_infop info_ptr = png_create_info_struct(png_ptr);

  if (!info_ptr) {
    png_destroy_read_struct(&png_ptr, NULL, NULL);
    result.msg = "read_png_to_canvas: Unable to create png info struct";
    result.state = ERROR;
    return result;
  }

  png_init_io(png_ptr, fp);
  png_set_sig_bytes(png_ptr, PNG_HEADER_SIZE);

  png_read_info(png_ptr, info_ptr);

  uint8_t channels = png_get_channels(png_ptr,  info_ptr);
  if (channels != 3 && channels != 4) {
    result.msg = "read_png_to_canvas: Bird does not support grayscale";
    result.state = ERROR;
    return result;
  }

  uint32_t height = png_get_image_height(png_ptr,  info_ptr);
  uint32_t width = png_get_image_width(png_ptr,  info_ptr);

  *c = init_canvas(channels == 3
      ? (Pixel){.rgb = {0, 0, 0}}
      : (Pixel){.rgba = {0, 0, 0, 0}},
      width, height, channels, ctm);

  for (int i = 0; i < c->len_y; i++) {
    png_bytep row = (png_bytep)malloc(png_get_rowbytes(png_ptr, info_ptr));
    png_read_row(png_ptr, row, NULL);

    for (int j = 0; j < c->len_x; j++) {
      if (c->no_channels == 3) {
        c->points[i][j].rgb = (RGBPixel){(uint8_t)row[3 * j],
                              (uint8_t)row[3 * j + 1],
                              (uint8_t)row[3 * j + 2]};
      } else {
        c->points[i][j].rgba = (RGBAPixel){(uint8_t)row[4 * j],
                              (uint8_t)row[4 * j + 1],
                              (uint8_t)row[4 * j + 2],
                              (uint8_t)row[4 * j + 3]};
      }
    }
    free(row);
    row = NULL;
  }

  fclose(fp);
  png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

  return result;
}
