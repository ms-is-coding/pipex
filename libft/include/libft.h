/* ************************************************************************** */
/*                                                                            */
/*                                                         ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀   */
/*   libft.h                                               ⠀⠀⠀⠀⢀⣴⣿⠟⠁ ⣿⠟⢹⣿⣿⠀   */
/*                                                         ⠀⠀⢀⣴⣿⠟⠁⠀⠀⠀⠁⢀⣼⣿⠟⠀   */
/*   By: smamalig <smamalig@student.42.fr>                 ⠀⣴⣿⣟⣁⣀⣀⣀⡀⠀⣴⣿⡟⠁⢀⠀   */
/*                                                         ⠀⠿⠿⠿⠿⠿⣿⣿⡇⠀⣿⣿⣇⣴⣿⠀   */
/*   Created: 2025/02/06 23:32:58 by smamalig              ⠀⠀⠀⠀⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀   */
/*   Updated: 2025/06/08 15:54:49 by smamalig              ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <stdarg.h>
# include <time.h>
# include <unistd.h>

// Enjoy this very thread-safe printf :)

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
void	*ft_malloc(size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_mempcpy(void *dst, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
char	*ft_stpcpy(char *dst, const char *src);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strdup(const char *s);
char	**ft_split(const char *s, char delim);

#endif
