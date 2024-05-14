/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 08:21:37 by janhan            #+#    #+#             */
/*   Updated: 2024/05/14 13:14:38 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	weapon_sprite_handle(t_game *game)
{
	if (game->player->shot == FALSE)
	{
		mlx_put_image_to_window(game->mlx, game->mlx_win, game->player->shotgun[0]->img, 0, 0);
		return (0);
	}
	if (game->player->shot == TRUE)
	{
		if (game->player->shot_frame < 3 && game->player->shot_time >= 400)
		{
			game->player->shot_frame++;
			game->player->shot_time = 0;
		}
		else if (game->player->shot_time >= 700)
		{
			game->player->shot_frame++;
			game->player->shot_time = 0;
		}
		if (game->player->shot_frame == 5)
		{
			game->player->shot_frame = 0;
			game->player->shot = FALSE;
		}
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->player->shotgun[game->player->shot_frame]->img, 0, 0);
	return (0);
}

