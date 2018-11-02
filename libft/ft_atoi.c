/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 17:16:17 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/05 12:20:13 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int index;
	int sign;
	int result;

	index = 0;
	sign = 1;
	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (str[index] >= '0' && str[index] <= '9')
	{
		if (index >= 19)
			return (sign > 0 ? -1 : 0);
		result = (result * 10) + (str[index] - '0');
		index++;
	}
	return (result * sign);
}
