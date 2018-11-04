#ifndef SCOP_H
# define SCOP_H

# include "libft.h"

# define CONTEXT_PROFILE SDL_GL_CONTEXT_PROFILE_CORE
# define CONTEXT_FLAGS SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG

# define GLEW_STATIC
# include <GL/glew.h>
#if _WIN32 || _WIN64
# include <SDL.h>
# include <SDL_image.h>
#else
# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
#endif

char scop_error(const char *error);

#define GLCall(x) GLClearError();x;GLCheckError(#x, __FILE__, __LINE__)

#include "events.h"

#endif
