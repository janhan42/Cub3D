/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_player_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:27:21 by janhan            #+#    #+#             */
/*   Updated: 2024/06/19 12:55:15 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"

static void	draw_circle(t_img *img, int x, int y)
{
	int	r;
	int	i;
	int	j;

	r = MINI_MAP_PIXEL / 4;
	i = -r;
	while (i < r)
	{
		j = -r;
		while (j < r)
		{
			if (i * i + j * j <= r * r)
				put_pixel_on_img(img, x
					/ (int)(PIXEL / MINI_MAP_PIXEL) + j,
					y
					/ (int)(PIXEL / MINI_MAP_PIXEL) + i, 0x00FF0000);
			j++;
		}
		i++;
	}
}

void	render_map_player(t_img *img, t_game *game)
{
	t_2dot	dots;

	draw_circle(img, game->player->player_x, game->player->player_y);
	dots.start_x = game->player->player_x
		/ (int)(PIXEL / MINI_MAP_PIXEL);
	dots.start_y = game->player->player_y
		/ (int)(PIXEL / MINI_MAP_PIXEL);
	dots.dest_x = game->player->player_x
		/ (int)(PIXEL / MINI_MAP_PIXEL) + 20 * cos(game->player->player_rad);
	dots.dest_y = game->player->player_y
		/ (int)(PIXEL / MINI_MAP_PIXEL) + 20 * sin(game->player->player_rad);
	draw_line(img, dots, 0x00FF0000);
}

void	render_map_player_center(t_img *img, t_game *game)
{
	t_2dot	dots;

	draw_circle(img, 352, 352);
	dots.start_x = 352
		/ (int)(PIXEL / MINI_MAP_PIXEL);
	dots.start_y = 352
		/ (int)(PIXEL / MINI_MAP_PIXEL);
	dots.dest_x = 352.0
		/ (int)(PIXEL / MINI_MAP_PIXEL) + 20 * cos(game->player->player_rad);
	dots.dest_y = 352.0
		/ (int)(PIXEL / MINI_MAP_PIXEL) + 20 * sin(game->player->player_rad);
	draw_line(img, dots, 0x00FF0000);
}
