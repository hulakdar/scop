#ifndef OBJ_H
# define OBJ_H
# include "libft.h"
# include "math.h"
# include <GL/glew.h>
# include "pthread.h"

typedef struct	s_face
{
	int			pos_indx[16];
	int			norm_indx[16];
	int			uvs_indx[16];
}				t_face;

typedef enum	e_uniform_type
{
	UT_VEC4,
	UT_VEC2,
	UT_UINT,
	UT_SINT,
	UT_FLOAT
}				t_uniform_type;

typedef union	u_uniform_data
{
	t_float4	vec4;
	t_float2	vec2;
	float		vec1;
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

typedef struct  s_buffers
{
	GLuint		vertex_array;
	GLuint		vertex_buffer;
}				t_buffers;

typedef struct	s_quad_data
{
	GLuint		shader;
	GLuint		texture;
	GLenum		texture_type;
}				t_quad_data;

typedef struct	s_depth
{
	GLuint		buffer;
	GLuint		shader;
	GLuint		texture;
}				t_depth;


typedef struct	s_model
{
	t_vector		vertecies;
	t_vector		submeshes;
	t_quad_data		skybox;
	t_quad_data		skybox_blurred;
	t_buffers		buffers;
	t_float4		offset_scale;
	pthread_mutex_t	lock;
	char			*filepath;
	unsigned		is_dirty : 1;
}				t_model;

typedef struct	s_obj
{
	t_vector	positions;
	t_vector	uvs;
	t_vector	normals;
	t_float4	min_bounds;
	t_float4	max_bounds;
	t_model		*result;
	t_submesh	*current_object;
	size_t		current_index;
	unsigned	no_uv : 1;
	unsigned	no_normals : 1;
}				t_obj;

void	parse_vec3(const char *line, t_vector *buffer);
void	parse_vec2(const char *line, t_vector *buffer);
void	parse_faces(const char *line, t_obj *buffers);
void	parse_mtl(const char *line, t_obj *buffers);
void	*parse_obj(t_model *model);
#endif
