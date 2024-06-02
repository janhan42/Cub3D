/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:59:28 by janhan            #+#    #+#             */
/*   Updated: 2024/06/02 13:06:47 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"

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

int	is_space_around_position(t_game *game, int row, int col)
{
	if (row <= 0 || row >= game->parse.row
		|| col <= 0 || col >= game->parse.col)
		return (FAILURE);
	else if (game->parse.map[row][col + 1] == ' '
		|| game->parse.map[row][col + 1] == '\0'
		|| game->parse.map[row][col - 1] == ' ')
		return (FAILURE);
	else if ((int)ft_strlen(game->parse.map[row - 1]) <= col
		|| game->parse.map[row - 1][col] == ' '
		|| game->parse.map[row - 1][col] == '\0')
		return (FAILURE);
	else if ((int)ft_strlen(game->parse.map[row + 1]) <= col
		|| game->parse.map[row + 1][col] == ' '
		|| game->parse.map[row + 1][col] == '\0')
		return (FAILURE);
	return (SUCCESS);
}

/**
 * @brief
 * 현재 멘데토리 기준 "01NESW " 만 유효하게 검사중 보너스는 추가로 검사를 넣을것
 * @param line
 * @return int
 */
int	is_map_valid(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (find_char("01NESW LRGD", line[i]) == FALSE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}
