/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 17:48:49 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/05 12:22:26 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	cunt;
	char	*result;

	result = NULL;
	if (s)
		result = ft_strnew(ft_strlen(s));
	if (result)
	{
		cunt = 0;
		while (s[cunt])
		{
			result[cunt] = f(s[cunt]);
			cunt++;
		}
		result[cunt] = 0;
	}
	return (result);
}
