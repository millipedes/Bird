#ifndef PNG_TRANSLATION_H
#define PNG_TRANSLATION_H

#include "core/canvas.h"

#include "translation_state.h"

// # of bytes which is the header for pngs
#define PNG_HEADER_SIZE 8

TranslationState write_canvas_to_png(const Canvas * c, const char * file_name);
TranslationState read_png_to_canvas(Canvas * c, const char * file_name);

#endif
