/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 22:18:50 by smamalig          #+#    #+#             */
/*   Updated: 2025/07/17 08:51:06 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

void	pipex_open_files(t_pipex *pipex, int argc, char **argv)
{
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (pipex->here_doc)
	{
		pipex->fd_in = open("/tmp/.pipex_here_doc", O_RDONLY);
		flags |= O_APPEND;
	}
	else
	{
		pipex->fd_in = open(argv[1], O_RDONLY);
		flags |= O_TRUNC;
	}
	pipex->fd_out = open(argv[argc - 1], flags, 0644);
	if (pipex->fd_out < 0)
		close(pipex->fd_in);
}

char	*pipex_get_bin(t_pipex *pipex, char *arg)
{
	char	*path;
	int		i;
	size_t	len;

	i = -1;
	if (!pipex->path || !arg)
		return (NULL);
	while (pipex->path[++i])
	{
		len = ft_strlen(pipex->path[i]) + ft_strlen(arg) + 2;
		path = ft_malloc(len);
		if (!path)
			return (NULL);
		ft_snprintf(path, len, "%s/%s", pipex->path[i], arg);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
	}
	return (NULL);
}

static int	pipex_expand_home(t_pipex *pipex, char **argv)
{
	char	*tmp;
	size_t	len;

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

static int	pipex_parse_exec(t_pipex *pipex, char *arg)
{
	t_pipex_exec	*exec;
	const int		argv_len = pipex_tokenize(arg, NULL);

	exec = pipex->nodes + pipex->node_count++;
	exec->argv = ft_calloc((size_t)argv_len, sizeof(char *));
	if (!exec->argv || pipex_tokenize(arg, exec->argv) != argv_len)
		return (1);
	if (!exec->argv[0])
	{
		free(exec->argv);
		exec->argv = ft_calloc(2, sizeof(char *));
		if (!exec->argv)
			return (1);
		exec->argv[0] = ft_strdup("/bin/true");
	}
	if (pipex_expand_home(pipex, exec->argv))
		return (1);
	if (exec->argv[0] && ft_strchr(exec->argv[0], '/'))
	{
		if (access(exec->argv[0], X_OK) == 0)
			exec->file = ft_strdup(exec->argv[0]);
	}
	else
		exec->file = pipex_get_bin(pipex, exec->argv[0]);
	return (0);
}

void	pipex_parse_arguments(t_pipex *pipex, int argc, char **argv)
{
	int	i;

	i = 1;
	if (!pipex->here_doc && access(argv[i], R_OK) == -1)
		pipex_perror(pipex, argv[i]);
	while (++i < argc - 1)
		pipex_parse_exec(pipex, argv[i]);
	if (access(argv[argc - 1], W_OK) < 0 && errno != ENOENT)
		pipex_perror(pipex, argv[argc - 1]);
}
