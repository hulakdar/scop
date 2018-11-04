#pragma once

#include "obj.h"

void GLClearError();
char GLCheckError(const char *Function, const char *File, int Line);

int event_loop(SDL_Window *window, t_model model);