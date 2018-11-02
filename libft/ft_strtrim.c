/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 17:54:53 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/05 12:22:32 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_isws(char c)
{
	return (c == ' ' || c == '\n' || c == '\t' ? 1 : 0);
}

char			*ft_strtrim(char const *s)
{
	unsigned int	start;
	size_t			len;

	start = 0;
	if (s)
	{
		if (!*s)
			return (ft_strdup(s));
		while (ft_isws(s[start]) && s[start])
			start++;
		len = ft_strlen(s);
		while (!s[len] || (len > start && (ft_isws(s[len]))))
		{
			len--;
		}
		if (len > start)
			return (ft_strsub(s, start, len - start + 1));
		return (ft_strdup(""));
	}
	return (NULL);
}
