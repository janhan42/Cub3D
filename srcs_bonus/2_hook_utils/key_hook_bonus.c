/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:05:34 by janhan            #+#    #+#             */
/*   Updated: 2024/06/17 13:36:59 by sangshin         ###   ########.fr       */
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

void	door_open(t_game *game)
{
	int			i;
	t_object	*one;

	i = 0;
	while (i < game->object_count)
	{
		one = game->objects[i];
		if (one->type >= HORIZONTAL_DOOR && one->distance < 100)
		{
			if (one->type == HORIZONTAL_DOOR && one->state == CLOSE)
				one->state = OPEN;
			else if (one->type == VERTICAL_DOOR && one->state == CLOSE)
				one->state = OPEN;
			else if (one->type == HORIZONTAL_DOOR && one->state == OPEN)
				one->state = CLOSE;
			else if (one->type == VERTICAL_DOOR && one->state == OPEN)
				one->state = CLOSE;
		}
		i++;
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
	if (keycode == KEY_M && (game->map_len_w > 11 && game->map_len_h > 11))
	{
		if (game->full_map == FALSE)
			game->full_map = MAP_SIZE_UP;
		else if (game->full_map == TRUE)
			game->full_map = MAP_SIZE_DOWN;
	}
	if (keycode == KEY_E)
		door_open(game);
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
