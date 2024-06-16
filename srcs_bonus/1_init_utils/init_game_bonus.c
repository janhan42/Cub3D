/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 09:05:49 by janhan            #+#    #+#             */
/*   Updated: 2024/06/16 17:49:33 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"

static void	init_ray_result(t_game *game)
{
	game->ray_info->ray_result = ft_calloc(3, sizeof(double));
}

static void	init_ray_info(t_game *game)
{
	game->ray_info = (t_ray_dest *)ft_calloc(1, sizeof(t_ray_dest));
	if (game->ray_info == NULL)
		error_exit("init_ray_info malloc failed");
	init_ray_result(game);
}

static void	init_mouse(t_game *game)
{
	game->mouse = (t_mouse *)malloc(sizeof(t_mouse));
	if (game->mouse == NULL)
		error_exit("init mouse malloc failed");
	mlx_mouse_get_pos(game->mlx_win,
		&game->mouse->x, &game->mouse->y);
	game->mouse->prev_x = WINDOW_W / 2;
	game->mouse->prev_y = WINDOW_H / 2;
}

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, WINDOW_W,
			WINDOW_H, "cub3d");
	game->render = make_image(game, WINDOW_W, WINDOW_H);
	init_mouse(game);
	init_ray_info(game);
	load_texture(game);
	game->s_time = 0;
	game->frame = 0;
	game->mode = INTRO;
	game->full_map = FALSE;
	game->full_map_x = 0;
	game->full_map_y = 0;
	game->npc_death_flag = FALSE;
	game->npc_attack_flag = FALSE;
	game->blood_flag = FALSE;
}
