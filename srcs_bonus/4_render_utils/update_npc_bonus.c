/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_npc_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 17:12:54 by janhan            #+#    #+#             */
/*   Updated: 2024/06/19 12:55:36 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"

void	frame_npc(t_draw_npc *info, t_game *game, int limiter)
{
	if (info->target->frame < info->target->frame_max
		&& info->target->frame_time > limiter)
	{
		info->target->frame++;
		info->target->frame_time = 0;
		if (info->target->state == ATTACK && info->target->frame == 2)
		{
			game->npc_attack_flag = TRUE;
			game->blood_flag = TRUE;
		}
	}
	if (info->target->frame >= info->target->frame_max
		&& info->target->state != PAIN && info->target->state != DEATH)
		info->target->frame = 0;
	info->target->frame_time++;
}

void	shot_npc(t_draw_npc *info, t_game *game, t_player *player, int *limiter)
{
	if (WINDOW_W / 2 - info->width / 2 < info->screen_x
		&& info->screen_x < WINDOW_W / 2 + info->width / 2
		&& player->shot == TRUE && info->target->state != PAIN
		&& game->player->npc_hit == FALSE)
	{
		info->target->state = PAIN;
		game->player->npc_hit = TRUE;
		game->npc_sound_flag = TRUE;
		info->target->frame = 0;
		info->target->frame_max = 1;
		info->target->frame_time = 0;
		*limiter = 6;
		info->target->hp--;
	}
	if (info->target->hp <= 0)
	{
		info->target->state = DEATH;
		game->npc_death_flag = TRUE;
		info->target->frame = 0;
		info->target->frame_max = 5;
	}
}

static void	npc_state_manager(t_npc *npc)
{
	if (npc->distance < 150 && npc->state != ATTACK)
	{
		npc->state = ATTACK;
		npc->frame = 0;
		npc->frame_max = 5;
	}
	else if (150 <= npc->distance && npc->distance <= 300 && npc->state != WALK)
	{
		npc->state = WALK;
		npc->frame = 0;
		npc->frame_max = 4;
	}
}

static void	npc_movement_manager(t_npc *npc,
t_npc_update *update, t_player *player)
{
	if (npc->state == WALK)
	{
		update->next_x = player->player_x;
		update->next_y = player->player_y;
		update->angle = atan2(update->next_y + 0.5 - npc->npc_y,
				update->next_x + 0.5 - npc->npc_x);
		update->dx = cos(update->angle) * 1.5;
		update->dy = sin(update->angle) * 1.5;
		npc->npc_x += update->dx;
		npc->npc_y += update->dy;
	}
}

void	update_npc(t_npc *npc, t_player *player, t_game *game)
{
	t_npc_update	update;

	update.ray_flag = npc_ray(player, npc, game);
	if (update.ray_flag == TRUE)
	{
		if (npc->state != PAIN)
		{
			npc_state_manager(npc);
			npc_movement_manager(npc, &update, player);
		}
		if (npc->state == PAIN && npc->frame >= npc->frame_max)
		{
			npc->state = IDLE;
			npc->frame = 0;
			npc->frame_max = 7;
		}
	}
	if ((300 < npc->distance && npc->state != IDLE)
		|| (update.ray_flag == FALSE && npc->state != IDLE))
	{
		npc->state = IDLE;
		npc->frame = 0;
		npc->frame_max = 7;
	}
}
