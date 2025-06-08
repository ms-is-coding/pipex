/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_signed.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:08:04 by smamalig          #+#    #+#             */
/*   Updated: 2025/05/16 10:48:07 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_internal.h"

static void	__ft_printf_int_internal(t_printf_parser *parser,
	intmax_t n, int iters)
{
	if (!iters)
		return ;
	__ft_printf_int_internal(parser, n / 10, iters - 1);
	__ft_printf_insert(parser, __ft_printf_abs_char(n % 10) + '0');
}

int	__ft_printf_print_len(t_printf_parser *parser, intmax_t n)
{
	const int	len = __ft_printf_int_len(n);

	if (n == 0 && parser->prec == -1)
		return (1);
	if (parser->prec > len)
		return (parser->prec);
	return (len);
}

void	__ft_printf_int(t_printf_parser *parser, intmax_t n)
{
	const int	len = __ft_printf_print_len(parser, n);
	const int	sign = n < 0 || parser->flags & PRINTF_FLAG_SIGN;

	if (parser->prec >= 0)
		parser->flags &= ~PRINTF_FLAG_ZEROPAD;
	__ft_printf_sign(parser, n < 0, PRINTF_START);
	__ft_printf_padding(parser, len + sign, PRINTF_START, PRINTF_NUMERIC);
	__ft_printf_sign(parser, n < 0, PRINTF_END);
	__ft_printf_int_internal(parser, n, len);
	__ft_printf_padding(parser, len + sign, PRINTF_END, PRINTF_NUMERIC);
}
