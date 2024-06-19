/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_object_sub_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:05:54 by janhan            #+#    #+#             */
/*   Updated: 2024/06/19 12:54:39 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"

/**
 * @brief
 * compare for qsort
 * @param a
 * @param b
 * @return int
 */
int	compare(const void *a, const void *b)
{
	const t_object	*obj_a = *(const t_object **)a;
	const t_object	*obj_b = *(const t_object **)b;

	if (obj_a->distance > obj_b->distance)
		return (-1);
	else if (obj_a->distance < obj_b->distance)
		return (1);
	else
		return (0);
}

/**
 * @brief
 * @param obj
 * @param player
 * @param cnt
 */
void	calculate_obj_dist(t_object **obj, t_player *player, int cnt)
{
	const int	px = player->player_x;
	const int	py = player->player_y;
	t_object	*one_obj;
	int			i;

	i = 0;
	while (i < cnt)
	{
		one_obj = obj[i];
		one_obj->distance = dist(px, py, one_obj->object_x, one_obj->object_y);
		i++;
	}
}

static void	set_obj_info_sub(t_draw_obj *info)
{
	info->screen_x = (int)((info->angle_diff + M_PI / 6)
			* (WINDOW_W / (M_PI / 3)));
	info->object_start_x = info->screen_x - info->width;
	info->object_end_x = info->screen_x + info->width;
	info->render_x = info->object_start_x;
}

void	set_obj_info(t_draw_obj *info, t_player *player, t_game *game)
{
	info->player_left = player->player_rad - M_PI / 6;
	info->player_right = player->player_rad + M_PI / 6;
	if (info->player_right < 0)
		info->player_right += M_PI * 2;
	if (info->player_left > M_PI * 2)
		info->player_left -= M_PI * 2;
	info->scale = (double)game->object_texture[info->target->type]
	[info->target->frame]->width / (info->target->distance * 2);
	info->width = game->object_texture[info->target->type]
	[info->target->frame]->width * info->scale;
	info->height = game->object_texture[info->target->type]
	[info->target->frame]->height * info->scale;
	info->object_rad = atan2(info->target->object_y - player->player_y,
			info->target->object_x - player->player_x);
	if (info->object_rad < 0)
		info->object_rad += M_PI * 2;
	info->angle_diff = info->object_rad - player->player_rad;
	while (info->angle_diff < M_PI)
		info->angle_diff += 2 * M_PI;
	while (info->angle_diff > M_PI)
		info->angle_diff -= 2 * M_PI;
	set_obj_info_sub(info);
}
