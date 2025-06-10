/* ************************************************************************** */
/*                                                                            */
/*                                                         ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀   */
/*   tokenize.c                                            ⠀⠀⠀⠀⢀⣴⣿⠟⠁ ⣿⠟⢹⣿⣿⠀   */
/*                                                         ⠀⠀⢀⣴⣿⠟⠁⠀⠀⠀⠁⢀⣼⣿⠟⠀   */
/*   By: smamalig <smamalig@student.42.fr>                 ⠀⣴⣿⣟⣁⣀⣀⣀⡀⠀⣴⣿⡟⠁⢀⠀   */
/*                                                         ⠀⠿⠿⠿⠿⠿⣿⣿⡇⠀⣿⣿⣇⣴⣿⠀   */
/*   Created: 2025/06/06 19:16:02 by smamalig              ⠀⠀⠀⠀⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀   */
/*   Updated: 2025/06/09 15:47:46 by smamalig              ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include <stdlib.h>

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

static inline char	quote_lookup(char curr, char quote)
{
	if (quote == '\'' && curr == '\'')
		return (0);
	if (quote == '"' && curr == '"')
		return (0);
	if (!quote && (curr == '"' || curr == '\''))
		return (curr);
	return (quote);
}

static inline int	should_start(char *s)
{
	if (s[0] == ' ')
		return (-1);
	if (s[0] == '"' && s[1] != '"')
		return (-1);
	if (s[0] == '\'' && s[1] != '\'')
		return (-1);
	if (s[0] == '"' && s[1] == '"')
		return (1);
	if (s[0] == '\'' && s[1] == '\'')
		return (1);
	return (0);
}

int	pipex_tokenize(char *s, char **collector)
{
	int			count;
	const char	*start;
	char		quote;

	count = 0;
	start = NULL;
	quote = 0;
	while (1)
	{
		if (should_start(s) != -1 && !start)
			start = s + should_start(s);
		else if (start && ((!quote && (*s == ' ' || !*s)) || *s == quote))
		{
			alloc_sub(s, start, count, collector);
			count++;
			start = NULL;
		}
		quote = quote_lookup(*s, quote);
		if (!*s)
			break ;
		s++;
	}
	if (collector)
		collector[count] = NULL;
	return (count + 1);
}
