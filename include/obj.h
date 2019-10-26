/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 22:43:57 by skamoza           #+#    #+#             */
/*   Updated: 2019/10/19 17:40:49 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_H
# define OBJ_H
# include <GL/glew.h>
# include "libft.h"
# include "gl_math.h"
# include "common.h"
# include "pthread.h"

typedef pthread_mutex_t	t_lock;

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

typedef struct	s_buffers
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
	SDL_Window		*window;
	SDL_GLContext	context;
	t_vector		vertecies;
	t_vector		submeshes;
	t_vector		materials;
	t_quad_data		skybox;
	t_quad_data		skybox_blurred;
	t_buffers		buffers;
	t_float4		offset_scale;
	t_lock			lock;
	const char		*filepath;
	unsigned		is_dirty;
	unsigned		request_exit;
}				t_model;

typedef struct	s_material
{
	float		diffuse_color[4];
	char		*name;
	char		*tex_name;
	GLuint		diffuse_tex;
	uint8_t		has_texture;
}				t_material;

typedef struct	s_submesh
{
	size_t		start;
	size_t		count;
	t_material	*material;
	GLuint		shader_program;
}				t_submesh;

typedef struct	s_obj
{
	t_vector	positions;
	t_vector	uvs;
	t_vector	normals;
	t_float4	min_bounds;
	t_float4	max_bounds;
	t_model		*result;
	t_submesh	*current_object;
	t_material	*current_material;
	size_t		current_index;
	unsigned	no_uv : 1;
	unsigned	no_normals : 1;
}				t_obj;

t_float4		parse_vec3(const char *line);
t_float2		parse_vec2(const char *line);
void			parse_faces(const char *line, t_obj *buffers);
void			fixup_normals(t_vector *verts, t_face face);
void			fixup_uvs(t_vector *verts, t_face face);
void			parse_mtl(const char *line, t_obj *buffers);
void			create_new_submesh(t_obj *buffers);
void			*parse_obj(t_model *model);
void			new_material(const char *line, t_obj *obj);
#endif
