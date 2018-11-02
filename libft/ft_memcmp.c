/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 15:42:26 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/05 12:22:05 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*t1;
	unsigned char	*t2;
	unsigned int	count;

	if (!n)
		return (0);
	t1 = (unsigned char *)s1;
	t2 = (unsigned char *)s2;
	count = 0;
	while (count + 1 < n && t1[count] == t2[count])
		count++;
	return (t1[count] - t2[count]);
}
