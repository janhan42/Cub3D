/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:01:52 by janhan            #+#    #+#             */
/*   Updated: 2024/05/28 17:24:37 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"

/*
 * if W: 0 0 ?
 * 	x + cos : 1 0 1 -> 5
 * 	y + sin : 1 1 1 -> 6
 *
 * 	if s: 0 1 ?
 * 	x - cos : 0 0 1 -> 1
 * 	y - sin	: 0 1 0 -> 2
 *
 * 	if a: 1 0 ?
 * 	x + sin : 1 1 1 -> 7
 * 	y - cos : 0 0 0 -> 0
 *
 * 	if d: 1 1 ?
 * 	x - sin : 0 1 1 -> 3
 * 	y + cos : 1 0 0 -> 4
 *
 *
 * 	state : 3bit	_ _ _
 * 	첫비트 1, 0 각각 플러스 마이너스
 * 	2번비트 1, 0 각각 sin cos
 * 	마지막 비트 1, 0 각각 x y
 */
double	wall_collision(t_game *game, int state)
{
	double	offset;
	int		sign;

	offset = 3 * (sin(game->player->player_rad) * ((state & 2) == 2)
			+ cos(game->player->player_rad) * ((state & 2) == 0));
	sign = 1 * ((state & 4) == 4) - 1 * ((state & 4) == 0);
	if (state & 1)
	{
		if (game->map[(int)game->player->player_y >> 6]
			[(int)(game->player->player_x + offset * sign * 10) >> 6] == '1')
			return (0);
		else
			return (offset * sign);
	}
	else
	{
		if (game->map[(int)(game->player->player_y + offset * sign * 10) >> 6]
			[(int)game->player->player_x >> 6] == '1')
			return (0);
		else
			return (offset * sign);
	}
}

void	player_movement(t_game *game)
{
	if (game->player->move_w)
	{
		game->player->player_x += wall_collision(game, 5);
		game->player->player_y += wall_collision(game, 4 + 2 + 0);
	}
	if (game->player->move_s)
	{
		game->player->player_x += wall_collision(game, 0 + 0 + 1);
		game->player->player_y += wall_collision(game, 0 + 2 + 0);
	}
	if (game->player->move_a)
	{
		game->player->player_x += wall_collision(game, 4 + 2 + 1);
		game->player->player_y += wall_collision(game, 0 + 0 + 0);
	}
	if (game->player->move_d)
	{
		game->player->player_x += wall_collision(game, 0 + 2 + 1);
		game->player->player_y += wall_collision(game, 4 + 0 + 0);
	}
	game->frame++;
}
