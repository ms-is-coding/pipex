/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:58:29 by smamalig          #+#    #+#             */
/*   Updated: 2025/04/30 08:32:43 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_printf.h"

int	ft_printf(const char *fmt, ...)
{
	va_list	ap;
	int		len;

	va_start(ap, fmt);
	len = ft_vprintf(fmt, ap);
	va_end(ap);
	return (len);
}
