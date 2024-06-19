/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parse_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 22:20:17 by janhan            #+#    #+#             */
/*   Updated: 2024/06/19 12:48:58 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"

/**
 * @brief
 * wall : 1, empty : 0, object : LRGHVOP, NPC : RTY
 * @param game
 * @param row
 * @param col
 * @param value
 * @return int
 */
static int	check_bonus_symbol(t_game *game, int row, int col, int value)
{
	if (ft_strchr("0RGLT", value) != NULL)
	{
		if (is_space_around_position(game, row, col) == FAILURE)
			error_exit("Empty space next to 0 or object and NPC!");
	}
	if (ft_strchr("LRGHV", value) != NULL)
		game->object_count++;
	if (ft_strchr("T", value) != NULL)
		game->npc_count++;
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
	else if (ft_strchr("0LRGHVT", value) != NULL)
		if (check_bonus_symbol(game, row, col, value) == FAILURE)
			return (FAILURE);
	return (SUCCESS);
}

/**
 * @brief
 * check map condition
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
 * check error case
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
 * check information
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
