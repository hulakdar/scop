/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 16:58:06 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/05 12:22:25 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	slen;
	size_t	dlen;

	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	if (dstsize && dlen < dstsize)
		ft_strncat(dst, src, dstsize - dlen - 1);
	if (dlen + slen == dstsize)
		dst[dlen + slen - 1] = 0;
	return (dlen > dstsize ? slen + dstsize : dlen + slen);
}
