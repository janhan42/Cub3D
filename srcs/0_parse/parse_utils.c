/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:59:28 by janhan            #+#    #+#             */
/*   Updated: 2024/05/27 18:51:39 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\n' || c == '\t'
		|| c == '\v' || c == '\f' || c == '\r')
		return (TRUE);
	return (FALSE);
}

int	is_cub_file(const char *cub_file_path)
{
	int	file_len;

	file_len = ft_strlen(cub_file_path);
	if (ft_strncmp(cub_file_path + file_len - 4, ".cub", 4) == 0)
		return (TRUE);
	else
		return (FALSE);
}

int	is_upper(char c)
{
	if ('A' <= c && c <= 'Z')
		return (TRUE);
	return (FALSE);
}
