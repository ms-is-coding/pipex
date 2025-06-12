/* ************************************************************************** */
/*                                                                            */
/*                                                         ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀   */
/*   main.c                                                ⠀⠀⠀⠀⢀⣴⣿⠟⠁ ⣿⠟⢹⣿⣿⠀   */
/*                                                         ⠀⠀⢀⣴⣿⠟⠁⠀⠀⠀⠁⢀⣼⣿⠟⠀   */
/*   By: smamalig <smamalig@student.42.fr>                 ⠀⣴⣿⣟⣁⣀⣀⣀⡀⠀⣴⣿⡟⠁⢀⠀   */
/*                                                         ⠀⠿⠿⠿⠿⠿⣿⣿⡇⠀⣿⣿⣇⣴⣿⠀   */
/*   Created: 2025/05/26 15:11:05 by smamalig              ⠀⠀⠀⠀⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀   */
/*   Updated: 2025/06/10 19:27:45 by smamalig              ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀   */
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
	pipex->nodes = ft_calloc(argc - pipex->heredoc, sizeof(t_pipex_exec));
	pipex->name = argv[0];
	return (0);
}

int	pipex_env_cleanup(t_pipex *pipex)
{
	int	i;

	i = -1;
	while (pipex->path && pipex->path[++i])
		free(pipex->path[i]);
	free(pipex->path);
	free(pipex->home);
	free(pipex->nodes);
	return (1);
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
	pipex_env_cleanup(pipex);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	ft_dprintf(2, "Starting pipex\n");
	for (int i = 0; argv[i]; i++)
		ft_dprintf(2, "-> [%s]\n", argv[i]);
	ft_memset(&pipex, 0, sizeof(t_pipex));
	if (argc > 1 && ft_strcmp(argv[1], "here_doc") == 0)
	{
		pipex.heredoc = true;
	}
	if (argc < 4 + pipex.heredoc)
		return (ft_dprintf(2, INCORRECT_USAGE, argv[0]), 1);
	if (pipex_init(&pipex, argc, argv, envp))
		return (pipex_init_failure(argv[0]));
	if (pipex_parse_env(&pipex, envp))
		return (pipex_env_cleanup(&pipex), pipex_invalid_env(argv[0]));
	if (pipex_parse_arguments(&pipex, argc - pipex.heredoc, argv + pipex.heredoc))
		return (pipex_cleanup(&pipex));
	if (pipex_open_files(&pipex, argc - pipex.heredoc, argv + pipex.heredoc))
		return (pipex_cleanup(&pipex));
	pipex_exec(&pipex);
	pipex_cleanup(&pipex);
	return (0);
}
