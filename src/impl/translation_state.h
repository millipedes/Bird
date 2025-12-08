#ifndef TRANSLATION_STATE_H
#define TRANSLATION_STATE_H

typedef enum {
  SUCCESS,
  WARNING,
  ERROR,
} State;

typedef struct TRANSLATION_STATE_H {
  const char * msg;
  State state;
} TranslationState;

#endif
