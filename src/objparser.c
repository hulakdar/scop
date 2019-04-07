
#include "obj.h"
#include <stdio.h>

static inline void parse_single_line(const char *line, t_obj *obj)
{
	if (!ft_memcmp(line, "v ", 2))
		parse_vec3(line + 2, &obj->positions);
	else if (!ft_memcmp(line, "vn ", 3))
		parse_vec3(line + 3, &obj->normals);
	else if (!ft_memcmp(line, "vt ", 3))
		parse_vec2(line + 3, &obj->uvs);
	else if (!ft_memcmp(line, "f ", 2))
		parse_faces(line + 2, obj);
	else if (!ft_memcmp(line, "mtlib ", 6))
		parse_mtl(line + 6, obj);
	else if (!ft_memcmp(line, "o ", 2))
		create_new_submesh(obj);
	else
		printf("I don't know what is this stuff: \n%s\n", line);
}

void *parse_obj(t_model *model)
{
	t_obj		obj;
	char		*line;
	const int	fd = open(model->filepath, O_RDONLY);
	
	ft_bzero(&obj, sizeof(t_obj));
	obj.result = model;
	ft_vec_init(&obj.positions, sizeof(t_float4), 256);
	ft_vec_init(&obj.normals, sizeof(t_float4), 256);
	ft_vec_init(&obj.uvs, sizeof(t_float2), 256);
	if (fd > 2)
	{
		int i = 0;
		while (get_next_line(fd, &line) > 0)
		{
			if (*line != '#' && *line != ' ' && *line)
				parse_single_line(line, &obj);
			free(line);
			i++;
		}
		close(fd);
	}
	ft_vec_del(&obj.positions);
	ft_vec_del(&obj.normals);
	ft_vec_del(&obj.uvs);
	model->is_done = 1;
}