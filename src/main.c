/* ************************************************************************** */
/*                                                                            */
<<<<<<< HEAD
/*                                                        :::      ::::::::   */
/*   main.c                                                ⠀⠀⠀⠀⢀⣴⣿⠟⠁ ⣿⠟⢹⣿⣿⠀   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:35:57 by smamalig          #+#    #+#             */
/*   Updated: 2025/06/05 07:47:58 by smamalig              ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv, char **envp) {
	(void)argc;
	(void)argv;
	(void)envp;
	return (0);
}

=======
/*                                                         ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀   */
/*   main.c                                                ⠀⠀⠀⠀⢀⣴⣿⠟⠁ ⣿⠟⢹⣿⣿⠀   */
/*                                                         ⠀⠀⢀⣴⣿⠟⠁⠀⠀⠀⠁⢀⣼⣿⠟⠀   */
/*   By: smamalig <smamalig@student.42.fr>                 ⠀⣴⣿⣟⣁⣀⣀⣀⡀⠀⣴⣿⡟⠁⢀⠀   */
/*                                                         ⠀⠿⠿⠿⠿⠿⣿⣿⡇⠀⣿⣿⣇⣴⣿⠀   */
/*   Created: 2025/05/26 15:11:05 by smamalig              ⠀⠀⠀⠀⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀   */
/*   Updated: 2025/06/06 22:20:10 by smamalig              ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
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

int	pipex_init(t_pipex *pipex, int argc, char **argv)
{
	pipex->path = NULL;
	pipex->home = NULL;
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

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc < 4)
		return (pipex_usage_error(argv[0]));
	if (pipex_init(&pipex, argc, argv))
		return (pipex_init_failure(argv[0]));
	if (pipex_parse_env(&pipex, envp))
		return (pipex_invalid_env(argv[0]));
	if (pipex_parse_arguments(&pipex, argc, argv))
		return (pipex_cleanup(&pipex));
	pipex_cleanup(&pipex);
	return (0);
}
>>>>>>> 8234817 (Initial commit. Parsing and executable finding works)
