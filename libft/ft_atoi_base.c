/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 14:02:10 by exam              #+#    #+#             */
/*   Updated: 2017/12/05 12:28:39 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_proper(char num, int str_base)
{
	char	*base;
	int		cunt;

	cunt = 0;
	base = "0123456789abcdef";
	while (cunt < str_base && base[cunt])
	{
		if (ft_tolower(num) == base[cunt])
			return (1);
		cunt++;
	}
	return (0);
}

int		ft_get_num(char num)
{
	num = ft_tolower(num);
	if (num >= '0' && num <= '9')
		return (num - '0');
	return (num - 'a' + 10);
}

int		ft_atoi_base(const char *str, int str_base)
{
	int		sign;
	int		result;

	sign = 1;
	if (*str == '-' && str++)
		sign = -1;
	result = 0;
	while (*str)
	{
		if (ft_proper(*str, str_base))
		{
			result *= str_base;
			result += ft_get_num(*str);
		}
		else
			break ;
		str++;
	}
	return (result * sign);
}
