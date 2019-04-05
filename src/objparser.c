
#include "obj.h"
#include <stdio.h>

float		*get_skybox()
{
	static const float skyboxVertices[] = { -1.f, 1.f, -1.f, -1.f, -1.f, -1.f,
	1.f, -1.f, -1.f, 1.f, -1.f, -1.f, 1.f, 1.f, -1.f, -1.f,  1.f, -1.f, -1.f, -1.f,
	1.f, -1.f, -1.f, -1.f, -1.f, 1.f, -1.f, -1.f, 1.f, -1.f, -1.f, 1.f, 1.f, -1.f,
	-1.f, 1.f, 1.f, -1.f, -1.f, 1.f, -1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f,
	1.f, -1.f, 1.f, -1.f, -1.f, -1.f, -1.f, 1.f, -1.f, 1.f, 1.f, 1.f, 1.f, 1.f,
	1.f, 1.f, 1.f, 1.f, -1.f, 1.f, -1.f, -1.f, 1.f, -1.f, 1.f, -1.f, 1.f, 1.f,
	-1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, -1.f, 1.f, 1.f, -1.f, 1.f, -1.f, -1.f,
	-1.f, -1.f, -1.f, -1.f, 1.f, 1.f, -1.f, -1.f, 1.f, -1.f, -1.f, -1.f, -1.f,
	1.f, 1.f, -1.f,  1.f };
	return (float *)skyboxVertices;
}

static inline void deinit_tmp(t_obj *obj)
{
	ft_vec_del(&obj->positions);
	ft_vec_del(&obj->normals);
	ft_vec_del(&obj->uvs);
}

static inline void parse_single_line(const char *line, t_obj *obj, t_model *model)
{
	if (!ft_memcmp(line, "v ", 2))
		parse_vec3(line + 2, &obj->positions);
	else if (!ft_memcmp(line, "vn ", 3))
		parse_vec3(line + 3, &obj->normals);
	else if (!ft_memcmp(line, "vt ", 3))
		parse_vec2(line + 3, &obj->uvs);
	else if (!ft_memcmp(line, "f ", 2))
		parse_faces(line + 2, obj, model);
	else if (!ft_memcmp(line, "mtlib ", 6))
		parse_mtl(line + 6, model);
	else
		printf("I don't know what is this stuff: \n%s\n", line);
}

t_model parse_obj(const char *filepath)
{
	t_model	result;
	t_obj	obj;
	char *line;
	const int fd = open(filepath, O_RDONLY);
	
	ft_vec_init(&obj.positions, sizeof(t_float4), 256);
	ft_vec_init(&obj.normals, sizeof(t_float4), 256);
	ft_vec_init(&obj.uvs, sizeof(t_float2), 256);
	if (fd > 2)
	{
		while (get_next_line(fd, &line) > 0)
		{
			if (*line != '#' && *line != ' ' && *line)
				parse_single_line(line, &obj, &result);
			free(line);
		}
		close(fd);
	}
	deinit_tmp(&obj);
	return result;
}