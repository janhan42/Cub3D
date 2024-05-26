/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:05:34 by janhan            #+#    #+#             */
/*   Updated: 2024/05/27 07:32:19 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	key_hook(int keycode, t_game *game)
{
	// 플레이어 x, y 좌표를 이동, 회전만 시키는 함수

	// print_game_info(game);
	if (keycode == KEY_C)
	{
		if (game->mode == GAME)
		{
			game->mode = INTRO;
			mlx_mouse_move(game->mlx_win, WINDOW_W / 2, WINDOW_H / 2);
			mlx_mouse_show();
		}
		else if (game->mode == INTRO)
		{
			game->mode = GAME;
			mlx_mouse_move(game->mlx_win, WINDOW_W / 2, WINDOW_H / 2);
			mlx_mouse_hide();
		}
	}
	if (keycode == ESC)
		end_program(game);
	if (keycode == KEY_W) // w
		game->player->move_w = TRUE;
	if (keycode == KEY_S) // s
		game->player->move_s = TRUE;
	if (keycode == KEY_A) // a
		game->player->move_a = TRUE;
	if (keycode == KEY_D) // d
		game->player->move_d = TRUE;
	if (game->player->player_x >= game->map_width - 8) // TODO: 이거 wall_collition에 있어야하는거 아닌가 싶음.
		game->player->player_x = game->map_width - 1 - 8;
	if (game->player->player_x <= 8)
		game->player->player_x = 8;
	if (game->player->player_y >= game->map_height - 8)
		game->player->player_y = game->map_height - 1 - 8;
	if (game->player->player_y <= 8)
		game->player->player_y = 8;
	return (0);
}

int	key_hook_release(int keycode, t_game *game)
{
	if (keycode == KEY_W) // w
		game->player->move_w = FALSE;
	if (keycode == KEY_S) // s
		game->player->move_s = FALSE;
	if (keycode == KEY_A) // a
		game->player->move_a = FALSE;
	if (keycode == KEY_D) // d
		game->player->move_d = FALSE;
	return (0);
}
