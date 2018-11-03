#ifndef SCOP_H
# define SCOP_H

# include "libft.h"

# define CONTEXT_PROFILE SDL_GL_CONTEXT_PROFILE_CORE
# define CONTEXT_FLAGS SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG

# define GLEW_STATIC
# include <GL/glew.h>
# include <SDL.h>
# include <SDL_image.h>

char scop_error(const char *error);

#define GLCall(x) GLClearError();x;GLCheckError(#x, __FILE__, __LINE__)

#endif
