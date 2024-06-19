/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_door_sub_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 00:57:56 by janhan            #+#    #+#             */
/*   Updated: 2024/06/19 12:53:45 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"

int	get_door_width(t_object *door, t_player *player)
{
	int		x;
	int		y;
	double	rad;
	int		width;

	x = door->object_x;
	y = door->object_y;
	if (door->type == VERTICAL_DOOR)
	{
		y = y - 32;
		rad = fabs(atan((y - player->player_y) / (x - player->player_x))
				- atan((y + 64 - player->player_y) / (x - player->player_x)));
	}
	else
		rad = fabs(atan2(y - player->player_y, x + 36 - player->player_x)
				- atan2(y - player->player_y, x - 36 - player->player_x));
	width = rad / (M_PI / 3) * WINDOW_W;
	return (width);
}

void	get_door_height_horizion(t_player *player, t_object *door,
double *longer, double *smaller)
{
	*longer = dist(player->player_x, player->player_y,
			door->object_x - ((int)door->object_x & 63),
			door->object_y);
	*longer = (WINDOW_H / *longer) * 100;
	*smaller = dist(player->player_x, player->player_y,
			door->object_x - ((int)door->object_x & 63) + 32,
			door->object_y);
	*smaller = (WINDOW_H / *smaller) * 100;
}

double	get_door_height(t_object *door, t_player *player,
int width, double *offset)
{
	double	middle;
	double	longer;
	double	smaller;
	double	gap;

	middle = (WINDOW_H / door->distance) * 100;
	if (door->type == VERTICAL_DOOR)
	{
		longer = dist(player->player_x, player->player_y,
				door->object_x, door->object_y - 34);
		longer = (WINDOW_H / longer) * 100;
		smaller = dist(player->player_x, player->player_y,
				door->object_x, door->object_y + 34);
		smaller = (WINDOW_H / smaller) * 100;
	}
	else
		get_door_height_horizion(player, door, &longer, &smaller);
	gap = fabs(longer - smaller);
	*offset = gap / width;
	return (middle);
}

void	set_door_info_sub(t_draw_door *info)
{
	info->rad_diff = info->door_rad - info->player_door_rad;
	if (info->rad_diff < 0)
		info->rad_diff += M_PI * 2;
	if ((info->rad_diff > 0 && info->rad_diff < M_PI_2)
		|| (info->rad_diff > M_PI && info->rad_diff < M_PI_2 + M_PI))
	{
		info->current_height = info->height
			+ info->h_offset * info->width / 2.0;
		info->h_offset = -info->h_offset;
	}
	else
		info->current_height = info->height
			- info->h_offset * info->width / 2.0;
	info->screen_x = (int)((info->angle_diff + M_PI / 6)
			* (WINDOW_W / (M_PI / 3)));
	info->door_start = info->screen_x - info->width / 2;
	info->door_end = info->screen_x + info->width / 2;
	info->render_x = info->door_start;
}

void	set_door_info(t_draw_door *info, t_player *player)
{
	info->player_door_rad
		= atan2(info->target->object_y - player->player_y,
			info->target->object_x - player->player_x);
	info->width = get_door_width(info->target, player);
	info->angle_diff = info->player_door_rad - player->player_rad;
	while (info->angle_diff < M_PI)
		info->angle_diff += 2 * M_PI;
	while (info->angle_diff > M_PI)
		info->angle_diff -= 2 * M_PI;
	info->height = get_door_height(info->target, player,
			info->width, &info->h_offset);
	if (info->player_door_rad < 0)
		info->player_door_rad += M_PI * 2;
	if (info->target->type == VERTICAL_DOOR)
		info->door_rad = M_PI_2;
	else
		info->door_rad = 2 * M_PI;
	set_door_info_sub(info);
}
