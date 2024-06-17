/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:05:34 by janhan            #+#    #+#             */
/*   Updated: 2024/06/17 13:43:51 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_mand/header_mand.h"

int	key_hook(int keycode, t_game *game)
{
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
	if (keycode == ARROW_L)
		game->player->player_rad -= 0.04;
	if (keycode == ARROW_R)
		game->player->player_rad += 0.04;
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
