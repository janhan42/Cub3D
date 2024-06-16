/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_npc_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 05:55:36 by janhan            #+#    #+#             */
/*   Updated: 2024/06/16 09:20:01 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"
#include <stdio.h>

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
	if (info->player_right < 0)
		info->player_right += M_PI * 2;
	if (info->player_left > M_PI * 2)
		info->player_left -= M_PI * 2;
	info->scale = (double)game->npc_texture[info->target->type][info->target->state]
	[info->target->frame]->width / (info->target->distance);
	info->width = game->npc_texture[info->target->type][info->target->state]
	[info->target->frame]->width * info->scale;
	info->height = game->npc_texture[info->target->type][info->target->state]
	[info->target->frame]->height * info->scale;
	info->npc_rad = atan2(info->target->npc_y - player->player_y,
			info->target->npc_x - player->player_x);
	if (info->npc_rad < 0)
		info->npc_rad += M_PI * 2;
	info->angle_diff = info->npc_rad - player->player_rad;
	while (info->angle_diff < M_PI)
		info->angle_diff += 2 * M_PI;
	while (info->angle_diff > M_PI)
		info->angle_diff -= 2 * M_PI;
	info->screen_x = (int)((info->angle_diff + M_PI / 6)
			* (WINDOW_W / (M_PI / 3)));
	info->npc_start_x = info->screen_x - info->width;
	info->npc_end_x = info->screen_x + info->width;
	info->render_x = info->npc_start_x;
	//printf("-----------------------------------------------\n");
	//printf("player_left [%f]\n", info->player_left);
	//printf("player_right [%f]\n", info->player_right);
	//printf("scale [%f]\n", info->scale);
	//printf("width [%d]\n", info->width);
	//printf("height [%d]\n", info->height);
	//printf("npc_rad [%f]\n", info->npc_rad);
	//printf("angle_diff [%f]\n", info->angle_diff);
	//printf("screen_x [%d]\n", info->screen_x);
	//printf("npc_start_x [%d]\n", info->npc_start_x);
	//printf("npc_end_x [%d]\n", info->npc_end_x);
	//printf("render_x [%d]\n", info->render_x);
	//printf("-----------------------------------------------\n");
}

void	draw_npc_core_sub(t_draw_npc *info, t_game *game)
{
	while (info->start_y < info->dest_y)
	{
		info->color = color_spoid((int)info->step_x,
				(int)info->step_y,
				game->npc_texture[info->target->type][info->target->state][info->target->frame]);
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

void	update_npc(t_npc *npc, t_player *player, t_game *game)
{
	int	ray_flag;

	ray_flag = npc_ray(player, npc, game); // player가 npc시야에 있는지
	if (ray_flag == TRUE) // 시야에 있을때
	{
		if (npc->state != PAIN) // PAIN이 우선 순위
		{
			if (npc->distance < 150 && npc->state != ATTACK) // 플레이어와의 거리가 150 이하이고 공격중이 아닐때
			{
				npc->state = ATTACK;
				npc->frame = 0;
				npc->frame_max = 5;
			}
			else if (150 <= npc->distance && npc->distance <= 300 && npc->state != WALK) // 플레이어와의 거리가 150이상 300 이하이고 WALK가 아닐때
			{
				npc->state = WALK;
				npc->frame = 0;
				npc->frame_max = 4;
			}
			else if (300 < npc->distance && npc->state != IDLE) // 플레이어와의 거리가 300 이상면 IDLE
			{
				npc->state = IDLE;
				npc->frame = 0;
				npc->frame_max = 7;
			}
			if (npc->state == WALK)
			{
				double	next_x = player->player_x;
				double	next_y = player->player_y;
				double	angle = atan2(next_y + 0.5 - npc->npc_y, next_x + 0.5 - npc->npc_x);
				double	dx = cos(angle) * 1.5;
				double	dy = sin(angle) * 1.5;
				npc->npc_x += dx;
				npc->npc_y += dy;
			}
		}
		if (npc->state == PAIN && npc->frame >= npc->frame_max)
		{
			npc->state = IDLE;
			npc->frame = 0;
			npc->frame_max = 7;
		}
	}

}



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
		if (info.target->state != DEATH)	// 살아있는걸 기본으로.
		{
			update_npc(info.target, player, game);
			if (WINDOW_W / 2 - info.width / 2 < info.screen_x
				&& info.screen_x < WINDOW_W / 2 + info.width / 2 && player->shot == TRUE && info.target->state != PAIN && info.target->state != DEATH && game->player->npc_hit == FALSE)
			{
				info.target->state = PAIN;
				game->player->npc_hit = TRUE;
				game->npc_sound_flag = TRUE;
				info.target->frame = 0;
				info.target->frame_max = 1;
				info.target->frame_time = 0;
				limiter = 6;
				info.target->hp--;
			}
			if (info.target->hp <= 0 && info.target->state != DEATH)
			{
				info.target->state = DEATH;
				game->npc_death_flag = TRUE;
				info.target->frame = 0;
				info.target->frame_max = 5;
			}
		}
		printf("frame : [%d] frame_max [%d] npc_hit [%d]\n", info.target->frame, info.target->frame_max, player->npc_hit);

		if	(((info.player_left < info.npc_rad
				&& info.npc_rad < info.player_right)
						|| (info.player_right > info.player_left))
					&& ((info.player_left < info.npc_rad)
						|| (info.npc_rad < info.player_right)))
			draw_npc_core(&info, player, game);
		if (info.target->frame < info.target->frame_max && info.target->frame_time > limiter)
		{
			info.target->frame++;
			info.target->frame_time = 0;
			if (info.target->state == ATTACK && info.target->frame == 2)
			{
				game->npc_attack_flag = TRUE;
				game->blood_flag = TRUE;
			}
		}
		if (info.target->frame >= info.target->frame_max && info.target->state != PAIN && info.target->state != DEATH)
			info.target->frame = 0;
		info.target->frame_time++;
		i++;
	}
}

void	render_npc(t_game *game)
{
	calculate_npc_dist(game->npcs, game->player, game->npc_count);
	qsort(game->npcs, game->npc_count, sizeof(t_npc *), compare_npc);
	draw_npc(game->npcs, game->npc_count, game->player, game);
}
