/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_texture_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:28:13 by janhan            #+#    #+#             */
/*   Updated: 2024/05/28 17:25:27 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"

static void	set_info(t_game *game, t_single_texture *info, t_dest *dest, int t)
{
	info->wall_x = (dest->x + 1) & 63;
	info->wall_y = (dest->y + 1) & 63;
	if (info->wall_x > info->wall_y)
		info->texture_x = info->wall_x * game->texture->width >> 6;
	else
		info->texture_x = info->wall_y * game->texture->width >> 6;
	if (dest->distance < 1)
		dest->distance = 1;
	info->line_h = (WINDOW_H / dest->distance) * 100;
	info->step = 1.0 * game->texture->height / info->line_h;
	info->h_offset = (int)(WINDOW_H / 2) - (info->line_h / 2)
		+ game->player->player_fov_off_y;
	info->step_y = 0;
	info->y = 0;
	info->x = t;
}

static void	render_ceiling(t_game *game, t_single_texture *info)
{
	int	i;

	i = 0;
	while (i < info->h_offset)
	{
		put_pixel_on_img(game->render, info->x, i, game->ceiling_color);
		i++;
	}
}

static void	render_wall(t_game *game, t_single_texture *info, t_img *texture)
{
	while (info->y < info->line_h)
	{
		if (info->y + info->h_offset > WINDOW_H)
			return ;
		while (info->y + info->h_offset < 0)
		{
			info->step_y += info->step;
			info->y++;
		}
		info->color = color_spoid(info->texture_x, (int)info->step_y, texture);
		put_pixel_on_img(game->render, info->x,
			info->y + info->h_offset, info->color);
		info->step_y += info->step;
		info->y++;
	}
}

static void	render_floor(t_game *game, t_single_texture *info)
{
	while (info->y + info->h_offset < WINDOW_H)
	{
		put_pixel_on_img(game->render, info->x,
			info->y + info->h_offset, game->floor_color);
		info->y++;
	}
}

void	render_texture(t_game *game, t_dest *dest, int t)
{
	t_single_texture	info;
	t_img				*texture;

	texture = get_texture(game, dest);
	set_info(game, &info, dest, t);
	render_ceiling(game, &info);
	render_wall(game, &info, texture);
	render_floor(game, &info);
}
