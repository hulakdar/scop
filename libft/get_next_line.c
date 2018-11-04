/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 11:28:49 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/05 12:22:53 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcombine(char *one, char *two)
{
	char *result;

	result = ft_strjoin(one, two);
	if (one)
		free(one);
	if (two)
		free(two);
	return (result);
}

int			the_work(char **line, t_array *tmp)
{
	char			*end;
	char			*start;
	t_array			arr;

	arr = *tmp;
	start = &(arr.array[0]);
	if ((end = ft_memchr(start, '\n', arr.size)))
	{
		*line = ft_strcombine(*line, ft_strsub(start, 0, end - start));
		arr.size -= end - start + 1;
		ft_memmove(start, end + 1, arr.size);
		*tmp = arr;
		return (1);
	}
	else if (!(arr.size = 0))
		*line = ft_strcombine(*line, ft_strdup(start));
	*tmp = arr;
	return (0);
}

static int	hard_work(t_array *tmp, int fd, char **line)
{
	t_array			arr;

	arr = *tmp;
	while (1)
	{
		if (!arr.size && (arr.size = READ(fd, arr.array, BUFF_SIZE)) < 1)
		{
			if (*line)
				break ;
			return ((int)arr.size);
		}
		arr.array[arr.size] = 0;
		if (the_work(line, &arr))
			break ;
	}
	*tmp = arr;
	if (!*line)
		*line = ft_strdup("");
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static	t_array	buff[45] = {{ {0}, 0} };

	if (fd < 0 || !line || fd > 44)
		return (-1);
	*line = NULL;
	if (READ(fd, NULL, 0) < 0)
		return (-1);
	return (hard_work(&(buff[fd]), fd, line));
}
