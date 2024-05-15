/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 23:43:33 by janhan            #+#    #+#             */
/*   Updated: 2024/05/16 02:03:43 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	scale_object(t_img *src, t_img *dst, float scale_factor)
{
	t_scale	info;

	info.sacle = 1.0 / scale_factor;
	info.new_y = 0;
	while (info.new_y < dst->height)
	{
		info.new_x = 0;
		while (info.new_x < dst->width)
		{
			info.x = (int)(info.new_x * info.sacle);
			info.y = (int)(info.new_y * info.sacle);
			if (info.x >= src->width || info.y >= src->height)
				continue ;
			info.color = *(int *)(src->addr + (info.y * src->line_length
						+ info.x * (src->bit_per_pixel / 8)));
			*(int *)(dst->addr + (info.new_y * dst->line_length + info.new_x
						* (dst->bit_per_pixel / 8))) = info.color;
			info.new_x++;
		}
		info.new_y++;
	}
}

void	render_sprite_object(t_game *game)
{
	int	i;
	double	sx;
	double	sy;
	double	sz;

	double	cs;
	double	sn;
	double	a;
	double	b;
	i = 0;
	while (i < game->object_count)
	{
		sx = game->objects[i]->object_x - game->player->player_x;
		sx = game->objects[i]->object_y - game->player->player_y;
		sx = game->objects[i]->object_z;
		cs = cos(game->player->player_rad);
		sn = sin(game->player->player_rad);
		a = sy * cs + sx * sn;
		b = sx * cs - sy * sn;
		sx = a;
		sy = b;
		sx = (sx * 108.0/sy) + ((double)WINDOW_W /2);
		sy = (sz * 108.0/sy) + ((double)WINDOW_H / 2);
	}
}
