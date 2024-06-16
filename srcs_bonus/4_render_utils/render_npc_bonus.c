/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_npc_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 05:55:36 by janhan            #+#    #+#             */
/*   Updated: 2024/06/16 17:19:41 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"

void	draw_npc_core_sub(t_draw_npc *info, t_game *game)
{
	while (info->start_y < info->dest_y)
	{
		info->color = color_spoid((int)info->step_x,
				(int)info->step_y,
				game->npc_texture[info->target->type]
			[info->target->state][info->target->frame]);
		info->step_y += (double)game->npc_texture
		[info->target->type]
		[info->target->state]
		[info->target->frame]->height / (2 * info->height);
		if ((info->color & 0xFF000000) != 0xFF000000)
			put_pixel_on_img(game->render,
				info->render_x,
				info->start_y,
				info->color);
		info->start_y++;
	}
}

void	draw_npc_core(t_draw_npc *info, t_player *player, t_game *game)
{
	info->step_x = 0;
	while (info->render_x < info->npc_end_x && info->render_x < WINDOW_W)
	{
		info->step_y = 0;
		if (0 < info->render_x
			&& game->w_dist[info->render_x] > info->target->distance)
		{
			info->start_y = WINDOW_H / 2 - info->height
				+ player->player_fov_off_y + info->height;
			info->dest_y = WINDOW_H / 2 + info->height
				+ player->player_fov_off_y + info->height;
			if (info->dest_y > WINDOW_H)
				info->dest_y = WINDOW_H;
			draw_npc_core_sub(info, game);
		}
		info->render_x++;
		info->step_x
			+= (double)game->npc_texture
		[info->target->type]
		[info->target->state]
		[info->target->frame]->width / (2 * info->width);
	}
}

/*
		CACO_DEMON
IDLE		8
WALK		3
ATTACK		5
PAIN		2
DEATH		6
*/
void	draw_npc(t_npc **npcs, int cnt, t_player *player, t_game *game)
{
	t_draw_npc	info;
	int			i;
	int			limiter;

	limiter = 3;
	i = 0;
	while (i < cnt)
	{
		info.target = npcs[i];
		set_npc_info(&info, player, game);
		if (info.target->state != DEATH)
		{
			update_npc(info.target, player, game);
			shot_npc(&info, game, player, &limiter);
		}
		if (((info.player_left < info.npc_rad
					&& info.npc_rad < info.player_right)
				|| (info.player_right > info.player_left))
			&& ((info.player_left < info.npc_rad)
				|| (info.npc_rad < info.player_right)))
			draw_npc_core(&info, player, game);
		frame_npc(&info, game, limiter);
		i++;
	}
}

void	render_npc(t_game *game)
{
	calculate_npc_dist(game->npcs, game->player, game->npc_count);
	qsort(game->npcs, game->npc_count, sizeof(t_npc *), compare_npc);
	draw_npc(game->npcs, game->npc_count, game->player, game);
}
