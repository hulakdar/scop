/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 15:24:11 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/05 12:22:07 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*td;
	unsigned char	*ts;
	unsigned int	cunt;

	td = (unsigned char *)dst;
	ts = (unsigned char *)src;
	if (dst < src)
	{
		cunt = 0;
		while (cunt < len)
		{
			td[cunt] = ts[cunt];
			cunt++;
		}
	}
	else if (dst > src)
	{
		while (len > 0)
		{
			td[len - 1] = ts[len - 1];
			len--;
		}
	}
	return (dst);
}
