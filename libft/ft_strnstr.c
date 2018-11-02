/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 17:11:23 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/05 12:22:30 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*sub;
	char	*str;
	size_t	cunt;
	size_t	l;

	sub = (char *)little;
	str = (char *)big;
	if (!*little)
		return ((char *)big);
	cunt = 0;
	l = ft_strlen(little);
	while (str[cunt] && cunt + l < len + 1)
	{
		if (!ft_memcmp(&str[cunt], sub, l))
			return (&str[cunt]);
		cunt++;
	}
	return (NULL);
}
