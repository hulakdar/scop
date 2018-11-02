
#include "obj.h"
#include <stdio.h>

static inline void init_model(t_model *model, t_obj *obj)
{
	ft_vec_init(&model->vertecies, sizeof(t_vertex), 256);
	ft_vec_init(&obj->indicies, sizeof(unsigned) * 9, 256);
	ft_vec_init(&obj->normals, sizeof(t_vec3), 256);
	ft_vec_init(&obj->positions, sizeof(t_vec3), 256);
	ft_vec_init(&obj->uvs, sizeof(t_vec2), 256);
}

static inline void deinit_tmp(t_obj *obj)
{
	ft_vec_del(&obj->indicies);
	ft_vec_del(&obj->normals);
	ft_vec_del(&obj->positions);
	ft_vec_del(&obj->uvs);
}

static inline void parse_single_line(const char *line, t_obj *obj, t_model *model)
{
	if (!ft_memcmp(line, "v ", 2))
		parse_vec3(line + 2, &obj->positions);
	else if (!ft_memcmp(line, "vn ", 2))
		parse_vec3(line + 3, &obj->normals);
	else if (!ft_memcmp(line, "vt ", 2))
		parse_vec2(line + 3, &obj->uvs);
	else if (!ft_memcmp(line, "f ", 2))
		parse_faces(line + 2, obj, model);
	else if (!ft_memcmp(line, "mtlib ", 2))
		;//parse_mtl(line + 6, &obj->materials);
	else
		printf("I don't know what is this stuff: \n%s\n", line);
}

t_model parse_obj(const char *filepath)
{
	t_model	result;
	t_obj	obj;
	char *line;
	const int fd = open(filepath, O_RDONLY);
	
	init_model(&result, &obj);
	if (fd > 2)
		while (get_next_line(fd, &line))
		{
			if (*line != '#' && *line != ' ')
				parse_single_line(line, &obj, &result);
			free(line);
		}
	deinit_tmp(&obj);
	return result;
}