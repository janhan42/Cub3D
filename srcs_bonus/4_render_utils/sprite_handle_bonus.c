/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_handle_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 08:21:37 by janhan            #+#    #+#             */
/*   Updated: 2024/06/19 12:55:24 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"

static void	render_weapon_idle(t_game *game, t_single_scale *info)
{
	info->x = WINDOW_W / 2 - (game->player->shotgun[0]->width / 2);
	info->y = WINDOW_H - game->player->shotgun[0]->height;
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->player->shotgun[0]->img,
		info->x, info->y);
}

void	player_frame_update(t_game *game)
{
	if (game->player->shot == TRUE)
	{
		game->npc_sound_flag = FALSE;
		if (game->player->shot_frame < 3 && game->player->shot_time >= 100)
		{
			game->player->shot_frame++;
			game->player->shot_time = 0;
		}
		else if (game->player->shot_time >= 300)
		{
			game->player->shot_frame++;
			game->player->shot_time = 0;
		}
		if (game->player->shot_frame == 6)
		{
			game->player->shot_frame = 0;
			game->player->shot = FALSE;
			game->player->npc_hit = FALSE;
		}
	}
}

static void	render_weapon_sprite(t_game *game, t_single_scale *info)
{
	info->x = WINDOW_W / 2 - (game->player->shotgun
		[game->player->shot_frame]->width / 2);
	info->y = WINDOW_H - game->player->shotgun
	[game->player->shot_frame]->height;
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->player->shotgun[game->player->shot_frame]->img, info->x, info->y);
}

int	render_weapon(t_game *game)
{
	t_single_scale	info;

	info.scale = 0.5;
	if (game->player->shot == FALSE)
	{
		render_weapon_idle(game, &info);
		return (0);
	}
	else
	{
		player_frame_update(game);
		render_weapon_sprite(game, &info);
	}
	return (0);
}
