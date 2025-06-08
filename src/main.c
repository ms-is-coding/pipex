/* ************************************************************************** */
/*                                                                            */
/*                                                         ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀   */
/*   main.c                                                ⠀⠀⠀⠀⢀⣴⣿⠟⠁ ⣿⠟⢹⣿⣿⠀   */
/*                                                         ⠀⠀⢀⣴⣿⠟⠁⠀⠀⠀⠁⢀⣼⣿⠟⠀   */
/*   By: smamalig <smamalig@student.42.fr>                 ⠀⣴⣿⣟⣁⣀⣀⣀⡀⠀⣴⣿⡟⠁⢀⠀   */
/*                                                         ⠀⠿⠿⠿⠿⠿⣿⣿⡇⠀⣿⣿⣇⣴⣿⠀   */
/*   Created: 2025/05/26 15:11:05 by smamalig              ⠀⠀⠀⠀⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀   */
/*   Updated: 2025/06/08 14:21:18 by smamalig              ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀   */
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

int	pipex_parse_env(t_pipex *pipex, char **envp)
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
	if (!pipex->home || !pipex->path)
		return (1);
	return (0);
}

int	pipex_init(t_pipex *pipex, int argc, char **argv, char **envp)
{
	pipex->path = NULL;
	pipex->home = NULL;
	pipex->envp = envp;
	pipex->nodes = ft_calloc(argc, sizeof(t_pipex_exec));
	pipex->node_count = 0;
	pipex->name = argv[0];
	return (0);
}

int	pipex_cleanup(t_pipex *pipex)
{
	int	i;
	int	j;

	i = -1;
	while (++i < pipex->node_count)
	{
		j = -1;
		while (pipex->nodes[i].argv[++j])
			free(pipex->nodes[i].argv[j]);
		free(pipex->nodes[i].argv);
		free(pipex->nodes[i].file);
	}
	free(pipex->nodes);
	i = -1;
	while (pipex->path[++i])
		free(pipex->path[i]);
	free(pipex->path);
	free(pipex->home);
	return (0);
}

int	pipex_open_files(t_pipex *pipex, int argc, char **argv)
{
	pipex->fd_in = open(argv[1], O_RDONLY);
	if (pipex->fd_in == -1)
		return (pipex_read_error(pipex, argv[1]));
	pipex->fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->fd_out == -1)
	{
		close(pipex->fd_in);
		pipex_write_error(pipex, argv[argc - 1]);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc < 4)
		return (ft_dprintf(2, INCORRECT_USAGE, argv[0]), 1);
	if (pipex_init(&pipex, argc, argv, envp))
		return (pipex_init_failure(argv[0]));
	if (pipex_parse_env(&pipex, envp))
		return (pipex_invalid_env(argv[0]));
	if (pipex_parse_arguments(&pipex, argc, argv))
		return (pipex_cleanup(&pipex));
	if (pipex_open_files(&pipex, argc, argv))
		return (pipex_cleanup(&pipex));
	pipex_exec(&pipex);
	pipex_cleanup(&pipex);
	return (0);
}
