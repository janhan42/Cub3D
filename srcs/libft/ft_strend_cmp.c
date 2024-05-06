/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strend_cmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 09:04:42 by janhan            #+#    #+#             */
/*   Updated: 2024/01/11 09:07:43 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 뒷부분의 dest의 end 길이가 end와 같으면 Return 1 다르면 return 0*/
int	ft_strend_cmp(char *dest, char *end)
{
	int	dest_len;
	int	end_len;

	dest_len = ft_strlen(dest);
	end_len = ft_strlen(end);
	if (dest_len <= end_len)
		return (0);
	dest += dest_len - end_len;
	while (*dest)
	{
		if (*dest != *end)
			return (0);
		dest++;
		end++;
	}
	return (1);
}
