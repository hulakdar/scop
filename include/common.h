#ifndef _COMMON_H_
# define _COMMON_H_

# include "libft.h"
# include <pthread.h>
# include <stdint.h>

# define CONTEXT_PROFILE SDL_GL_CONTEXT_PROFILE_CORE
# define CONTEXT_FLAGS SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG
# define SDL_MAIN_HANDLED

# define GLEW_STATIC
# include <GL/glew.h>
# if _WIN32 || _WIN64 || __WIN32__
#  define CUBEMAP_PIXEL_FORMAT GL_RGB
#  define GLCALL(x) gl_clear_error();x;gl_check_error(#x, __FILE__, __LINE__)
#  define DEBUG_BREAK() if (IsDebuggerPresent()) __debugbreak()
#  include <SDL.h>
#  include <SDL_image.h>
# else
#  define CUBEMAP_PIXEL_FORMAT GL_BGRA
#  define GLCALL(x) x
#  define DEBUG_BREAK() __builtin_trap()
#  include <SDL2/SDL.h>
#  include <SDL2/SDL_image.h>
# endif

#endif
