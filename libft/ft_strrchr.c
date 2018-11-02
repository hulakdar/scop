/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 17:07:48 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/05 12:22:30 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*seeker;

	seeker = (char *)(s + ft_strlen(s));
	while (seeker >= (char *)s)
	{
		if (*seeker == (char)c)
			return (seeker);
		seeker--;
	}
	return (NULL);
}
