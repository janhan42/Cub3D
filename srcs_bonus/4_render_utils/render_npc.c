/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_npc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 05:55:36 by janhan            #+#    #+#             */
/*   Updated: 2024/06/06 06:31:10 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"

int	compare_npc(const void *a, const void *b)
{
	const t_npc	*npc_a = *(const t_npc**)a;
	const t_npc *npc_b = *(const t_npc**)b;

	if (npc_a->distance > npc_b->distance)
		return (-1);
	else if (npc_a->distance < npc_b->distance)
		return (1);
	else
		return (0);
}

void	calculate_npc_dist(t_npc **npc, t_player *player, int cnt)
{
	const int	px = player->player_x;
	const int	py = player->player_y;
	t_npc		*target;
	int			i;

	i = 0;
	while (i < cnt)
	{
		target = npc[i];
		target->distance = dist(px, py, target->npc_x, target->npc_y);
		i++;
	}
}

void	set_npc_info(t_draw_npc *info, t_player *player, t_game *game)
{
	info->player_left = player->player_rad - M_PI / 6;
	info->player_right = player->player_rad + M_PI / 6;
	if (info->player_left < 0)
		info->player_left += M_PI * 2;
	if (info->player_right > M_PI * 2)
		info->player_right -= M_PI * 2;
	info->scale = (double)game->npc_texture[info->target->type][info->target->state][info->target->frame]->width / (info->target->distance * 2);
	info->width = game->npc_texture[info->target->type][info->target->state][info->target->frame]->width * info->scale;
	info->height = game->npc_texture[info->target->type][info->target->state][info->target->frame]->height * info->scale;
	info->npc_rad = atan2(info->target->npc_y - player->player_y, info->target->npc_x - player->player_x);
	if (info->npc_rad < 0)
		info->npc_rad += M_PI * 2;
	info->angle_diff = info->npc_rad - player->player_rad;
	while (info->angle_diff < M_PI)
		info->angle_diff += M_PI * 2;
	while (info->angle_diff > M_PI)
		info->angle_diff -= M_PI * 2;
	info->screen_x = (int)(info->angle_diff + M_PI / 6) * (WINDOW_W / (M_PI / 3));
	info->npc_start_x = info->screen_x - info->width;
	info->npc_end_x = info->screen_x + info->width;
	info->render_x = info->npc_start_x;
}
void	draw_npc_core_sub(t_draw_npc *info, t_game *game)
{
	while (info->start_y < info->dest_y)
	{
		info->color = color_spoid((int)info->step_x, (int)info->step_y, game->npc_texture[info->target->type][info->target->state][info->target->frame]);
		info->step_y += (double)game->npc_texture[info->target->type][info->target->state][info->target->frame]->height / ( 2 * info->height);
		if ((info->color & 0xFF000000) != 0xFF000000)
			put_pixel_on_img(game->render, info->render_x, info->start_y, info->color);
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

void	draw_npc(t_npc **npcs, int cnt, t_player *player, t_game *game)
{
	t_draw_npc	info;
	int			i;

	i = 0;
	while (i < cnt)
	{
		info.target = npcs[i];
		set_npc_info(&info, player, game);
		if	(((info.player_left < info.npc_rad && info.npc_rad < info.player_right)
						|| (info.player_right > info.player_left))
					&& ((info.player_left < info.npc_rad) || (info.npc_rad < info.player_right)))
			draw_npc_core(&info, player, game);

	}
}

void	render_npc(t_game *game)
{
	calculate_npc_dist(game->npcs, game->player, game->npc_count);
	qsort(game->npcs, game->npc_count, sizeof(t_npc *), compare_npc);
	draw_npc(game->npcs, game->npc_count, game->player, game);
}
