/* ************************************************************************** */
/*                                                                            */
/*                                                         ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀   */
/*   exec.c                                                ⠀⠀⠀⠀⢀⣴⣿⠟⠁ ⣿⠟⢹⣿⣿⠀   */
/*                                                         ⠀⠀⢀⣴⣿⠟⠁⠀⠀⠀⠁⢀⣼⣿⠟⠀   */
/*   By: smamalig <smamalig@student.42.fr>                 ⠀⣴⣿⣟⣁⣀⣀⣀⡀⠀⣴⣿⡟⠁⢀⠀   */
/*                                                         ⠀⠿⠿⠿⠿⠿⣿⣿⡇⠀⣿⣿⣇⣴⣿⠀   */
/*   Created: 2025/06/07 07:53:15 by smamalig              ⠀⠀⠀⠀⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀   */
/*   Updated: 2025/06/10 19:21:16 by smamalig              ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include <sys/wait.h>
#include <unistd.h>

static void	pipex_dup_io(t_pipex *pipex, int i, int prev_fd, int pipefd[2])
{
	if (i == 0)
	{
		dup2(pipex->fd_in, STDIN_FILENO);
		close(pipex->fd_in);
	}
	else
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (i == pipex->node_count - 1)
	{
		dup2(pipex->fd_out, STDOUT_FILENO);
		close(pipex->fd_out);
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
}

static int	pipex_child(t_pipex *pipex, int i, int prev_fd, int pipefd[2])
{
	pipex_dup_io(pipex, i, prev_fd, pipefd);
	execve(pipex->nodes[i].file, pipex->nodes[i].argv, pipex->envp);
	ft_dprintf(2, "%s: execve failed: %m\n", pipex->name);
	exit(1);
	return (0);
}

static int	pipex_spawn(t_pipex *pipex, int i, int prev_fd)
{
	int		pipefd[2];
	pid_t	pid;

	if (i < pipex->node_count - 1 && pipe(pipefd) < 0)
		return (pipex_pipe_error(pipex->name));
	pid = fork();
	if (pid < 0)
		return (pipex_fork_error(pipex->name, pipefd));
	if (pid == 0)
		pipex_child(pipex, i, prev_fd, pipefd);
	if (prev_fd != -1)
		close(prev_fd);
	if (i < pipex->node_count - 1)
	{
		close(pipefd[1]);
		return (pipefd[0]);
	}
	return (-1);
}

int	pipex_exec(t_pipex *pipex)
{
	int	prev_fd;
	int	i;

	prev_fd = -1;
	i = -1;
	while (++i < pipex->node_count)
	{
		prev_fd = pipex_spawn(pipex, i, prev_fd);
		if (prev_fd == -1 && i < pipex->node_count - 1)
			return (1);
	}
	i = -1;
	while (++i < pipex->node_count)
		wait(NULL);
	close(pipex->fd_in);
	close(pipex->fd_out);
	return (0);
}
