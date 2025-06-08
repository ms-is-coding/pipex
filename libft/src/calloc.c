/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:52:10 by smamalig          #+#    #+#             */
/*   Updated: 2025/02/13 20:03:24 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <errno.h>

void	*ft_calloc(size_t n, size_t size)
{
	bool	overflow;
	void	*ptr;

	overflow = (size != 0) && (n > SIZE_MAX / size);
	if (overflow)
	{
		errno = EOVERFLOW;
		return (NULL);
	}
	ptr = ft_malloc(n * size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, n * size);
	return (ptr);
}
