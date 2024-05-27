/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 09:05:49 by janhan            #+#    #+#             */
/*   Updated: 2024/05/27 17:03:15 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

static void	init_ray_result(t_game *game)
{
	game->ray_info->ray_result = ft_calloc(3, sizeof(double));
	print_ray_result_info(game->ray_info->ray_result);
}

static void	init_ray_info(t_game *game)
{
	game->ray_info = (t_ray_dest *)ft_calloc(1, sizeof(t_ray_dest));
	if (game->ray_info == NULL)
		error_exit("init_ray_info malloc failed");
	print_ray_info(game->ray_info);
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
	print_mouse_info(game->mouse);
}

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, WINDOW_W,
			WINDOW_H, "cub3d");
	game->minimap_img = make_image(game, game->map_len_w * MINI_MAP_PIXEL,
			game->map_len_h * MINI_MAP_PIXEL);
	game->render = make_image(game, WINDOW_W, WINDOW_H);
	init_mouse(game);
	init_ray_info(game);
	game->background = make_image(game, WINDOW_W, WINDOW_H);
	load_texture(game);
	game->s_time = 0;
	game->mode = INTRO;
	if (game->main_background->img == NULL)
		printf("ERROR");
	print_game_info(game);
	printf("--------------------init_mlx OK--------------------\n");
}
