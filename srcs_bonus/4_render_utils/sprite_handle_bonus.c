/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_handle_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 08:21:37 by janhan            #+#    #+#             */
/*   Updated: 2024/05/28 17:25:33 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"

static void	render_weapon_idle(t_game *game,
	t_img *dst_img, t_single_scale *info)
{
	dst_img->width = (int)(game->player->shotgun[0]->width * info->scale);
	dst_img->height = (int)(game->player->shotgun[0]->height * info->scale);
	dst_img->img = mlx_new_image(game->mlx, dst_img->width, dst_img->height);
	dst_img->addr = mlx_get_data_addr(dst_img->img,
			&dst_img->bit_per_pixel, &dst_img->line_length, &dst_img->endian);
	info->x = WINDOW_W / 2 - (dst_img->width / 2);
	info->y = WINDOW_H - dst_img->height;
	scale_texture(game->player->shotgun[0], dst_img, info->scale);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		dst_img->img,
		info->x, info->y);
}

void	player_frame_update(t_game *game)
{
	if (game->player->shot == TRUE)
	{
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
		if (game->player->shot_frame == 5)
		{
			game->player->shot_frame = 0;
			game->player->shot = FALSE;
		}
	}
}

static void	render_weapon_sprite(t_game *game,
	t_img *dst_img, t_single_scale *info)
{
	dst_img->width = (int)(game->player
			->shotgun[game->player->shot_frame]->width * info->scale);
	dst_img->height = (int)(game->player
			->shotgun[game->player->shot_frame]->height * info->scale);
	dst_img->img = mlx_new_image(game->mlx, dst_img->width, dst_img->height);
	dst_img->addr = mlx_get_data_addr(dst_img->img,
			&dst_img->bit_per_pixel, &dst_img->line_length, &dst_img->endian);
	info->x = WINDOW_W / 2 - (dst_img->width / 2);
	info->y = WINDOW_H - dst_img->height;
	scale_texture(game->player->shotgun[game->player->shot_frame],
		dst_img, info->scale);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		dst_img->img, info->x, info->y);
}

int	render_weapon(t_game *game)
{
	t_img			dst_img;
	t_single_scale	info;

	info.scale = 0.5;
	if (game->player->shot == FALSE)
	{
		render_weapon_idle(game, &dst_img, &info);
		return (0);
	}
	else
	{
		player_frame_update(game);
		render_weapon_sprite(game, &dst_img, &info);
	}
	return (0);
}
