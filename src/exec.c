/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 07:53:15 by smamalig          #+#    #+#             */
/*   Updated: 2025/07/22 13:31:14 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static inline void	pipex_close(int fd)
{
	if (fd != -1)
		close(fd);
}

static void	pipex_dup_io(t_pipex *pipex, int i, int prev_fd, int pipefd[2])
{
	if (i == 0)
		dup2(pipex->fd_in, STDIN_FILENO);
	else
	{
		dup2(prev_fd, STDIN_FILENO);
		pipex_close(prev_fd);
	}
	if (i == pipex->node_count - 1)
		dup2(pipex->fd_out, STDOUT_FILENO);
	else
	{
		pipex_close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		pipex_close(pipefd[1]);
	}
	pipex_close(pipex->fd_in);
	pipex_close(pipex->fd_out);
}

static int	pipex_child(t_pipex *pipex, int i, int prev_fd, int pipefd[2])
{
	auto t_pipex_exec * exec = &pipex->nodes[i];
	pipex_dup_io(pipex, i, prev_fd, pipefd);
	if (exec->file)
		execve(exec->file, exec->argv, pipex->envp);
	if (exec->argv[0] && ft_strchr(exec->argv[0], '/'))
	{
		(void)!access(exec->argv[0], X_OK);
		if (errno == EACCES)
			return (ft_dprintf(2, "%s: %s: %m\n", pipex->name, exec->argv[0]),
				_exit(126), 1);
		if (errno == EPERM)
			return (ft_dprintf(2, "%s: %s: %m\n", pipex->name, exec->argv[0]),
				_exit(1), 1);
		ft_dprintf(2, "%s: %s: %m\n", pipex->name, exec->argv[0]);
		_exit(127);
	}
	ft_dprintf(2, "%s: %s: command not found\n", pipex->name, exec->argv[0]);
	pipex_cleanup(pipex);
	_exit(127);
}

static int	pipex_spawn(t_pipex *pipex, int i, int prev_fd)
{
	int		pipefd[2];
	pid_t	pid;

	if (i < pipex->node_count - 1 && pipe(pipefd) < 0)
		return (pipex_pipe_error(pipex->name));
	pid = fork();
	pipex->last_pid = pid;
	if (pid == -1)
		return (pipex_fork_error(pipex->name, pipefd));
	if (pid == 0)
		pipex_child(pipex, i, prev_fd, pipefd);
	if (prev_fd != -1)
		pipex_close(prev_fd);
	if (i < pipex->node_count - 1)
	{
		pipex_close(pipefd[1]);
		return (pipefd[0]);
	}
	return (-1);
}

int	pipex_exec(t_pipex *pipex)
{
	auto int prev_fd = -1;
	auto int i = -1;
	auto int exit_code = 0;
	auto pid_t pid;
	auto int status;
	while (++i < pipex->node_count)
	{
		prev_fd = pipex_spawn(pipex, i, prev_fd);
		if (prev_fd == -1 && i < pipex->node_count - 1)
			return (1);
	}
	i = -1;
	while (1)
	{
		pid = wait(&status);
		if (pid == -1)
			break ;
		if (pid == pipex->last_pid && WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
	}
	pipex_close(pipex->fd_in);
	pipex_close(pipex->fd_out);
	return (exit_code);
}
