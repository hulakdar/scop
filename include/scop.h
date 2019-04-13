#ifndef SCOP_H
# define SCOP_H

# include "libft.h"
# include <pthread.h>
# include <stdint.h>

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
# include "events.h"

typedef	struct	s_global_uniforms
{
	t_m44		mvp;
	t_float4	light_dir;
}				t_global_uniforms;

typedef struct	s_frame_info 
{
	t_global_uniforms	g_uniforms;
	t_float4			position;
	t_float4			position_offset;
	t_float2			angles;
	t_float2			angles_offset;
	Uint64				last_time;
	Uint64				current_time;
	GLuint				uniform_buffer;
	GLenum				polygon_mode;
	float				delta_time;
	float				scale;
	float				scale_dir;
	uint_fast8_t		is_dirty : 1;
}				t_frame_info;

typedef	uint_fast8_t t_bool;

unsigned 		scop_error(const char *error);
t_buffers		create_skybox_data();
GLuint			create_depth_buffer();


#define GLCALL(x) gl_clear_error();x;gl_check_error(#x, __FILE__, __LINE__)


#endif
