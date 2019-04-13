#pragma once

#include "obj.h"

void gl_clear_error();
char gl_check_error(const char *Function, const char *File, int Line);

void	bind_buffers(t_buffers model_buffers);
int		event_loop(SDL_Window *window, t_model *model);