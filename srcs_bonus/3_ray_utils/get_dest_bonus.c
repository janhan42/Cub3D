/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dest_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 11:31:58 by janhan            #+#    #+#             */
/*   Updated: 2024/05/28 17:24:15 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"
#include <math.h>

/*
	맵 파일에서의 좌표 및 ray의 좌표를 확인후 거리 계산
*/
static void	check_horizion(t_game *game, t_ray_dest *ray, double x, double y)
{
	while (ray->dof < 100)
	{
		ray->mx = (int)ray->rx >> 6;
		ray->my = (int)ray->ry >> 6;
		if (ray->mx < 0 || ray->mx > game->map_width
			|| ray->my < 0 || ray->my > game->map_height)
			break ;
		if (ray->mx >= 0 && ray->mx < game->map_width / 64
			&& ray->my >= 0 && ray->my < game->map_height / 64
			&& (ft_strchr("1D", game->map[ray->my][ray->mx])) != NULL)
		{
			ray->hx = ray->rx;
			ray->hy = ray->ry;
			ray->distance_h = dist(x, y, ray->hx, ray->hy);
			ray->dof = 100;
			if (game->map[ray->my][ray->mx] == 'D')
				ray->is_h_door = 1;
		}
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			ray->dof += 1;
		}
	}
}

/*
	맵 파일에서의 좌표 및 ray의 좌표를 확인후 거리 계산
*/
static void	check_vertical(t_game *game, t_ray_dest *ray, double x, double y)
{
	while (ray->dof < 100)
	{
		ray->mx = (int)ray->rx >> 6;
		ray->my = (int)ray->ry >> 6;
		if (ray->mx < 0 || ray->mx > game->map_width
			|| ray->my < 0 || ray->my > game->map_height)
			break ;
		if (ray->mx >= 0 && ray->mx < game->map_width / 64
			&& ray->my >= 0 && ray->my < game->map_height / 64
			&& (ft_strchr("1D", game->map[ray->my][ray->mx])) != NULL)
		{
			ray->vx = ray->rx;
			ray->vy = ray->ry;
			ray->distance_v = dist(x, y, ray->vx, ray->vy);
			ray->dof = 100;
			if (game->map[ray->my][ray->mx] == 'D')
				ray->is_v_door = 1;
		}
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			ray->dof += 1;
		}
	}
}

static void	compare_distance_sub(t_game *game, t_dest *dest, double rad)
{
	if (game->ray_info->distance_v < game->ray_info->distance_h)
	{
		dest->x = game->ray_info->vx;
		dest->y = game->ray_info->vy;
		dest->distance = game->ray_info->distance_v;
		dest->y_vert %= 1;
		dest->offset = dest->y_vert;
		if (game->ray_info->is_v_door)
			dest->wall_type = DOOR;
		else if (rad > M_PI_2 && rad < M_PI + M_PI_2)
			dest->wall_type = WEST;
		else
			dest->wall_type = EAST;
		dest->offset = game->ray_info->vy - floor(game->ray_info->vy);
		if (!(rad > M_PI_2 && rad < 3 * M_PI_2))
			dest->offset = 1 - dest->offset;
	}
}

static void	compare_distance(t_game *game, t_dest *dest, double rad)
{
	if (game->ray_info->distance_h < game->ray_info->distance_v)
	{
		dest->x = game->ray_info->hx;
		dest->y = game->ray_info->hy;
		dest->distance = game->ray_info->distance_h;
		if (game->ray_info->is_h_door)
			dest->wall_type = DOOR;
		else if (rad > 0 && rad < M_PI)
			dest->wall_type = NORTH;
		else
			dest->wall_type = SOUTH;
		dest->offset = game->ray_info->hx - floor(game->ray_info->hx);
		if (!(rad > 0 && rad < M_PI))
			dest->offset = 1 - dest->offset;
	}
	compare_distance_sub(game, dest, rad);
}

/*
 * dest[3] == 0 or 1 or 2 or 3
 * 			 right / up / left / down
 */
t_dest	*get_dest(double x, double y, double rad, t_game *game)
{
	t_dest	*dest;

	dest = ft_calloc(1, sizeof(t_dest));
	if (rad > 2 * M_PI)
		rad -= 2 * M_PI;
	if (rad < 0)
		rad += 2 * M_PI;
	game->ray_info->is_h_door = 0;
	game->ray_info->is_v_door = 0;
	check_horizion_init(x, y, rad, game->ray_info);
	check_horizion(game, game->ray_info, x, y);
	check_vertical_init(x, y, rad, game->ray_info);
	check_vertical(game, game->ray_info, x, y);
	compare_distance(game, dest, rad);
	return (dest);
}
