/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 09:05:49 by janhan            #+#    #+#             */
/*   Updated: 2024/05/14 17:11:02 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

static void init_ray_result(t_game *game)
{
	game->ray_info->ray_result = ft_calloc(3, sizeof(double));
	print_ray_result_info(game->ray_info->ray_result);
}

static void	init_ray_info(t_game *game)
{
	game->ray_info = (t_ray_dest *)malloc(sizeof(t_ray_dest));
	if (game->ray_info == NULL)
		error_exit("init_ray_info malloc failed");
	game->ray_info->rx = 0;
	game->ray_info->ry = 0;
	game->ray_info->hx = 0;
	game->ray_info->hy = 0;
	game->ray_info->vx = 0;
	game->ray_info->vy = 0;
	game->ray_info->xo = 0;
	game->ray_info->yo = 0;
	game->ray_info->distance_h = 0;
	game->ray_info->distance_v = 0;
	game->ray_info->a_tan = 0;
	game->ray_info->n_tan = 0;
	game->ray_info->mx = 0;
	game->ray_info->my = 0;
	game->ray_info->dof = 0;
	print_ray_info(game->ray_info);
	init_ray_result(game);
}

static void init_mouse(t_game *game)
{
	game->mouse = (t_mouse *)malloc(sizeof(t_mouse));
	if (game->mouse == NULL)
		error_exit("init mouse malloc failed");
	mlx_mouse_get_pos(game->mlx_win,
		&game->mouse->mouse_x, &game->mouse->mouse_y);
	game->mouse->prev_x = game->mouse->mouse_x;
	game->mouse->prev_y = game->mouse->mouse_y;
	print_mouse_info(game->mouse);
}

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	printf("--------------------init_mlx->mlx_init OK--------------------\n");
	game->mlx_win = mlx_new_window(game->mlx, WINDOW_W, WINDOW_H, "Testing");
	printf("--------------------init_mlx->mlx_win_init OK--------------------\n");
	game->minimap_img = make_image(game, game->map_len_w * MINI_MAP_PIXEL, game->map_len_h * MINI_MAP_PIXEL);
	printf("--------------------init_mlx->minimap init OK--------------------\n");
	game->render = make_image(game, WINDOW_W, WINDOW_H);
	printf("--------------------init_mlx->render init OK--------------------\n");
	init_mouse(game);
	printf("--------------------init_mlx->mouse init OK--------------------\n");
	init_ray_info(game);
	printf("---------------init_mlx->ray_info && dest init OK------------------\n");
	game->background = make_image(game, WINDOW_W, WINDOW_H);
	printf("--------------------init_mlx->background init OK--------------------\n");
	/* TEST */
	game->delta_time = 0;
	game->s_time = 0;
}