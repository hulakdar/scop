#include "obj.h"

void parse_mtl(const char *line, t_obj *model)
{
	t_mtl		mtl;
	char		*line;
	const int	fd = open(model->filepath, O_RDONLY);
	
	prepare_obj(&mtl);
	mtl.result = model;
	if (fd > 2)
	{
		int i = 0;
		while (get_next_line(fd, &line) > 0)
		{
			if (*line != '#' && *line != ' ' && *line)
				parse_single_line(line, &mtl);
			free(line);
			i++;
		}
		close(fd);
	}
	ft_vec_del(&mtl.positions);
	ft_vec_del(&mtl.normals);
	ft_vec_del(&mtl.uvs);
}

