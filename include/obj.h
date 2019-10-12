#ifndef OBJ_H
# define OBJ_H
# include "libft.h"
# include "gl_math.h"
# include <GL/glew.h>
# include "pthread.h"

typedef pthread_mutex_t t_lock;

typedef struct	s_face
{
	int			pos_indx[16];
	int			norm_indx[16];
	int			uvs_indx[16];
}				t_face;

typedef enum	e_attribute
{
	A_DIFFUSE,
	A_AMBIENT,
	A_SPECULAR,
	A_SPECULAR_POW,
	A_TRANSLUCENCY
}				t_attribute;

typedef enum	e_uniform_type
{
	UT_NONE,
	UT_VEC4,
	UT_SAMPLER2D,
	UT_FLOAT
}				t_uniform_type;

typedef union	u_uniform_data
{
	t_float4	vec4;
	float		vec1;
	GLuint		uint;
}				t_uniform_data;

typedef struct  s_uniform
{
	t_uniform_type	type;
	t_uniform_data	data;
}				t_uniform;

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

typedef struct	s_model
{
	t_vector	vertecies;
	t_vector	submeshes;
	t_quad_data	skybox;
	t_quad_data	skybox_blurred;
	t_buffers	buffers;
	t_float4	offset_scale;
	t_lock		lock;
	const char	*filepath;
	unsigned	is_dirty : 1;
}				t_model;

typedef struct	s_material
{
	char*		name;
	t_uniform	ambient;
	t_uniform	diffuse;
	t_uniform	specular;
	t_uniform	specular_power;
	t_uniform	translucency;
}				t_material;

typedef struct	s_submesh
{
	size_t		start;
	size_t		count;
	GLuint		shader_program;
}				t_submesh;

typedef struct	s_obj
{
	t_vector	positions;
	t_vector	uvs;
	t_vector	normals;
	t_vector	materials;
	t_float4	min_bounds;
	t_float4	max_bounds;
	t_model		*result;
	t_submesh	*current_object;
	t_material	*current_material;
	size_t		current_index;
	unsigned	no_uv : 1;
	unsigned	no_normals : 1;
}				t_obj;

t_float4	parse_vec3(const char *line);
t_float2	parse_vec2(const char *line);
void		parse_faces(const char *line, t_obj *buffers);
void		fixup_normals(t_vector *verts, t_face face);
void		fixup_uvs(t_vector *verts, t_face face);
void		parse_mtl(const char *line, t_obj *buffers);
void		create_new_submesh(t_obj * buffers);
void		*parse_obj(t_model *model);
#endif
