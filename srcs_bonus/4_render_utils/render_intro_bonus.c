/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_intro_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:40:50 by janhan            #+#    #+#             */
/*   Updated: 2024/06/14 07:33:20 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"

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
	const t_img	*logo = game->intro;
	int			x;
	int			y;

	mlx_mouse_get_pos(game->mlx_win, &x, &y);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->main_background->img, 0, 0);
	draw_str(game, x, y);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		logo->img, WINDOW_W / 2 - (logo->width / 2),
		WINDOW_H / 2 - (logo->height));
}
