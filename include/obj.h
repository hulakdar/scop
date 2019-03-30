#ifndef OBJ_H
# define OBJ_H
# include "libft.h"

# define VEC3_IS_ZERO(v)	(!(v.x || v.y || v.z))
# define VEC2_IS_ZERO(v)	(!(v.x || v.y))
# define VEC3_ADD(a,b)	((t_vec3) {a.x + b.x, a.y + b.y, a.z + b.z})
# define VEC2_ADD(a,b)	((t_vec2) {a.x + b.x, a.y + b.y})
# define VEC3_MUL(a,b)	((t_vec3) {a.x * b.x, a.y * b.y, a.z * b.z})
# define VEC2_MUL(a,b)	((t_vec2) {a.x * b.x, a.y * b.y})
# define VEC3_MULS(v,s)	((t_vec3) {v.x * s, v.y * s, v.z * s})
# define VEC2_MULS(v,s)	((t_vec2) {v.x * s, v.y * s})
# define VEC3(x,y,z)	((t_vec3) {x, y, z})
# define VEC2(x,y)		((t_vec2) {x, y})

typedef struct	s_obj
{
	t_vector		positions;
	t_vector		uvs;
	t_vector		normals;
	unsigned char	no_uv : 1;
	unsigned char	no_normals : 1;
}				t_obj;

typedef struct	s_vec2
{
	float		x;
	float		y;
}				t_vec2;

typedef struct	s_vec3
{
	float		x;
	float		y;
	float		z;
}				t_vec3;

typedef struct	s_vertex 
{
	t_vec3		position;
	t_vec2		uv;
	t_vec3		normal;
}				t_vertex;

typedef struct	s_face
{
	int		pos_indx[4];
	int		norm_indx[4];
	int		uvs_indx[4];
	int		has_norm : 1;
	int		has_uv : 1;
}				t_face;

typedef struct	s_meshlet
{
	int x;
}				t_meshlet;

typedef struct	s_model
{
	t_vector	vertecies;
	t_vector	materials;
	unsigned	vertex_buffer;
	unsigned	vertex_array;
	unsigned	texture;
	int			shader_program;
}				t_model;


void	parse_vec3(const char *line, t_vector *buffer);
void	parse_vec2(const char *line, t_vector *buffer);
void	parse_faces(const char *line, t_obj *buffers, t_model *model);
void	parse_mtl(const char *line, t_vector *materials);
t_model parse_obj(const char *filename);
#endif
