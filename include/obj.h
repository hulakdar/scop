#ifndef OBJ_H
# define OBJ_H
# include "libft.h"

typedef struct	s_obj
{
	t_vector		positions;
	t_vector		uvs;
	t_vector		normals;
	unsigned char	no_uv : 1;
	unsigned char	no_normals : 1;
}				t_obj;

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
	t_float2		uv;
	t_float4		normal;
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

typedef union	u_uniform
{
	t_float4	vec4;
	GLuint		uint;
	GLint		sint;
}				t_uniform;

typedef struct  s_uniform
{
	t_uniform_type	type;
	t_uniform		value;
};

typedef struct	s_submesh
{
	size_t		start;
	size_t		count;
	t_vector	uniforms;
	int			shader_program;
}				t_submesh;

typedef struct	s_model
{
	t_vector		vertecies;
	t_vector		submeshes;
	unsigned		vertex_buffer;
	unsigned		vertex_array;
}				t_model;


void	parse_vec3(const char *line, t_vector *buffer);
void	parse_vec2(const char *line, t_vector *buffer);
void	parse_faces(const char *line, t_obj *buffers, t_model *model);
void	parse_mtl(const char *line, t_model *model);
t_model parse_obj(const char *filename);
#endif
