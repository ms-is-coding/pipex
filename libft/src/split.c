/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                               ⠀⠀⠀⠀⢀⣴⣿⠟⠁ ⣿⠟⢹⣿⣿⠀   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:43:48 by smamalig          #+#    #+#             */
/*   Updated: 2025/06/05 22:39:11 by smamalig              ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	alloc_sub(const char *s, const char *start, int i, char **collector)
{
	if (!collector)
		return (0);
	collector[i] = malloc(s - start + 1);
	if (!collector[i])
		return (1);
	ft_memcpy(collector[i], start, s - start);
	collector[i][s - start] = 0;
	return (0);
}

static int	split_words(const char *s, char delim, char **collector)
{
	int			count;
	const char	*start;

	count = 0;
	start = NULL;
	while (1)
	{
		if (*s != delim && !start)
			start = s;
		else if (start && (*s == delim || !*s))
		{
			alloc_sub(s, start, count, collector);
			count++;
			start = NULL;
		}
		if (!*s)
			break ;
		s++;
	}
	if (collector)
		collector[count] = NULL;
	return (count + 1);
}

char	**ft_split(const char *s, char delim)
{
	char	**collector;
	int		sub_count;
	int		i;

	sub_count = split_words(s, delim, NULL);
	collector = ft_calloc(sub_count, sizeof(char *));
	if (!collector)
		return (NULL);
	if (split_words(s, delim, collector) != sub_count)
	{
		i = 0;
		while (i < sub_count)
			free(collector[i++]);
		free(collector);
		return (NULL);
	}
	return (collector);
}
