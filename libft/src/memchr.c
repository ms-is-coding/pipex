/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:15:35 by smamalig          #+#    #+#             */
/*   Updated: 2025/07/09 17:42:59 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*s_ = s;

	if (!s)
		return (NULL);
	while (n--)
	{
		if (*(unsigned char *)s_ == (unsigned char)c)
			return ((void *)s_);
		s_++;
	}
	return (NULL);
}
