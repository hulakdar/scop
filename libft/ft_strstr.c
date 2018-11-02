/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 17:10:32 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/05 12:22:31 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	char *sub;
	char *guess;
	char *str;

	sub = (char *)needle;
	str = (char *)haystack - 1;
	if (!*needle)
		return ((char *)haystack);
	while (*(++str))
	{
		guess = str;
		while (*(str++) == *(sub++))
			if (!*sub)
				return (guess);
		str = guess;
		sub = (char *)needle;
	}
	return (NULL);
}
