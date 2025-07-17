/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:46:39 by smamalig          #+#    #+#             */
/*   Updated: 2025/07/17 08:50:30 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>

# define USAGE "Usage:\t%s file1 cmd1 cmd2 [cmdn...] file2\n"
# define HEREDOC_USAGE "\t%s here_doc LIMITER cmd1 cmd2 [cmdn...] file2\n"

typedef struct s_pipex_exec
{
	int		fds[2];
	char	*file;
	char	**argv;
}	t_pipex_exec;

typedef struct s_pipex
{
	int				node_count;
	int				fd_in;
	int				fd_out;
	pid_t			last_pid;
	_Bool			here_doc;
	char			*home;
	char			*name;
	char			**path;
	t_pipex_exec	*nodes;
	char			**envp;
}	t_pipex;

int		pipex_invalid_env(char *name);
int		pipex_init_failure(char *name);
int		pipex_perror(t_pipex *pipex, char *file);

int		pipex_pipe_error(char *name);
int		pipex_fork_error(char *name, int pipefd[2]);

char	*pipex_get_bin(t_pipex *pipex, char *arg);
void	pipex_parse_arguments(t_pipex *pipex, int argc, char **argv);
int		pipex_cleanup(t_pipex *pipex);
int		pipex_tokenize(char *s, char **collector);
void	pipex_open_files(t_pipex *pipex, int argc, char **argv);

int		pipex_exec(t_pipex *pipex);

#endif
