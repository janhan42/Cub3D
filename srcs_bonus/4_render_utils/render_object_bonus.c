/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_object_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 23:43:33 by janhan            #+#    #+#             */
/*   Updated: 2024/06/07 08:30:15 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"

static void	draw_obj_core_sub(t_draw_obj *info, t_game *game)
{
	while (info->start_y < info->dest_y)
	{
		info->color = color_spoid((int)info->step_x,
				(int)info->step_y,
				game->object_texture[info->target->type]
			[info->target->frame]);
		info->step_y += (double)game->object_texture
		[info->target->type]
		[info->target->frame]->height / (2 * info->height);
		if ((info->color & 0xFF000000) != 0xFF000000)
			put_pixel_on_img(game->render,
				info->render_x,
				info->start_y,
				info->color);
		info->start_y++;
	}
}

static void	draw_obj_core(t_draw_obj *info, t_player *player, t_game *game)
{
	info->step_x = 0;
	while (info->render_x < info->object_end_x && info->render_x < WINDOW_W)
	{
		info->step_y = 0;
		if (0 < info->render_x
			&& game->w_dist[info->render_x] > info->target->distance)
		{
			game->w_dist[info->render_x] = info->target->distance;
			info->start_y = WINDOW_H / 2 - info->height
				+ player->player_fov_off_y + info->height;
			info->dest_y = WINDOW_H / 2 + info->height
				+ player->player_fov_off_y + info->height;
			if (info->dest_y > WINDOW_H)
				info->dest_y = WINDOW_H;
			draw_obj_core_sub(info, game);
		}
		info->render_x++;
		info->step_x += (double)game->object_texture
		[info->target->type]
		[info->target->frame]->width / (2 * info->width);
	}
}

static void	draw_obj(t_object **obj, int cnt, t_player *player, t_game *game)
{
	int				i;
	t_draw_obj		info;

	i = 0;
	while (i < cnt)
	{
		info.target = obj[i];
		if (GREEN_LIGHT <= info.target->type
			&& info.target->type <= NOMAL_LIGHT)
		{
			set_obj_info(&info, player, game);
			if (info.target->distance > 30
				&& (((info.player_left < info.object_rad
							&& info.object_rad < info.player_right)
						|| (info.player_right > info.player_left))
					&& ((info.player_left < info.object_rad)
						|| (info.object_rad < info.player_right))))
				draw_obj_core(&info, player, game);
		}
		i++;
	}
}

void	render_object(t_game *game)
{
	calculate_obj_dist(game->objects, game->player, game->object_count);
	qsort(game->objects, game->object_count, sizeof(t_object *), compare);
	draw_obj(game->objects, game->object_count, game->player, game);
	render_npc(game);
	draw_door(game->objects, game->object_count, game->player, game);
}
