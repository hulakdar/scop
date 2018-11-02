/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 17:52:11 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/05 12:22:32 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	cunt;

	result = NULL;
	if (s)
		result = ft_strnew(len);
	if (result)
	{
		cunt = 0;
		while (cunt < len)
		{
			result[cunt] = s[start + cunt];
			cunt++;
		}
		result[cunt] = 0;
	}
	return (result);
}
