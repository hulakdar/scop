/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 16:01:23 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/05 12:22:28 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	unsigned int	count;

	count = 0;
	while (src[count] && count < len)
	{
		dst[count] = src[count];
		count++;
	}
	while (count < len)
		dst[count++] = 0;
	return (dst);
}
