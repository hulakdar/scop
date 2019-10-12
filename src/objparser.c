
#include "obj.h"
#include <stdio.h>
#include "scop.h"

t_material get_default_material()
{
	t_material result;

	ft_bzero(&result, sizeof(result));
	result.name = "default";
	result.diffuse.type = UT_SAMPLER2D;
	result.diffuse.data.uint = get_default_texture();
	return result;
}

static void			prepare_obj(t_obj *obj)
{
	const t_float4 tmp = {0,0,0,0};
	t_material material;

	ft_bzero(obj, sizeof(t_obj));
	material = get_default_material();
	ft_vec_init(&obj->positions, sizeof(t_float4), 256);
	ft_vec_init(&obj->normals, sizeof(t_float4), 256);
	ft_vec_init(&obj->uvs, sizeof(t_float2), 256);
	ft_vec_init(&obj->materials, sizeof(t_float2), 2);
	ft_vec_pushback(&obj->positions, &tmp);
	ft_vec_pushback(&obj->normals, &tmp);
	ft_vec_pushback(&obj->uvs, &tmp);
	obj->current_material =
		(t_material *)ft_vec_pushback(&obj->materials, &material);
}

static void handle_vec(const char *line, t_vector *buffer, t_bool is_vec3)
{
	void*		result;
	t_float4	vec4;
	t_float2	vec2;

	while (*line == ' ')
		line++;
	if (is_vec3)
	{
		vec4 = parse_vec3(line);
		result = &vec4;
	}
	else
	{
		vec2 = parse_vec2(line);
		result = &vec2;
	}
	ft_vec_pushback(buffer, result);
}

static void set_mtl(const char *line, t_obj *obj)
{

}

static inline void parse_single_line(const char *line, t_obj *obj)
{
	while (!ft_isprint(*line))
		line++;
	if (!ft_memcmp(line, "v ", 2))
		handle_vec(line + 2, &obj->positions, true);
	else if (!ft_memcmp(line, "vn ", 3))
		handle_vec(line + 3, &obj->normals, true);
	else if (!ft_memcmp(line, "vt ", 3))
		handle_vec(line + 3, &obj->uvs, false);
	else if (!ft_memcmp(line, "f ", 2))
		parse_faces(line + 2, obj);
	else if (!ft_memcmp(line, "mtllib ", 7))
		parse_mtl(line + 7, obj);
	else if (!ft_memcmp(line, "usemtl ", 7))
		set_mtl(line + 7, obj);
	else if (!ft_memcmp(line, "o ", 2))
		create_new_submesh(obj);
	else
	{
		ft_putendl("Unknown in .obj: ");
		ft_putendl(line);
	}
}

void *parse_obj(t_model *model)
{
	t_obj		obj;
	char		*line;
	const int	fd = open(model->filepath, O_RDONLY);
	
	prepare_obj(&obj);
	obj.result = model;
	if (fd > 2)
	{
		while (get_next_line(fd, &line) > 0)
		{
			if (*line != '#' && *line != '\n' && *line)
				parse_single_line(line, &obj);
			free(line);
		}
		close(fd);
	}
	ft_vec_del(&obj.positions);
	ft_vec_del(&obj.normals);
	ft_vec_del(&obj.uvs);
	ft_vec_del(&obj.materials);
	return NULL;
}