/* ************************************************************************** */
/*                                                                            */
/*                                                         ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀   */
/*   error.c                                               ⠀⠀⠀⠀⢀⣴⣿⠟⠁ ⣿⠟⢹⣿⣿⠀   */
/*                                                         ⠀⠀⢀⣴⣿⠟⠁⠀⠀⠀⠁⢀⣼⣿⠟⠀   */
/*   By: smamalig <smamalig@student.42.fr>                 ⠀⣴⣿⣟⣁⣀⣀⣀⡀⠀⣴⣿⡟⠁⢀⠀   */
/*                                                         ⠀⠿⠿⠿⠿⠿⣿⣿⡇⠀⣿⣿⣇⣴⣿⠀   */
/*   Created: 2025/06/06 22:15:52 by smamalig              ⠀⠀⠀⠀⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀   */
/*   Updated: 2025/06/08 18:24:03 by smamalig              ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

int	pipex_invalid_env(char *name)
{
	ft_dprintf(2, "%s: Error: Missing PATH variable\n", name);
	return (1);
}

int	pipex_init_failure(char *name)
{
	ft_dprintf(2, "%s: Error: Could not initialize\n", name);
	return (1);
}

int	pipex_argument_error(t_pipex *pipex, char *arg)
{
	ft_dprintf(2, "%s: %s: command not found\n", pipex->name, arg);
	return (1);
}

int	pipex_perror(t_pipex *pipex, char *file)
{
	ft_dprintf(2, "%s: %s: %m\n", pipex->name, file);
	return (1);
}
