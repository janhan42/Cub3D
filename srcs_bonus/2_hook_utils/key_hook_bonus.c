/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:05:34 by janhan            #+#    #+#             */
/*   Updated: 2024/05/28 21:35:39 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"

void	change_mode(t_game *game)
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

int	key_hook(int keycode, t_game *game)
{
	if (keycode == KEY_C)
		change_mode(game);
	if (keycode == ESC)
		end_program(game);
	if (keycode == KEY_W)
		game->player->move_w = TRUE;
	if (keycode == KEY_S)
		game->player->move_s = TRUE;
	if (keycode == KEY_A)
		game->player->move_a = TRUE;
	if (keycode == KEY_D)
		game->player->move_d = TRUE;
	if (keycode == KEY_M)
	{
		if (game->full_map == FALSE)
			game->full_map = MAP_SIZE_UP;
		else if (game->full_map == TRUE)
			game->full_map = MAP_SIZE_DOWN;
	}
	return (0);
}

int	key_hook_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->player->move_w = FALSE;
	if (keycode == KEY_S)
		game->player->move_s = FALSE;
	if (keycode == KEY_A)
		game->player->move_a = FALSE;
	if (keycode == KEY_D)
		game->player->move_d = FALSE;
	return (0);
}
