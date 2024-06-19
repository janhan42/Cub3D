/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 22:35:48 by janhan            #+#    #+#             */
/*   Updated: 2024/06/19 12:49:58 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_mand/header_mand.h"

int	is_blank_line(char *line)
{
	int	i;

	if (line[0] == '\0' || (line[0] == '\n' && line[1] == '\0'))
		return (TRUE);
	i = 0;
	while (line[i])
	{
		if (is_space(line[i]) == FALSE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	find_char(const char *value, char c)
{
	while (*value != '\0')
	{
		if (*value == c)
			return (TRUE);
		value++;
	}
	return (FALSE);
}
