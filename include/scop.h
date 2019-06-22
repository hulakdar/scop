#ifndef SCOP_H
# define SCOP_H

# include "libft.h"
# include <pthread.h>
# include <stdint.h>

# define CONTEXT_PROFILE SDL_GL_CONTEXT_PROFILE_CORE
# define CONTEXT_FLAGS SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG

# define GLEW_STATIC
#  include <GL/glew.h>
# if _WIN32 || _WIN64 || __WIN32__
#  define DEBUG_BREAK() if (IsDebuggerPresent()) __debugbreak()
#  include <SDL.h>
#  include <SDL_image.h>
# else
#  define DEBUG_BREAK()
#  include <SDL2/SDL.h>
#  include <SDL2/SDL_image.h>
# endif
# include "obj.h"
# include "events.h"

# define SCREEN_W 1024
# define SCREEN_H 1024

typedef	struct	s_global_uniforms
{
	t_m44		mvp;
	t_m44		light_transform;
	t_float4	light_dir;
}				t_global_uniforms;

typedef struct	s_frame_info 
{
	t_global_uniforms	g_uniforms;
	t_float4			position;
	t_float2			angles;
	t_float2			light_angles;
	uint64_t			last_time;
	uint64_t			current_time;
	t_depth				depth;
	t_quad_data			depth_preview;
	GLuint				uniform_buffer;
	GLuint				default_texture;
	GLenum				polygon_mode;
	float				delta_time;
	float				scale;
	uint_fast8_t		is_dirty : 1;
	uint_fast8_t		is_depth_pass : 1;
}				t_frame_info;

typedef	uint_fast8_t t_bool;

unsigned 		scop_error(const char *error);
t_depth			create_depth();
void			draw_quad(t_frame_info *frame, t_quad_data quad_data);

#define GLCALL(x) gl_clear_error();x;gl_check_error(#x, __FILE__, __LINE__)


#endif
