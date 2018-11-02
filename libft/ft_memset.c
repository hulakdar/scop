/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 15:03:48 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/05 12:22:09 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	u;
	unsigned int	count;
	unsigned char	*tmp;

	u = (unsigned char)c;
	tmp = (unsigned char *)b;
	count = 0;
	while (count < len)
	{
		tmp[count] = u;
		count++;
	}
	return (b);
}
