/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 15:30:54 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/05 12:22:04 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	count;
	unsigned char	*tmp;

	count = 0;
	tmp = (unsigned char *)s;
	while (count < n)
	{
		if (tmp[count] == (unsigned char)c)
			return ((void *)&tmp[count]);
		count++;
	}
	return (NULL);
}
