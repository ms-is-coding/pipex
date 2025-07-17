/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:17:46 by smamalig          #+#    #+#             */
/*   Updated: 2025/07/09 17:29:58 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_internal.h"

#include <string.h>
#include <errno.h>

static int	__ft_can_print(t_printf_parser *p)
{
	if (p->prec == -1)
		return (1);
	if (p->prec--)
		return (1);
	return (0);
}

void	__ft_printf_str(t_printf_parser *p, const char *s)
{
	if (!s && (p->prec < 0 || p->prec > 5))
	{
		__ft_printf_str(p, "(null)");
		return ;
	}
	else if (!s)
	{
		__ft_printf_str(p, "");
		return ;
	}
	auto int len = __ft_printf_strnlen(s, p->prec);
	auto int i = 0;
	__ft_printf_padding(p, len, PRINTF_START, PRINTF_OTHER);
	while (i < len && __ft_can_print(p))
		__ft_printf_insert(p, s[i++]);
	__ft_printf_padding(p, len, PRINTF_END, PRINTF_OTHER);
}

#ifdef USE_ERRNO

void	__ft_printf_strerror(t_printf_parser *p)
{
	if (p->flags & PRINTF_FLAG_ALTERNATE)
		__ft_printf_str(p, __ft_str_errorname(errno));
	else
		__ft_printf_str(p, strerror(errno));
}

#endif
