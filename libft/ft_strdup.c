/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 15:51:29 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/05 12:22:23 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*result;
	int		counter;

	result = malloc(ft_strlen(s) + 1);
	if (!result || !s)
		return (NULL);
	counter = -1;
	while (s[++counter])
		result[counter] = s[counter];
	result[counter] = '\0';
	return (result);
}
