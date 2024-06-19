/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_door_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 23:00:05 by janhan            #+#    #+#             */
/*   Updated: 2024/06/19 12:53:34 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"

void	draw_door_core_sub(t_draw_door *info, t_game *game)
{
	while (info->start_y < info->dest_y)
	{
		if (0 > info->start_y && info->start_y > WINDOW_H)
			break ;
		info->color
			= color_spoid((int)info->step_x, (int)info->step_y,
				game->object_texture[HORIZONTAL_DOOR]
			[info->target->frame]);
		if ((info->color & 0xFF000000) != 0xFF000000)
			put_pixel_on_img(game->render, info->render_x,
				info->start_y, info->color);
		info->step_y += info->one_step_y;
		info->start_y++;
	}
}

void	draw_door_core(t_draw_door *info, t_player *player, t_game *game)
{
	while (info->render_x < info->door_end && info->render_x < WINDOW_W)
	{
		info->step_y = 0;
		info->start_y = (WINDOW_H / 2.0) - info->current_height
			/ 2 + player->player_fov_off_y;
		if (info->render_x > 0
			&& game->w_dist[info->render_x] > info->target->distance)
		{
			info->dest_y = info->start_y + info->current_height;
			if (info->dest_y > WINDOW_H)
				info->dest_y = WINDOW_H;
			info->one_step_y
				= (double)game->object_texture[HORIZONTAL_DOOR]
			[0]->height / info->current_height;
			draw_door_core_sub(info, game);
		}
		info->render_x++;
		info->current_height += info->h_offset;
		info->step_x += info->one_step_x;
	}
}

void	draw_door(t_object **obj, int cnt, t_player *player, t_game *game)
{
	t_draw_door	info;
	int			i;

	i = 0;
	while (i < cnt)
	{
		info.target = obj[i];
		if (HORIZONTAL_DOOR <= info.target->type
			&& info.target->type <= VERTICAL_DOOR && info.target->distance > 20)
		{
			set_door_info(&info, player);
			info.step_x = 0;
			info.one_step_x
				= (double)game->object_texture[HORIZONTAL_DOOR][0]->width
				/ info.width;
			draw_door_core(&info, player, game);
		}
		i++;
	}
}
