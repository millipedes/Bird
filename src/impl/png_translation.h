#ifndef PNG_TRANSLATION_H
#define PNG_TRANSLATION_H

#include "core/canvas.h"
#include "core/matrix3d.h"

#include "translation_state.h"

#ifdef __cplusplus
extern "C" {
#endif

// # of bytes which is the header for pngs, this will never change
#define PNG_HEADER_SIZE 8

TranslationState write_canvas_to_png(const Canvas * c, const char * file_name);
TranslationState read_png_to_canvas(Canvas * c, Matrix ctm, const char * file_name);

#ifdef __cplusplus
}
#endif

#endif
