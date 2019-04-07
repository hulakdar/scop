#ifndef OBJ_H
# define OBJ_H
# include "libft.h"
# include <GL/glew.h>
# include "pthread.h"
#include <stdint.h>

#if __INTELLISENSE__
typedef struct { float x; float y; float z; float w; } t_float4;
typedef struct { float x; float y; } t_float2;
#else
typedef float t_float4 __attribute__((ext_vector_type(4)));
typedef float t_float2 __attribute__((ext_vector_type(2)));
#endif

typedef struct	s_vertex 
{
	t_float4		position;
	t_float4		normal;
	t_float2		uv;
}				t_vertex;

typedef struct	s_face
{
	int		pos_indx[4];
	int		norm_indx[4];
	int		uvs_indx[4];
	int		has_norm : 1;
	int		has_uv : 1;
}				t_face;

typedef enum	e_uniform_type
{
	UT_VEC4, UT_UINT, UT_SINT
}				t_uniform_type;

typedef union	u_uniform_data
{
	t_float4	vec4;
	GLuint		uint;
	GLint		sint;
}				t_uniform_data;

typedef struct  s_uniform
{
	t_uniform_type	type;
	t_uniform_data	data;
}				t_uniform;

typedef struct	s_submesh
{
	size_t		start;
	size_t		count;
	t_vector	uniforms;
	GLuint		shader_program;
}				t_submesh;

typedef struct  s_buffer_pair
{
	GLuint		vertex_buffer;
	GLuint		vertex_array;
}				t_buffer_pair;

typedef struct  s_skybox_data
{
	t_buffer_pair	buffers;
	GLuint			shader;
	GLuint			texture;
}				t_skybox_data;

typedef struct	s_model
{
	char			*filepath;
	t_vector		vertecies;
	t_vector		submeshes;
	t_buffer_pair	buffers;
	t_skybox_data	skybox;
	pthread_mutex_t	lock;
	uint_fast8_t	is_dirty : 1;
	uint_fast8_t	is_done : 1;
}				t_model;

typedef struct	s_obj
{
	t_vector		positions;
	t_vector		uvs;
	t_vector		normals;
	t_model			*result;
	t_submesh		*current_object;
	size_t			current_index;
	unsigned char	no_uv : 1;
	unsigned char	no_normals : 1;
}				t_obj;

void	parse_vec3(const char *line, t_vector *buffer);
void	parse_vec2(const char *line, t_vector *buffer);
void	parse_faces(const char *line, t_obj *buffers);
void	parse_mtl(const char *line, t_obj *buffers);
void	*parse_obj(t_model *model);
#endif
