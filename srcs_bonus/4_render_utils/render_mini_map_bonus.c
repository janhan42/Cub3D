/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mini_map_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:26:52 by janhan            #+#    #+#             */
/*   Updated: 2024/06/19 12:53:55 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"

static void	full_map_update_sub(t_game *game)
{
	if (game->full_map == MAP_SIZE_UP)
	{
		if (game->full_map_x <= game->map_len_w - 1 - MINI_MAP_RADIUS * 2)
			game->full_map_x++;
		if (game->full_map_y <= game->map_len_h - 1 - MINI_MAP_RADIUS * 2)
			game->full_map_y++;
		game->minimap_img = make_image(game, ((MINI_MAP_RADIUS * 2)
					+ game->full_map_x) * MINI_MAP_PIXEL,
				((MINI_MAP_RADIUS * 2) + game->full_map_y) * MINI_MAP_PIXEL);
		if (game->full_map_x == game->map_len_w - MINI_MAP_RADIUS * 2)
			game->full_map = TRUE;
	}
	if (game->full_map == MAP_SIZE_DOWN)
	{
		if (game->full_map_x > 0)
			game->full_map_x--;
		if (game->full_map_y > 0)
			game->full_map_y--;
		game->minimap_img = make_image(game, ((MINI_MAP_RADIUS * 2 + 1)
					+ game->full_map_x) * MINI_MAP_PIXEL,
				((MINI_MAP_RADIUS * 2 + 1)
					+ game->full_map_y) * MINI_MAP_PIXEL);
		if (game->full_map_x == 0)
			game->full_map = FALSE;
	}
}

static void	full_map_update(t_game *game)
{
	if (game->full_map == FALSE)
		game->minimap_img = make_image(game,
				((MINI_MAP_RADIUS * 2 + 1)
					+ game->full_map_x) * MINI_MAP_PIXEL,
				((MINI_MAP_RADIUS * 2 + 1)
					+ game->full_map_y) * MINI_MAP_PIXEL);
	if (game->full_map == TRUE)
		game->minimap_img = make_image(game,
				((MINI_MAP_RADIUS * 2)
					+ game->full_map_x) * MINI_MAP_PIXEL,
				((MINI_MAP_RADIUS * 2) + game->full_map_y) * MINI_MAP_PIXEL);
	full_map_update_sub(game);
}

static void	set_position_y(t_game *game, t_single_minimap *m, int py)
{
	if (game->full_map == TRUE)
		m->my = 0;
	else if (game->full_map == MAP_SIZE_DOWN)
	{
		m->my = 0;
		if (game->full_map_y + (MINI_MAP_RADIUS) < py)
			m->my += py - (game->full_map_y + MINI_MAP_RADIUS);
	}
	else if (game->full_map == MAP_SIZE_UP)
	{
		m->my = py - (MINI_MAP_RADIUS);
		if (m->my - game->full_map_y >= 0)
			m->my -= game->full_map_y;
		else
			m->my = 0;
	}
	else
		m->my = py - (MINI_MAP_RADIUS);
}

static void	set_position_x(t_game *game, t_single_minimap *m, int px)
{
	if (game->full_map == TRUE)
		m->mx = 0;
	else if (game->full_map == MAP_SIZE_DOWN)
	{
		m->mx = 0;
		if (game->full_map_x + MINI_MAP_RADIUS < px)
			m->mx += px - game->full_map_x - MINI_MAP_RADIUS;
	}
	else if (game->full_map == MAP_SIZE_UP)
	{
		m->mx = px - MINI_MAP_RADIUS;
		if (m->mx - game->full_map_x > 0)
			m->mx -= game->full_map_x;
		else
			m->mx = 0;
	}
	else
		m->mx = px - (MINI_MAP_RADIUS);
}

void	render_mini_map_center(t_game *game)
{
	const int			px = game->player->player_x / PIXEL;
	const int			py = game->player->player_y / PIXEL;
	t_single_minimap	m;

	full_map_update(game);
	set_position_y(game, &m, py);
	m.y = 0;
	while (m.my <= py + MINI_MAP_RADIUS + game->full_map_y
		|| (py < MINI_MAP_RADIUS && m.my <= MINI_MAP_RADIUS
			+ game->full_map_y + MINI_MAP_RADIUS))
	{
		m.x = 0;
		set_position_x(game, &m, px);
		while (m.mx <= px + MINI_MAP_RADIUS + game->full_map_x
			|| (px < MINI_MAP_RADIUS && m.mx <= MINI_MAP_RADIUS
				+ game->full_map_x + MINI_MAP_RADIUS))
		{
			draw_map_squre(game, &m);
			m.x += MINI_MAP_PIXEL;
			m.mx++;
		}
		m.y += MINI_MAP_PIXEL;
		m.my++;
	}
}
