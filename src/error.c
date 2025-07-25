/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 22:15:52 by smamalig          #+#    #+#             */
/*   Updated: 2025/07/17 08:51:47 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

int	pipex_init_failure(char *name)
{
	ft_dprintf(2, "%s: Error: Could not initialize\n", name);
	return (1);
}

int	pipex_perror(t_pipex *pipex, char *file)
{
	ft_dprintf(2, "%s: %s: %m\n", pipex->name, file);
	return (1);
}

int	pipex_pipe_error(char *name)
{
	ft_dprintf(2, "%s: Error: %m\n", name);
	return (-1);
}

int	pipex_fork_error(char *name, int pipefd[2])
{
	ft_dprintf(2, "%s: Error: %m\n", name);
	close(pipefd[0]);
	close(pipefd[1]);
	return (-1);
}
