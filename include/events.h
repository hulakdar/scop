#pragma once

#include "obj.h"

void GLClearError();
char GLCheckError(const char *Function, const char *File, int Line);

void	bind_buffers(t_buffer_pair model_buffers);
int		event_loop(SDL_Window *window, t_model *model);