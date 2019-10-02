#include "obj.h"

static void new_material(const char* line, t_obj* obj)
{
	t_material material;

	ft_bzero(&material, sizeof(t_material));
	material.name = ft_strdup(line);
	ft_vec_pushback(&obj->materials, &material);
}

static void parse_color(const char* line, t_obj* obj)
{
	const t_float4 value = parse_vec3(line);
}

static void	parse_single_line(const char* line, t_obj* obj)
{
	while (*line == ' ')
		line++;
	if (!ft_memcmp(line, "newmtl ", 7))
		new_material(line + 7, obj);
	else if (!ft_memcmp(line, "Ka ", 3))
		parse_color(line + 3, obj);
	else
		printf("Unknown in .mtl: \n%s\n", line);
}

static char* find_mtllib(const char *line, const char *filepath)
{
	char* result;
	char* seeker;

	while (*line == ' ')
		line++;
	result = ft_strdup(filepath);
	if ((seeker = ft_strrchr(result, '/')))
		*seeker = 0;
	ft_strcat(result, line);
	return result;
}

void parse_mtl(const char *line, t_obj *model)
{
	char* filepath = find_mtllib(line, model->result->filepath);
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

