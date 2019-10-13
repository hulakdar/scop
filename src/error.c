/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 23:47:34 by skamoza           #+#    #+#             */
/*   Updated: 2019/10/13 23:48:39 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

unsigned	scop_error(const char *error)
{
	ft_putendl_fd(error, 2);
	DEBUG_BREAK();
	return (-1);
}

void		gl_clear_error(void)
{
	while (glGetError())
		continue;
}

char		gl_check_error(const char *function, const char *file, int line)
{
	GLenum error;

	(void)function;
	(void)file;
	(void)line;
	while ((error = glGetError()))
	{
		DEBUG_BREAK();
	}
	return (1);
}
