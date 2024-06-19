/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 11:31:58 by janhan            #+#    #+#             */
/*   Updated: 2024/06/19 12:38:42 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_mand/header_mand.h"
#include <math.h>

static void	check_horizion(t_game *game, t_ray_dest *ray, double x, double y)
{
	while (ray->dof < 100)
	{
		ray->mx = (int)ray->rx >> 6;
		ray->my = (int)ray->ry >> 6;
		if (ray->mx < 0 || ray->mx > game->map_len_w
			|| ray->my < 0 || ray->my > game->map_len_h)
			break ;
		if (ray->mx >= 0 && ray->mx < game->map_len_w
			&& ray->my >= 0 && ray->my < game->map_len_h
			&& (ft_strchr("1 ", game->map[ray->my][ray->mx])) != NULL)
		{
			ray->hx = ray->rx;
			ray->hy = ray->ry;
			ray->distance_h = dist(x, y, ray->hx, ray->hy);
			ray->dof = 100;
		}
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			ray->dof += 1;
		}
	}
}

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
			&& (ft_strchr("1 ", game->map[ray->my][ray->mx])) != NULL)
		{
			ray->vx = ray->rx;
			ray->vy = ray->ry;
			ray->distance_v = dist(x, y, ray->vx, ray->vy);
			ray->dof = 100;
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
		if (rad > M_PI_2 && rad < M_PI + M_PI_2)
			dest->wall_type = EAST;
		else
			dest->wall_type = WEST;
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
		if (rad > 0 && rad < M_PI)
			dest->wall_type = NORTH;
		else
			dest->wall_type = SOUTH;
		dest->offset = game->ray_info->hx - floor(game->ray_info->hx);
		if (!(rad > 0 && rad < M_PI))
			dest->offset = 1 - dest->offset;
	}
	compare_distance_sub(game, dest, rad);
}

t_dest	get_dest(double x, double y, double rad, t_game *game)
{
	t_dest	dest;

	if (rad > 2 * M_PI)
		rad -= 2 * M_PI;
	if (rad < 0)
		rad += 2 * M_PI;
	check_horizion_init(x, y, rad, game->ray_info);
	check_horizion(game, game->ray_info, x, y);
	check_vertical_init(x, y, rad, game->ray_info);
	check_vertical(game, game->ray_info, x, y);
	compare_distance(game, &dest, rad);
	return (dest);
}
