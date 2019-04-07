#ifndef SCOP_H
# define SCOP_H

# include "libft.h"
# include <pthread.h>

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
# include "obj.h"

typedef struct	s_frame_info 
{
	Uint64		last_time;
	Uint64		current_time;
	float		delta_time;
	int			angles_u_location;
	int			position_u_location;
	int			scale_u_location;
	float		scale;
	float		scale_dir;
	t_float2	angles;
	t_float2	angles_offset;
	t_float4	position;
	t_float4	position_offset;
}				t_frame_info;

unsigned 		scop_error(const char *error);
t_buffer_pair	create_skybox_data();

#define GLCall(x) GLClearError();x;GLCheckError(#x, __FILE__, __LINE__)

#include "events.h"

#endif
