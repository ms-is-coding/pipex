/* ************************************************************************** */
/*                                                                            */
/*                                                         ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀   */
/*   argument.c                                            ⠀⠀⠀⠀⢀⣴⣿⠟⠁ ⣿⠟⢹⣿⣿⠀   */
/*                                                         ⠀⠀⢀⣴⣿⠟⠁⠀⠀⠀⠁⢀⣼⣿⠟⠀   */
/*   By: smamalig <smamalig@student.42.fr>                 ⠀⣴⣿⣟⣁⣀⣀⣀⡀⠀⣴⣿⡟⠁⢀⠀   */
/*                                                         ⠀⠿⠿⠿⠿⠿⣿⣿⡇⠀⣿⣿⣇⣴⣿⠀   */
/*   Created: 2025/06/06 22:18:50 by smamalig              ⠀⠀⠀⠀⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀   */
/*   Updated: 2025/06/08 15:31:03 by smamalig              ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

char	*pipex_get_bin(t_pipex *pipex, char *arg)
{
	char	*path;
	int		i;
	size_t	len;

	i = -1;
	while (pipex->path[++i])
	{
		len = ft_strlen(pipex->path[i]) + ft_strlen(arg) + 2;
		path = malloc(len);
		ft_snprintf(path, 1024, "%s/%s", pipex->path[i], arg);
		if (access(path, X_OK) == 0)
			return (ft_strdup(path));
		free(path);
	}
	return (NULL);
}

int	pipex_parse_exec(t_pipex *pipex, char *arg)
{
	t_pipex_exec	*exec;
	int				len;

	exec = pipex->nodes + pipex->node_count++;
	exec->argv = ft_calloc(pipex_tokenize(arg, NULL), sizeof(char *));
	pipex_tokenize(arg, exec->argv);
	if (ft_strncmp(exec->argv[0], "/", 1) == 0
		|| ft_strncmp(exec->argv[0], "./", 2) == 0)
	{
		exec->file = ft_strdup(arg);
	}
	else if (ft_strncmp(exec->argv[0], "~/", 2) == 0)
	{
		len = ft_strlen(pipex->home) + ft_strlen(exec->argv[0] + 2) + 2;
		exec->file = ft_malloc(len);
		ft_snprintf(exec->file, len, "%s/%s", pipex->home, exec->argv[0] + 2);
	}
	else
		exec->file = pipex_get_bin(pipex, exec->argv[0]);
	if (!exec->file || access(exec->file, X_OK) == -1)
		return (1);
	return (0);
}

int	pipex_parse_arguments(t_pipex *pipex, int argc, char **argv)
{
	int	i;
	int	had_error;

	i = 1;
	had_error = 0;
	if (access(argv[i], R_OK) == -1)
		return (pipex_read_error(pipex, argv[i]));
	while (++i < argc - 1)
	{
		if (pipex_parse_exec(pipex, argv[i]))
			had_error |= pipex_argument_error(pipex, argv[i]);
	}
	if (had_error)
		return (1);
	return (0);
}
