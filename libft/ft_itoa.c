/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 18:04:08 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/05 12:21:41 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strrevcpy(char *ptr, char *digits, int counter, int nb)
{
	int	cunt;

	cunt = 0;
	if (nb < 0 && ((ptr[cunt++] = '-')))
		ptr[cunt++] = -nb + 48;
	else
		ptr[cunt++] = nb + 48;
	while (--counter >= 0)
		ptr[cunt++] = digits[counter];
}

char		*ft_itoa(int nb)
{
	char	digits[12];
	char	*ptr;
	int		counter;

	counter = 0;
	digits[counter++] = '\0';
	while (nb / 10)
	{
		if (nb < 0)
			digits[counter++] = -(nb % 10) + 48;
		else
			digits[counter++] = (nb % 10) + 48;
		nb /= 10;
	}
	ptr = ft_strnew(nb < 0 ? counter + 1 : counter);
	if (ptr)
		ft_strrevcpy(ptr, digits, counter, nb);
	return (ptr);
}
