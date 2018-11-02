/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 18:00:20 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/05 12:22:31 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_panic(char ***hint)
{
	char	**output;
	size_t	cunt;

	cunt = 0;
	output = *hint;
	while (output[cunt])
	{
		free(output[cunt]);
		output[cunt] = NULL;
		cunt++;
	}
	free(*hint);
	*hint = NULL;
}

static void	ft_counter(char *str, int *word_count, int *has_words, char c)
{
	while (*str)
	{
		while ((*str == c) && *str)
			str++;
		while (!(*str == c) && *str)
		{
			str++;
			*has_words = 1;
		}
		*word_count += 1;
	}
}

static void	ft_suballocator(char *str, char ***hint, char c)
{
	char	*seeker;
	char	**output;
	int		counter;

	seeker = str;
	counter = 0;
	output = *hint;
	while (*str)
	{
		while ((*str == c) && *str)
			str++;
		seeker = str;
		while (!(*seeker == c) && *seeker)
			seeker++;
		if (str < seeker)
		{
			output[counter] = ft_strsub(str, 0, seeker - str);
			if (!output[counter])
			{
				ft_panic(hint);
				return;
			}
			counter++;
			str = seeker;
		}
	}
	output[counter] = NULL;
}

char		**ft_strsplit(char const *str, char c)
{
	char	**output;
	int		word_count;
	int		has_words;

	if (!str)
		return (NULL);
	has_words = 0;
	word_count = 0;
	ft_counter((char *)str, &word_count, &has_words, c);
	output = malloc((word_count + has_words) * sizeof(char *));
	if (output)
		ft_suballocator((char *)str, &output, c);
	return (output);
}
