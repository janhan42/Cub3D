/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 22:20:17 by janhan            #+#    #+#             */
/*   Updated: 2024/05/28 17:41:50 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_mand/header_mand.h"

static int	check_bonus_symbol(t_game *game, int row, int col, int value)
{
	if (ft_strchr("0", value) != NULL)
	{
		if (is_space_around_position(game, row, col) == FAILURE)
			error_exit("Empty space next to 0!");
	}
	return (SUCCESS);
}

static int	check_symbol2(t_game *game, int row, int col)
{
	char	value;

	value = game->parse.map[row][col];
	if (ft_strchr("NSEW", value) != NULL)
	{
		if (game->parse.is_d == TRUE)
			error_exit("must have one to NSEW!");
		if (is_space_around_position(game, row, col) == FAILURE)
			error_exit("Empty space next to NSEW!");
		game->parse.is_d = TRUE;
	}
	else if (ft_strchr("0", value) != NULL)
		if (check_bonus_symbol(game, row, col, value) == FAILURE)
			return (FAILURE);
	return (SUCCESS);
}

/**
 * @brief
 * 맵파일에서의 허용되는 글자 그리고 플레이어 포지션이 두개가 있지 않은지 0의 주변이 빈 공간이 있는지 확인.
 * @param game
 * @return int
 */
static int	check_symbol(t_game *game)
{
	int		row;
	int		col;

	row = -1;
	while (game->parse.map[++row] != NULL)
	{
		col = -1;
		while (game->parse.map[row][++col] != '\0')
		{
			if (check_symbol2(game, row, col) == FAILURE)
				return (FAILURE);
		}
	}
	if (game->parse.is_d != TRUE)
		error_exit("no NSEW!");
	return (SUCCESS);
}

/**
 * @brief
 * row, col의 길이가 있는지, 천장 바닥 색상이 파싱 되었는지, 텍스쳐 중복이 있는지, 파싱안된 텍스쳐가 있는지
 * @param game
 * @return int
 */
static int	check_type(t_game *game)
{
	int	i;

	if (!(game->parse.row) || !(game->parse.col))
		error_exit("check_type map error");
	if ((game->parse.ceiling_color == NO_COLOR)
		|| (game->parse.floor_color == NO_COLOR))
		error_exit("Ceiling and Floor color wasn't parsed!");
	if (check_tex(game) == ERROR)
		error_exit("NO,SO,EA,WE direction must be different each other!");
	i = -1;
	while (++i < TEXTURE_COUNT)
		if ((game->parse.tex[i].tex_path) == NULL)
			error_exit("Some texture weren't parsed!");
	return (SUCCESS);
}

/**
 * @brief
 * 맵 파일에서 받아온 정보가 맞는지 체크
 * @param game
 * @return int
 */
int	check_parse(t_game *game)
{
	if (check_type(game) == FAILURE)
		error_exit("NOT PARSED_TYPE");
	if (check_symbol(game) == FAILURE)
		error_exit("NOT PARSED_MAP");
	return (SUCCESS);
}
