/* ************************************************************************** */
/*                                                                            */
/*                                                         ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀   */
/*   libft.h                                               ⠀⠀⠀⠀⢀⣴⣿⠟⠁ ⣿⠟⢹⣿⣿⠀   */
/*                                                         ⠀⠀⢀⣴⣿⠟⠁⠀⠀⠀⠁⢀⣼⣿⠟⠀   */
/*   By: smamalig <smamalig@student.42.fr>                 ⠀⣴⣿⣟⣁⣀⣀⣀⡀⠀⣴⣿⡟⠁⢀⠀   */
/*                                                         ⠀⠿⠿⠿⠿⠿⣿⣿⡇⠀⣿⣿⣇⣴⣿⠀   */
/*   Created: 2025/02/06 23:32:58 by smamalig              ⠀⠀⠀⠀⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀   */
/*   Updated: 2025/06/12 20:02:43 by smamalig              ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# define FT_GNL_SUCCESS 0
# define FT_GNL_FAILURE -1
# define FT_GNL_CONTINUE 1

typedef struct s_reader
{
	int				fd;
	char			*end;
	char			*curr;
	struct s_reader	*next;
	char			buf[BUFFER_SIZE];
}	t_reader;

char	*get_next_line(int fd, _Bool force_eof);

int		ft_printf(const char *fmt, ...)
		__attribute__((format (printf, 1, 2)));

int		ft_dprintf(int fd, const char *fmt, ...)
		__attribute__((format (printf, 2, 3)));

int		ft_sprintf(char *dst, const char *fmt, ...)
		__attribute__((format (printf, 2, 3)));

int		ft_snprintf(char *dst, size_t size, const char *fmt, ...)
		__attribute__((format (printf, 3, 4)));

// for internal use, you can also use them if you know what you're doing
// though why, if you can use the above alternatives?

int		ft_vprintf(const char *fmt, va_list ap);
int		ft_vdprintf(int fd, const char *fmt, va_list ap);
int		ft_vsprintf(char *dst, const char *fmt, va_list ap);
int		ft_vsnprintf(char *dst, size_t size, const char *fmt, va_list ap);

// not required as we won't use FILE structs
// int ft_fprintf(FILE *stream, const char *fmt, ...);
// int ft_vfprintf(FILE *stream, const char *fmt, va_list ap);

void	*ft_calloc(size_t n, size_t size);
void	*ft_realloc(void *ptr, size_t old_sz, size_t new_sz);
void	*ft_malloc(size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_mempcpy(void *dst, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
char	*ft_stpcpy(char *dst, const char *src);
size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strdup(const char *s);
char	**ft_split(const char *s, char delim);

#endif
