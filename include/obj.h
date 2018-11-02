#ifndef OBJ_H
# define OBJ_H
#include "libft.h"

typedef struct	s_obj
{
	t_vector		positions;
	t_vector		uvs;
	t_vector		normals;
	t_vector		indicies;
	unsigned char	no_uv : 1;
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
	t_vec3		normale;
}				t_vertex;

typedef struct	s_face
{
	int		pos_indx[4];
	int		norm_indx[4];
	int		uvs_indx[4];
	int		has_norm : 1;
	int		has_uv : 1;
}				t_face;

typedef struct	s_model
{
	t_vector	vertecies;
	t_vector	materials;
}				t_model;

void	parse_vec3(const char *line, t_vector *buffer);
void	parse_vec2(const char *line, t_vector *buffer);
void	parse_faces(const char *line, t_obj *buffers, t_model *model);
void	parse_mtl(const char *line, t_vector *materials);
t_model parse_obj(const char *filename);
#endif
