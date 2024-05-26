/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 09:05:49 by janhan            #+#    #+#             */
/*   Updated: 2024/05/27 06:56:18 by janhan           ###   ########.fr       */
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
	game->ray_info = (t_ray_dest *)ft_calloc(1, sizeof(t_ray_dest));
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
	game->mouse->prev_x = WINDOW_W / 2;
	game->mouse->prev_y = WINDOW_H / 2;
	print_mouse_info(game->mouse);
}

static void	load_texture(t_game *game)
{
	t_img	*tmp;

	tmp = ft_calloc(5, sizeof(t_img));
	tmp[EAST].img = mlx_png_file_to_image(game->mlx, "resources/textures/1.png", &tmp[EAST].width, &tmp[EAST].height);
	tmp[EAST].addr = mlx_get_data_addr(tmp[EAST].img, &tmp[EAST].bit_per_pixel, &tmp[EAST].line_length, &tmp[EAST].endian);
	tmp[NORTH].img = mlx_png_file_to_image(game->mlx, "resources/textures/2.png", &tmp[NORTH].width, &tmp[NORTH].height);
	tmp[NORTH].addr = mlx_get_data_addr(tmp[NORTH].img, &tmp[NORTH].bit_per_pixel, &tmp[NORTH].line_length, &tmp[NORTH].endian);
	tmp[WEST].img = mlx_png_file_to_image(game->mlx, "resources/textures/3.png", &tmp[WEST].width, &tmp[WEST].height);
	tmp[WEST].addr = mlx_get_data_addr(tmp[WEST].img, &tmp[WEST].bit_per_pixel, &tmp[WEST].line_length, &tmp[WEST].endian);
	tmp[SOUTH].img = mlx_png_file_to_image(game->mlx, "resources/textures/5.png", &tmp[SOUTH].width, &tmp[SOUTH].height);
	tmp[SOUTH].addr = mlx_get_data_addr(tmp[SOUTH].img, &tmp[SOUTH].bit_per_pixel, &tmp[SOUTH].line_length, &tmp[SOUTH].endian);
	tmp[DOOR].img = mlx_png_file_to_image(game->mlx, "resources/doors/door_close.png", &tmp[DOOR].width, &tmp[DOOR].height);
	tmp[DOOR].addr = mlx_get_data_addr(tmp[DOOR].img, &tmp[DOOR].bit_per_pixel, &tmp[DOOR].line_length, &tmp[DOOR].endian);
	game->texture = tmp;
	printf("--------------------load_texture OK--------------------\n");
}

void	init_game(t_game *game)
{
	game->mlx = mlx_init(); // mlx 포인터 init
	printf("--------------------init_mlx->mlx_init OK--------------------\n");
	game->mlx_win = mlx_new_window(game->mlx, WINDOW_W, WINDOW_H, "Testing"); // mlx_window 포인터
	printf("--------------------init_mlx->mlx_win_init OK--------------------\n");
	game->minimap_img = make_image(game, game->map_len_w * MINI_MAP_PIXEL, game->map_len_h * MINI_MAP_PIXEL); // minimap 그리기용 이미지
	printf("--------------------init_mlx->minimap init OK--------------------\n");
	game->render = make_image(game, WINDOW_W, WINDOW_H); // 3D wall 그리기용 이미지
	printf("--------------------init_mlx->render init OK--------------------\n");
	init_mouse(game); // mouse 구조체 init
	printf("--------------------init_mlx->mouse init OK--------------------\n");
	init_ray_info(game); // ray 케스팅 계산용 구조체 init
	printf("---------------init_mlx->ray_info && dest init OK------------------\n");
	game->background = make_image(game, WINDOW_W, WINDOW_H); // 배경 그리기용 이미지
	printf("--------------------init_mlx->background init OK--------------------\n");
	load_texture(game);

	/* TEST */
	game->delta_time = 0;
	game->s_time = 0;
	game->mode = INTRO;
	game->main_menu = make_image(game, 2000, 2000);
	game->main_menu->img = mlx_xpm_file_to_image(game->mlx, "resources/textures/klipartz.com.xpm", &game->main_menu->width, &game->main_menu->height);
	game->main_menu->addr = mlx_get_data_addr(game->main_menu->img, &game->main_menu->bit_per_pixel, &game->main_menu->line_length, &game->main_menu->endian);
	game->main_background = make_image(game, 1920, 1080);
	game->main_background->img  = mlx_xpm_file_to_image(game->mlx, "resources/textures/main_background.xpm", &game->main_background->width, &game->main_background->height);
	game->main_background->addr = mlx_get_data_addr(game->main_background->img, &game->main_background->bit_per_pixel, &game->main_background->line_length, &game->main_background->endian);
	game->start_n = make_image(game, 145, 71);
	game->start_n->img = mlx_xpm_file_to_image(game->mlx, "resources/textures/Start_n.xpm", &game->start_n->width, &game->start_n->height);
	game->start_n->addr = mlx_get_data_addr(game->start_n->img, &game->start_n->bit_per_pixel, &game->start_n->line_length, &game->start_n->endian);
//
	game->start_h = make_image(game, 154, 75);
	game->start_h->img = mlx_xpm_file_to_image(game->mlx, "resources/textures/Start_h.xpm", &game->start_h->width, &game->start_h->height);
	game->start_h->addr = mlx_get_data_addr(game->start_h->img, &game->start_h->bit_per_pixel, &game->start_h->line_length, &game->start_h->endian);

	game->exit_game_n = make_image(game, 240, 83);
	game->exit_game_n->img = mlx_xpm_file_to_image(game->mlx, "resources/textures/Exit_game_n.xpm", &game->exit_game_n->width, &game->exit_game_n->height);
	game->exit_game_n->addr = mlx_get_data_addr(game->exit_game_n->img, &game->exit_game_n->bit_per_pixel, &game->exit_game_n->line_length, &game->exit_game_n->endian);
//
	game->exit_game_h = make_image(game, 269, 93);
	game->exit_game_h->img = mlx_xpm_file_to_image(game->mlx, "resources/textures/Exit_game_h.xpm", &game->exit_game_h->width, &game->exit_game_h->height);
	game->exit_game_h->addr = mlx_get_data_addr(game->exit_game_h->img, &game->exit_game_h->bit_per_pixel, &game->exit_game_h->line_length, &game->exit_game_h->endian);
	if (game->main_background->img == NULL)
		printf("ERROR");
	print_game_info(game);
	printf("--------------------init_mlx OK--------------------\n");
}
