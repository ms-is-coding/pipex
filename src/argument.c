/* ************************************************************************** */
/*                                                                            */
/*                                                         ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀   */
/*   argument.c                                            ⠀⠀⠀⠀⢀⣴⣿⠟⠁ ⣿⠟⢹⣿⣿⠀   */
/*                                                         ⠀⠀⢀⣴⣿⠟⠁⠀⠀⠀⠁⢀⣼⣿⠟⠀   */
/*   By: smamalig <smamalig@student.42.fr>                 ⠀⣴⣿⣟⣁⣀⣀⣀⡀⠀⣴⣿⡟⠁⢀⠀   */
/*                                                         ⠀⠿⠿⠿⠿⠿⣿⣿⡇⠀⣿⣿⣇⣴⣿⠀   */
/*   Created: 2025/06/06 22:18:50 by smamalig              ⠀⠀⠀⠀⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀   */
/*   Updated: 2025/06/10 19:26:06 by smamalig              ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int	pipex_open_files(t_pipex *pipex, int argc, char **argv)
{
	int	flags;

	if (!pipex->heredoc)
	{
		pipex->fd_in = open(argv[1], O_RDONLY);
		if (pipex->fd_in == -1)
			return (pipex_perror(pipex, argv[1]));
	}
	flags = O_WRONLY | O_CREAT | O_TRUNC;
	pipex->fd_out = open(argv[argc - 1], flags, 0644);
	if (pipex->fd_out == -1)
	{
		close(pipex->fd_in);
		pipex_perror(pipex, argv[argc - 1]);
		return (1);
	}
	return (0);
}

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
		ft_snprintf(path, len, "%s/%s", pipex->path[i], arg);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
	}
	return (NULL);
}

int	pipex_expand_home(t_pipex *pipex, char **argv)
{
	char	*tmp;
	int		len;

	if (!pipex->home)
		return (0);
	while (*argv)
	{
		if (ft_strncmp(*argv, "~/", 2) == 0)
		{
			len = ft_strlen(pipex->home) + ft_strlen(*argv + 2) + 2;
			tmp = *argv;
			*argv = ft_malloc(len);
			if (!*argv)
			{
				*argv = tmp;
				return (1);
			}
			ft_snprintf(*argv, len, "%s/%s", pipex->home, tmp + 2);
			free(tmp);
		}
		argv++;
	}
	return (0);
}

int	pipex_parse_exec(t_pipex *pipex, char *arg, char **name)
{
	t_pipex_exec	*exec;

	exec = pipex->nodes + pipex->node_count++;
	exec->argv = ft_calloc(pipex_tokenize(arg, NULL), sizeof(char *));
	pipex_tokenize(arg, exec->argv);
	if (!exec->argv[0])
	{
		free(exec->argv);
		exec->argv = ft_calloc(2, sizeof(char *));
		exec->argv[0] = ft_strdup("/bin/true");
	}
	*name = exec->argv[0];
	if (pipex_expand_home(pipex, exec->argv))
		return (1);
	if (access(exec->argv[0], X_OK) == 0)
		exec->file = ft_strdup(exec->argv[0]);
	else
		exec->file = pipex_get_bin(pipex, exec->argv[0]);
	if (!exec->file)
		return (1);
	return (0);
}

int	pipex_parse_arguments(t_pipex *pipex, int argc, char **argv)
{
	int		i;
	char	*name;

	i = 1;
	if (!pipex->heredoc && access(argv[i], R_OK) == -1)
		pipex->had_error |= pipex_perror(pipex, argv[i]);
	while (++i < argc - 1)
	{
		if (pipex_parse_exec(pipex, argv[i], &name))
			pipex->had_error |= pipex_argument_error(pipex, argv[i]);
	}
	if (access(argv[argc - 1], W_OK) == -1 && errno != ENOENT)
		pipex->had_error |= pipex_perror(pipex, argv[argc - 1]);
	return (pipex->had_error);
}
