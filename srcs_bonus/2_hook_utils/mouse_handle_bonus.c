/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handle_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 07:23:35 by janhan            #+#    #+#             */
/*   Updated: 2024/05/28 17:24:08 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"

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
 * 마우스의 클릭 이벤트와 이동좌표를 저장
 * @param button 버튼 이벤트 코드
 * @param x mouse x좌표
 * @param y mouse y좌표
 * @param game
 * @return int
 */
int	mouse_handle(int button, int x, int y, t_game *game)
{
	game->mouse->x = x;
	game->mouse->y = y;
	printf("CLICK!!!!!!!!!!!!");
	if (game->mode == GAME)
		event_in_game(button, game);
	if (game->mode == INTRO)
		event_in_intro(button, x, y, game);
	return (0);
}
