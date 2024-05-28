/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 22:35:48 by janhan            #+#    #+#             */
/*   Updated: 2024/05/28 17:22:22 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"

int	is_blank_line(char *line)
{
	int	i;

	if (line[0] == '\0')
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
