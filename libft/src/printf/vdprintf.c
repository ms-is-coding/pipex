/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vdprintf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:45:24 by smamalig          #+#    #+#             */
/*   Updated: 2025/05/26 15:01:15 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_printf.h"
#include <unistd.h>

#define BUFFER_SIZE 1024

int	ft_vdprintf(int fd, const char *fmt, va_list ap)
{
	char	small_buf[BUFFER_SIZE];
	char	*buf;
	int		len;
	va_list	ap_copy;

	va_copy(ap_copy, ap);
	len = ft_vsnprintf(NULL, 0, fmt, ap_copy);
	if (len < 0)
		return (len);
	va_end(ap_copy);
	buf = small_buf;
	if (len >= BUFFER_SIZE)
	{
		buf = malloc(len + 1);
		if (!buf)
			return (-1);
	}
	len = ft_vsnprintf(buf, len + 1, fmt, ap);
	write(fd, buf, len);
	if (buf != small_buf)
		free(buf);
	return (len);
}
