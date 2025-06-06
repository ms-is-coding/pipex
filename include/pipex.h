/* ************************************************************************** */
/*                                                                            */
<<<<<<< HEAD
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:05:04 by smamalig          #+#    #+#             */
/*   Updated: 2025/05/06 16:06:46 by smamalig         ###   ########.fr       */
=======
/*                                                         ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀   */
/*   pipex.h                                               ⠀⠀⠀⠀⢀⣴⣿⠟⠁ ⣿⠟⢹⣿⣿⠀   */
/*                                                         ⠀⠀⢀⣴⣿⠟⠁⠀⠀⠀⠁⢀⣼⣿⠟⠀   */
/*   By: smamalig <smamalig@student.42.fr>                 ⠀⣴⣿⣟⣁⣀⣀⣀⡀⠀⣴⣿⡟⠁⢀⠀   */
/*                                                         ⠀⠿⠿⠿⠿⠿⣿⣿⡇⠀⣿⣿⣇⣴⣿⠀   */
/*   Created: 2025/06/05 17:46:39 by smamalig              ⠀⠀⠀⠀⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀   */
/*   Updated: 2025/06/06 22:18:08 by smamalig              ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀   */
>>>>>>> 8234817 (Initial commit. Parsing and executable finding works)
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

<<<<<<< HEAD
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
=======
typedef struct s_pipex_exec
{
	int		fds[2];
	char	*file;
	char	**argv;
}	t_pipex_exec;

typedef struct s_pipex
{
	int				node_count;
	char			*home;
	char			*name;
	char			**path;
	t_pipex_exec	*nodes;
}	t_pipex;

int	pipex_invalid_env(char *name);
int	pipex_init_failure(char *name);
int	pipex_usage_error(char *name);
int	pipex_argument_error(t_pipex *pipex, char *arg);
int	pipex_read_error(t_pipex *pipex, char *file);

int	pipex_parse_arguments(t_pipex *pipex, int argc, char **argv);
int	pipex_parse_exec(t_pipex *pipex, char *arg);
int	pipex_cleanup(t_pipex *pipex);
int	pipex_tokenize(char *s, char **collector);
>>>>>>> 8234817 (Initial commit. Parsing and executable finding works)

#endif
