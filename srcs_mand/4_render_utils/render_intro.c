/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_intro.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:40:50 by janhan            #+#    #+#             */
/*   Updated: 2024/05/28 17:41:50 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_mand/header_mand.h"

static void	draw_str(t_game *game, int x, int y)
{
	if (WINDOW_W / 2 - (game->start_n->width / 2) < x
		&& x < WINDOW_W / 2 + (game->start_n->width / 2)
		&& 600 < y && y < 600 + game->start_n->height)
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			game->start_h->img, WINDOW_W / 2 - (game->start_h->width / 2), 600);
	else
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			game->start_n->img, WINDOW_W / 2 - (game->start_n->width / 2), 600);
	if (WINDOW_W / 2 - (game->exit_game_n->width / 2) < x
		&& x < WINDOW_W / 2 + (game->exit_game_n->width / 2)
		&& 700 < y && y < 700 + game->exit_game_n->height)
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			game->exit_game_h->img,
			WINDOW_W / 2 - (game->exit_game_h->width / 2), 700);
	else
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			game->exit_game_n->img,
			WINDOW_W / 2 - (game->exit_game_n->width / 2), 700);
}

/**
 * @brief
 * game->mode == intro
 * @param game
 */
void	render_intro(t_game *game)
{
	t_img		intro;
	float		scale_factor;
	int			x;
	int			y;

	mlx_mouse_get_pos(game->mlx_win, &x, &y);
	scale_factor = 0.3;
	intro.width = (int)(game->main_menu->width * scale_factor);
	intro.height = (int)(game->main_menu->height * scale_factor);
	intro.img = mlx_new_image(game->mlx, intro.width, intro.height);
	intro.addr = mlx_get_data_addr(intro.img,
			&intro.bit_per_pixel, &intro.line_length, &intro.endian);
	scale_texture(game->main_menu, &intro, scale_factor);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->main_background->img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		intro.img, WINDOW_W / 2 - (intro.width / 2),
		WINDOW_H / 2 - (intro.height));
	draw_str(game, x, y);
}
