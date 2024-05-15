/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:42:08 by janhan            #+#    #+#             */
/*   Updated: 2024/05/16 03:36:57 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

static void	player_animation(t_game *game)
{
	//if (game->player->move_w)
	//{
	//	game->player->player_y += (sin(game->player->player_rad));
	//	game->player->player_x += (cos(game->player->player_rad));
	//}
	//if (game->player->move_s)
	//{
	//	game->player->player_x -= (cos(game->player->player_rad));
	//	game->player->player_y -= (sin(game->player->player_rad));
	//}
	//if (game->player->move_a)
	//{
	//	game->player->player_x += (sin(game->player->player_rad));
	//	game->player->player_y -= (cos(game->player->player_rad));
	//}
	//if (game->player->move_d)
	//{
	//	game->player->player_x -= (sin(game->player->player_rad));
	//	game->player->player_y += (cos(game->player->player_rad));
	//}
	if (game->player->move_w)
	{
		// printf("KEY W\n");
		// printf("WALL COL : [%f]\n", wall_collision(game, 5));
		// printf("WALL COL : [%f]\n", wall_collision(game, 4 + 2 + 0));
		game->player->player_x += wall_collision(game, 5);
		game->player->player_y += wall_collision(game, 4 + 2 + 0);
		// printf("game->player_x : [%f]\n", game->player->player_x);
		// printf("game->player_y : [%f]\n", game->player->player_y);
	}
	if (game->player->move_s)
	{
		// printf("KEY S\n");
		// printf("WALL COL : [%f]\n", wall_collision(game, 0 + 0 + 1));
		// printf("WALL COL : [%f]\n", wall_collision(game, 0 + 2 + 0));
		game->player->player_x += wall_collision(game, 0 + 0 + 1);
		game->player->player_y += wall_collision(game, 0 + 2 + 0);
		// printf("game->player_x : [%f]\n", game->player->player_x);
		// printf("game->player_y : [%f]\n", game->player->player_y);
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
}
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
	const double	offset = 2 * (sin(game->player->player_rad) * ((state & 2) == 2)
						 + cos(game->player->player_rad) * ((state & 2) == 0));
	const int	sign = 1 * ((state & 4) == 4) - 1 * ((state & 4) == 0);

	if (state & 1) // x축이
	{
		if (game->map[(int)game->player->player_y >> 6][(int)(game->player->player_x + offset * sign) >> 6] == '1')
			return (0);
		else
			return (offset * sign);
	}
	else // y축
	{
		if (game->map[(int)(game->player->player_y + offset * sign) >> 6][(int)game->player->player_x >> 6] == '1')
			return (0);
		else
			return (offset * sign);
	}
}

void	draw_background(t_game *game)
{
	int	x;
	int	y;
	int	mid;

	y = 0;
	mid = 1080/2 + game->player->player_fov_off_y;
	while (y < WINDOW_H)
	{
		x = 0;
		while (x < WINDOW_W)
		{
			if (y > mid)
				put_pixel_on_img(game->background, x, y, game->floor_color);
			else
				put_pixel_on_img(game->background, x, y, game->ceiling_color);
			x++;
		}
		y++;
	}
}

/**
 * @brief
 * game->mode = menu
 * @param game
 */
void	render_menu(t_game *game)
{
	mlx_clear_window(game->mlx, game->mlx_win);
	mlx_destroy_image(game->mlx, game->render->img);
	free(game->render);
	game->render = make_image(game, WINDOW_W, WINDOW_H);
	/* render 에 이미지 처리 */
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->render->img, 0, 0);
}

/**
 * @brief
 * game->mode == intro
 * @param game
 */
void	render_intro(t_game *game)
{
	t_img intro;
	float		scale_factor;

	scale_factor = 0.3;
	mlx_clear_window(game->mlx, game->mlx_win);
	mlx_destroy_image(game->mlx, game->render->img);
	free(game->render);
	game->render = make_image(game, WINDOW_W, WINDOW_H);
	intro.width = (int)(game->main_menu->width * scale_factor);
	intro.height = (int)(game->main_menu->height * scale_factor);
	intro.img = mlx_new_image(game->mlx, intro.width, intro.height);
	intro.addr = mlx_get_data_addr(intro.img, &intro.bit_per_pixel, &intro.line_length, &intro.endian);
	scale_texture(game->main_menu, &intro,  scale_factor);
	mlx_put_image_to_window(game->mlx, game->mlx_win, intro.img, WINDOW_W / 2 - (intro.width / 2), WINDOW_H / 2 - (intro.height));
	/* render 에 이미지 처리 */
}

/**
 * @brief
 * game->mode = GAME
 * @param game
 */
void	render_game(t_game *game)
{
	int i = 0;

	//mlx_clear_window(game->mlx, game->mlx_win);
	// BackGround
	render_mini_map(game->minimap_img, game->map);
	mlx_destroy_image(game->mlx, game->render->img);
	free(game->render);
	game->render = make_image(game, WINDOW_W, WINDOW_H);
	draw_player(game->minimap_img, game);

	int x = 0;
	int y = 0;
	while (y < WINDOW_H) // TODO: 이거 왜 넣었는지 설명 필요.
	{						// 우리가 그릴 벽 제외하고 투명하게 바꿔주는 부분임
		x = 0;
		while (x < WINDOW_W)
		{
			put_pixel_on_img(game->render, x, y, 0xFFFFFFFF);
			x++;
		}
		y++;
	}
	render_3d(game);
	draw_background(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->background->img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->render->img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->minimap_img->img, 0, 0);
	// Wall
	// PLAYER && NPC
	weapon_sprite_handle(game);
}

void	mouse_update(t_game *game)
{
	t_vec2i	mouse_diff;

	mlx_mouse_get_pos(game->mlx_win, &game->mouse->mouse_x, &game->mouse->mouse_y);
	mouse_diff.x = game->mouse->prev_x - game->mouse->mouse_x;
	mouse_diff.y = game->mouse->prev_y - game->mouse->mouse_y;
	if (mouse_diff.x > 0) // a
		game->player->player_rad -= 0.07;
	if (mouse_diff.x < 0) // d
		game->player->player_rad += 0.07;
	if (mouse_diff.y > 0)
		game->player->player_fov_off_y += mouse_diff.y * 3;
	if (mouse_diff.y < 0)
		game->player->player_fov_off_y += mouse_diff.y * 3;
	game->mouse->prev_x = WINDOW_W / 2;
	game->mouse->prev_y = WINDOW_H / 2;
	if (game->player->player_rad > M_PI * 2)
		game->player->player_rad -= 2 * M_PI;
	else if (game->player->player_rad < 0)
		game->player->player_rad += 2 * M_PI;
	if (game->mouse->mouse_x > 0  && game->mouse->mouse_y > 0)
		mlx_mouse_move(game->mlx_win, WINDOW_W / 2, WINDOW_H / 2);
}

int	update(t_game *game)
{
	game->delta_time = get_delta_time(&game->current_time);
	double fps;
	static int flag;

	fps = 1.0 / game->delta_time;
	game->s_time++;
	if (game->player->shot == TRUE)
		game->player->shot_time++;
	if (game->s_time >= 100)
	{
		if (game->mode == GAME)
		{
			flag = 0;
			mouse_update(game);
			player_animation(game);
			render_game(game);
		}
		if (game->mode == MENU)
		{
			flag = 0;
			render_menu(game);
		}
		if (game->mode == INTRO && flag == 0)
		{
			render_intro(game);
			flag += 1;
		}
		game->s_time = 0;
	}
	return (0);
}
