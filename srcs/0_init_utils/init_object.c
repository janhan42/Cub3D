/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 23:53:45 by janhan            #+#    #+#             */
/*   Updated: 2024/05/16 00:04:53 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

/**
 * @brief jang hun han
 *	char **map에서
 * x, y로 **map을 탐색하면서
 * 플레이어 포지션에서의 좌표 지정
 * @param map
 * @param player
 */
static void	get_object_position(char **map, t_object *object, int x, int y)
{
	while (map[y])
	{
		while (map[y][x])
		{
			if (map[y][x] == 'G' || map[y][x] == 'R' || map[y][x] == 'L')
			{
				object->object_x = x * PIXEL + (int)(PIXEL / 2);
				object->object_x = y * PIXEL + (int)(PIXEL / 2);
				if (map[y][x] == 'G')
				if (map[y][x] == 'R')
				if (map[y][x] == 'L')
				if (map[y][x] == 'L')
				return ;
			}
			x++;
		}
		x = 0;
		y++;
	}
}

void	init_object(t_game *game)
{
	int	i;
	int	x;
	int y;

	i = 0;
	x = 0;
	y = 0;
	game->objects = (t_object **)malloc(sizeof(t_object *) * game->object_count);
	if (game->objects == NULL)
		error_exit("init_object malloc failed");
	while (i < game->object_count)
		get_object_position(game->map, game->objects[i], x, y);
	game->player->shotgun = (t_img **)malloc(sizeof(t_img *) * 6);
	if(game->player->shotgun == NULL)
		error_exit("init_player shotgun malloc failed");
	init_multi_xpm_img(game, game->player->shotgun, "resources/sprites/weapon/shotgun/", 6);
	print_img_info(game->player->shotgun[0], "shotgun[0]");
	game->player->shot_time = 0;
	game->player->shot_frame = 0;
	game->player->shot = FALSE;
	game->player->shot_sound = FALSE;
	game->player->move_w = FALSE;
	game->player->move_s = FALSE;
	game->player->move_a = FALSE;
	game->player->move_d = FALSE;
	game->player->player_fov_off_y = 0;
	//mlx_mouse_move(game->mlx_win, WINDOW_W / 2, WINDOW_H / 2); -> game->mode = GAME 일때
	print_player_info(game->player);
}
