#include "libft.h"

float ft_atof(const char *str)
{
	const size_t length = ft_wordlen(str);
	const char *const dot = ft_memchr(str, '.', length);
	double result;
	double sign;

	result = 1;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	result *= ft_atoull(str);
	if (dot)
	{
		size_t after_dot = ft_atoull(dot + 1);
		size_t afer_dot_len = ft_wordlen(dot + 1);
		double divisor = ft_intpow(10, afer_dot_len);
		result += after_dot / divisor;
	}
	return result * sign;
}