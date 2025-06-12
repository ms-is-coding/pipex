/* ************************************************************************** */
/*                                                                            */
/*                                                         ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀   */
/*   pipex.h                                               ⠀⠀⠀⠀⢀⣴⣿⠟⠁ ⣿⠟⢹⣿⣿⠀   */
/*                                                         ⠀⠀⢀⣴⣿⠟⠁⠀⠀⠀⠁⢀⣼⣿⠟⠀   */
/*   By: smamalig <smamalig@student.42.fr>                 ⠀⣴⣿⣟⣁⣀⣀⣀⡀⠀⣴⣿⡟⠁⢀⠀   */
/*                                                         ⠀⠿⠿⠿⠿⠿⣿⣿⡇⠀⣿⣿⣇⣴⣿⠀   */
/*   Created: 2025/06/05 17:46:39 by smamalig              ⠀⠀⠀⠀⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀   */
/*   Updated: 2025/06/12 17:06:05 by smamalig              ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define INCORRECT_USAGE "%s: Error: Incorrect usage\n"

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
	_Bool			had_error;
	_Bool			here_doc;
	char			*home;
	char			*name;
	char			**path;
	t_pipex_exec	*nodes;
	char			**envp;
}	t_pipex;

int	pipex_invalid_env(char *name);
int	pipex_init_failure(char *name);
int	pipex_argument_error(t_pipex *pipex, char *arg);
int	pipex_perror(t_pipex *pipex, char *file);

int	pipex_pipe_error(char *name);
int	pipex_fork_error(char *name, int pipefd[2]);

int	pipex_parse_arguments(t_pipex *pipex, int argc, char **argv);
int	pipex_parse_exec(t_pipex *pipex, char *arg, char **name);
int	pipex_cleanup(t_pipex *pipex);
int	pipex_tokenize(char *s, char **collector);
int	pipex_open_files(t_pipex *pipex, int argc, char **argv);

int	pipex_exec(t_pipex *pipex);

#endif
