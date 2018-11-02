/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 16:47:02 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/05 12:22:27 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char	*tmp;
	size_t	count;

	tmp = ft_memchr(s1, 0, ft_strlen(s1) + 1);
	count = 0;
	while (s2[count] && count < n)
	{
		tmp[count] = s2[count];
		count++;
	}
	tmp[count] = 0;
	return (s1);
}
