/* ************************************************************************** */
/*                                                                            */
/*                                                         ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀   */
/*   main.c                                                ⠀⠀⠀⠀⢀⣴⣿⠟⠁ ⣿⠟⢹⣿⣿⠀   */
/*                                                         ⠀⠀⢀⣴⣿⠟⠁⠀⠀⠀⠁⢀⣼⣿⠟⠀   */
/*   By: smamalig <smamalig@student.42.fr>                 ⠀⣴⣿⣟⣁⣀⣀⣀⡀⠀⣴⣿⡟⠁⢀⠀   */
/*                                                         ⠀⠿⠿⠿⠿⠿⣿⣿⡇⠀⣿⣿⣇⣴⣿⠀   */
/*   Created: 2025/05/26 15:11:05 by smamalig              ⠀⠀⠀⠀⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀   */
/*   Updated: 2025/06/12 20:20:10 by smamalig              ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀   */
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
	if (!pipex->path)
		return (1);
	return (0);
}

int	pipex_init(t_pipex *pipex, int argc, char **argv, char **envp)
{
	pipex->envp = envp;
	pipex->nodes = ft_calloc(argc - 3 - pipex->here_doc, sizeof(t_pipex_exec));
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
	i = -1;
	while (pipex->path && pipex->path[++i])
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
	if (fd < 0)
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

	ft_memset(&pipex, 0, sizeof(t_pipex));
	if (argc > 2 && ft_strcmp(argv[1], "here_doc") == 0)
		pipex.here_doc = true;
	if (argc < 5 + pipex.here_doc)
		return (ft_dprintf(2, INCORRECT_USAGE, argv[0]), 1);
	if (pipex_init(&pipex, argc, argv, envp))
		return (pipex_init_failure(argv[0]));
	if (pipex_parse_env(&pipex, envp))
		return (pipex_cleanup(&pipex), pipex_invalid_env(argv[0]));
	if (pipex_parse_arguments(&pipex, argc - pipex.here_doc,
			argv + pipex.here_doc))
		return (pipex_cleanup(&pipex));
	if (pipex_here_doc(argv[2]))
		return (pipex_cleanup(&pipex));
	if (pipex_open_files(&pipex, argc - pipex.here_doc, argv + pipex.here_doc))
		return (pipex_cleanup(&pipex));
	pipex_exec(&pipex);
	pipex_cleanup(&pipex);
	return (0);
}
