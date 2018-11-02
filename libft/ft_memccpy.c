/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 15:20:53 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/05 12:22:03 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	char *tmpd;
	char *tmps;

	tmpd = (char *)dest;
	tmps = (char *)src;
	while (n--)
	{
		*tmpd = *tmps;
		if (*tmpd == (char)c)
			return ((void *)(tmpd + 1));
		tmpd++;
		tmps++;
	}
	return (NULL);
}
