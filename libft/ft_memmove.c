/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 23:49:43 by janhan            #+#    #+#             */
/*   Updated: 2024/05/13 10:48:05 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*temp_dest;
	const unsigned char	*temp_src;

	temp_dest = (unsigned char *)dest;
	temp_src = (const unsigned char *)src;
	if (temp_dest == temp_src || n == 0)
		return (dest);
	if (temp_dest < temp_src || temp_dest >= temp_src + n)
		while (n--)
			*temp_dest++ = *temp_src++;
	else
	{
		temp_dest += n;
		temp_src += n;
		while (n--)
			*(--temp_dest) = *(--temp_src);
	}
	return (dest);
}
