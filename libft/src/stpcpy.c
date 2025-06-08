/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strpcpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 11:01:32 by smamalig          #+#    #+#             */
/*   Updated: 2025/02/23 11:01:34 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_stpcpy(char *dst, const char *src)
{
	char	*p;

	p = ft_mempcpy(dst, src, ft_strlen(src));
	*p = 0;
	return (p);
}
