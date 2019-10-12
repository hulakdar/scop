#include "obj.h"

static void new_material(const char* line, t_obj* obj)
{
	t_material material;

	ft_bzero(&material, sizeof(t_material));
	material.name = ft_strdup(line);
	obj->current_material = (t_material*)ft_vec_pushback(&obj->materials, &material);
}

static void parse_color(const char* line, t_obj* obj)
{
	t_float4	value;
	float		*dst;

	while (!ft_isprint(*line))
		line++;
	value = parse_vec3(line);
	if (obj->current_material)
	{
		obj->current_material->diffuse.type = UT_VEC4;
		dst = obj->current_material->diffuse.data.vec4;
		dst[0] = value.x;
		dst[1] = value.y;
		dst[2] = value.z;
		dst[3] = value.w;
	}
}

static void parse_texture(const char* line, t_obj* obj)
{
	// in main thread please
	if (obj->current_material)
	{
		obj->current_material->diffuse.type = UT_VEC4;
		dst = obj->current_material->diffuse.data.vec4;
		dst[0] = value.x;
		dst[1] = value.y;
		dst[2] = value.z;
		dst[3] = value.w;
	}
}

static void	parse_single_line(const char* line, t_obj* obj)
{
	while (!ft_isprint(*line))
		line++;
	if (!ft_memcmp(line, "newmtl ", 7))
		new_material(line + 7, obj);
	else if (!ft_memcmp(line, "Kd ", 3))
		parse_color(line + 3, obj);
	else if (!ft_memcmp(line, "map_Kd ", 7))
		parse_texture(line + 7, obj);
	else
	{
		ft_putendl("Unknown in .mtl: ");
		ft_putendl(line);
	}
}

static char* find_mtllib(const char *line, const char *filepath)
{
	char* result;
	char* seeker;

	while (*line == ' ')
		line++;
	result = ft_strdup(filepath);
	if ((seeker = ft_strrchr(result, '/')))
		*(seeker + 1) = 0;
	ft_strcat(result, line);
	return result;
}

void parse_mtl(const char *filename, t_obj *model)
{
	char	*filepath = find_mtllib(filename, model->result->filepath);
	char	*line;
	const int	fd = open(filepath, O_RDONLY);
	
	if (fd > 0)
	{
		while (get_next_line(fd, &line) > 0)
		{
			if (*line != '#' && *line != '\n' && *line)
				parse_single_line(line, model);
			free(line);
		}
		close(fd);
	}
	free(filepath);
}

