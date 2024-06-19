/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 09:11:15 by janhan            #+#    #+#             */
/*   Updated: 2024/06/19 12:37:53 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_mand/header_mand.h"

static int	get_player_position_sub(char **map, t_player *player, int x, int y)
{
	if (map[y][x] == 'E')
	{
		player->player_x = x * PIXEL + (int)(PIXEL / 2);
		player->player_y = y * PIXEL + (int)(PIXEL / 2);
		player->player_rad = 0;
		return (SUCCESS);
	}
	if (map[y][x] == 'W')
	{
		player->player_x = x * PIXEL + (int)(PIXEL / 2);
		player->player_y = y * PIXEL + (int)(PIXEL / 2);
		player->player_rad = M_PI;
		return (SUCCESS);
	}
	if (map[y][x] == 'S')
	{
		player->player_x = x * PIXEL + (int)(PIXEL / 2);
		player->player_y = y * PIXEL + (int)(PIXEL / 2);
		player->player_rad = M_PI_2;
		return (SUCCESS);
	}
	return (FAILURE);
}

/**
 * @brief jang hun han
 * get player position
 * @param map
 * @param player
 */
static void	get_player_position(char **map, t_player *player)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N')
			{
				player->player_x = x * PIXEL + (int)(PIXEL / 2);
				player->player_y = y * PIXEL + (int)(PIXEL / 2);
				player->player_rad = M_PI_2 + M_PI;
				return ;
			}
			if (get_player_position_sub(map, player, x, y) == SUCCESS)
				return ;
			x++;
		}
		y++;
	}
}

void	init_player(t_game *game)
{
	game->player = (t_player *)malloc(sizeof(t_player));
	if (game->player == NULL)
		error_exit("init_player -> player malloc failed");
	get_player_position(game->map, game->player);
	game->player->move_w = FALSE;
	game->player->move_s = FALSE;
	game->player->move_a = FALSE;
	game->player->move_d = FALSE;
}
