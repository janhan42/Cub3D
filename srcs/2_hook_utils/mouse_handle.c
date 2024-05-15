/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 07:23:35 by janhan            #+#    #+#             */
/*   Updated: 2024/05/15 15:09:00 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	mouse_handle(int button, int x, int y, t_game *game)
{
	printf("mouse x : [%d] mouse y : [%d]\n", x , y);
	game->mouse->mouse_x = x;
	game->mouse->mouse_x = y;
	if (button == 1 && game->player->shot == FALSE && game->mode == GAME)
	{
		game->player->shot = TRUE;
		game->player->shot_sound = TRUE;
		game->player->shot_time = 0;
		game->player->shot_frame = 0;
	}
	if (button == 1 && x > 0 && y > 0 && game->mode == INTRO)
	{
		mlx_mouse_hide();
		mlx_mouse_move(game->mlx_win, WINDOW_W / 2, WINDOW_H / 2);
		game->mode = GAME;
	}
	return (0);
}
