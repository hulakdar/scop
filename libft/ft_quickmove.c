/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quickmove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 17:28:57 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/05 12:22:18 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_quickmove(void *dst, void *src, size_t size)
{
	unsigned long long	*tdst;
	unsigned long long	*tsrc;

	size >>= 3;
	tdst = (unsigned long long *)dst;
	tsrc = (unsigned long long *)src;
	while (size--)
		tdst[size] = tsrc[size];
	return (dst);
}
