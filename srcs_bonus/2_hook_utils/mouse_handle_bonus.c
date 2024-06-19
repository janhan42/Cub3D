/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handle_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 07:23:35 by janhan            #+#    #+#             */
/*   Updated: 2024/06/19 12:52:13 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"
#include <stdlib.h>

static void	event_in_game(int button, t_game *game)
{
	if (button == 1 && game->player->shot == FALSE)
	{
		game->player->shot = TRUE;
		game->player->shot_sound = TRUE;
		game->player->shot_time = 0;
		game->player->shot_frame = 0;
	}
}

static void	event_in_intro(int button, int x, int y, t_game *game)
{
	if (button == 1 && x > 0 && y > 0)
	{
		if (WINDOW_W / 2 - (game->start_h->width / 2)
			< x && x < WINDOW_W / 2 + (game->start_h->width / 2)
			&& 600 < y && y < 600 + game->start_h->height)
		{
			mlx_mouse_hide();
			mlx_mouse_move(game->mlx_win, WINDOW_W / 2, WINDOW_H / 2);
			game->mode = GAME;
		}
		if (WINDOW_W / 2 - (game->exit_game_h->width / 2)
			< x && x < WINDOW_W / 2 + (game->exit_game_h->width / 2)
			&& 700 < y && y < 700 + game->exit_game_h->height)
			end_program(game);
	}
}

/**
 * @brief
 * save mouse click event and x, y position
 * @param button  button event code
 * @param x mouse x position
 * @param y mouse y position
 * @param game
 * @return int
 */
int	mouse_handle(int button, int x, int y, t_game *game)
{
	game->mouse->x = x;
	game->mouse->y = y;
	if (game->mode == GAME)
		event_in_game(button, game);
	if (game->mode == INTRO)
		event_in_intro(button, x, y, game);
	return (0);
}
