/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 09:11:15 by janhan            #+#    #+#             */
/*   Updated: 2024/05/14 11:36:03 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

static int	get_player_position_sub(char **map, t_player *player, int x, int y)
{

	if (map[y][x] == 'E')
	{
		player->player_x = x * PIXEL + 32;
		player->player_y = y * PIXEL + 32;
		player->player_rad = 0;
		return (SUCCESS);
	}
	if (map[y][x] == 'W')
	{
		player->player_x = x * PIXEL + 32;
		player->player_y = y * PIXEL + 32;
		player->player_rad = M_PI;
		return (SUCCESS);
	}
	if (map[y][x] == 'S')
	{
		player->player_x = x * PIXEL + 32;
		player->player_y = y * PIXEL + 32;
		player->player_rad = M_PI + M_PI_2;
		return (SUCCESS);
	}
	return (FAILURE);
}

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
				player->player_x = x * PIXEL + 32;
				player->player_y = y * PIXEL + 32;
				player->player_rad = M_PI_2;
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
	mlx_mouse_hide();
	//mlx_mouse_move(game->mlx_win, WINDOW_W / 2, WINDOW_H / 2); -> game->mode = GAME 일때
	mlx_mouse_get_pos(game->mlx_win, &game->mouse->prev_x, &game->mouse->prev_y);
	print_player_info(game->player);
}
