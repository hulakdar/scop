/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 16:42:36 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/05 12:22:20 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	size_t len;
	size_t cunt;

	cunt = -1;
	len = ft_strlen(dest);
	while (src[++cunt])
		dest[len + cunt] = src[cunt];
	dest[len + cunt] = '\0';
	return (dest);
}
