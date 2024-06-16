/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_npc_sub_bouns.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 17:07:42 by janhan            #+#    #+#             */
/*   Updated: 2024/06/16 17:19:48 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"

int	compare_npc(const void *a, const void *b)
{
	const t_npc	*npc_a = *(const t_npc**)a;
	const t_npc	*npc_b = *(const t_npc**)b;

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

static void	set_npc_info_sub(t_draw_npc *info, t_player *player)
{
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
}

void	set_npc_info(t_draw_npc *info, t_player *player, t_game *game)
{
	info->player_left = player->player_rad - M_PI / 6;
	info->player_right = player->player_rad + M_PI / 6;
	if (info->player_right < 0)
		info->player_right += M_PI * 2;
	if (info->player_left > M_PI * 2)
		info->player_left -= M_PI * 2;
	info->scale = (double)game->npc_texture[info->target->type]
	[info->target->state]
	[info->target->frame]->width / (info->target->distance);
	info->width = game->npc_texture[info->target->type][info->target->state]
	[info->target->frame]->width * info->scale;
	info->height = game->npc_texture[info->target->type][info->target->state]
	[info->target->frame]->height * info->scale;
	info->npc_rad = atan2(info->target->npc_y - player->player_y,
			info->target->npc_x - player->player_x);
	if (info->npc_rad < 0)
		info->npc_rad += M_PI * 2;
	set_npc_info_sub(info, player);
}
