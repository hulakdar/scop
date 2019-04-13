#include "libft.h"

int ft_chrcnt(const char *str, char chr)
{
	size_t count;

	count = 0;
	while (*str)
		if (*(str++) == chr)
			count++;
	return count;
}

