/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:11:05 by smamalig          #+#    #+#             */
/*   Updated: 2025/07/11 15:56:13 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/unistd.h>
#include <sys/fcntl.h>
#include <unistd.h>

static void	pipex_parse_env(t_pipex *pipex, char **envp)
{
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			pipex->path = ft_split(*envp + 5, ':');
		}
		else if (ft_strncmp(*envp, "HOME=", 5) == 0)
		{
			pipex->home = ft_strdup(*envp + 5);
		}
		envp++;
	}
}

static int	pipex_init(t_pipex *pipex, int argc, char **argv, char **envp)
{
	pipex->envp = envp;
	pipex->nodes = ft_calloc((size_t)(argc - 3 - pipex->here_doc),
			sizeof(t_pipex_exec));
	if (!pipex->nodes)
		return (1);
	pipex->name = argv[0];
	return (0);
}

int	pipex_cleanup(t_pipex *pipex)
{
	auto int i = -1;
	while (++i < pipex->node_count)
	{
		auto int j = -1;
		if (pipex->nodes[i].argv)
			while (pipex->nodes[i].argv[++j])
				free(pipex->nodes[i].argv[j]);
		free(pipex->nodes[i].argv);
		free(pipex->nodes[i].file);
	}
	i = -1;
	if (pipex->path)
		while (pipex->path[++i])
			free(pipex->path[i]);
	free(pipex->path);
	free(pipex->home);
	free(pipex->nodes);
	return (1);
}

static int	pipex_here_doc(const char *limiter)
{
	char	*line;
	int		fd;

	line = NULL;
	fd = open("/tmp/.pipex_here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	while (1)
	{
		ft_printf("> ");
		line = get_next_line(0, false);
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& line[ft_strlen(limiter)] == '\n')
			break ;
		ft_dprintf(fd, "%s", line);
		free(line);
	}
	free(line);
	get_next_line(0, true);
	close(fd);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		exit_code;

	ft_memset(&pipex, 0, sizeof(t_pipex));
	if (argc > 2 && ft_strcmp(argv[1], "here_doc") == 0)
		pipex.here_doc = true;
	if (argc < 5 + pipex.here_doc)
		return (ft_dprintf(2, USAGE HEREDOC_USAGE, argv[0], argv[0]), 1);
	if (pipex_init(&pipex, argc, argv, envp))
		return (pipex_init_failure(argv[0]));
	pipex_parse_env(&pipex, envp);
	pipex_parse_arguments(&pipex, argc - pipex.here_doc, argv + pipex.here_doc);
	if (pipex.here_doc)
		pipex_here_doc(argv[2]);
	pipex_open_files(&pipex, argc - pipex.here_doc, argv + pipex.here_doc);
	exit_code = pipex_exec(&pipex);
	pipex_cleanup(&pipex);
	return (exit_code);
}
