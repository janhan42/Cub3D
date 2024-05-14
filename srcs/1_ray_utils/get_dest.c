/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 11:31:58 by janhan            #+#    #+#             */
/*   Updated: 2024/05/14 17:50:39 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"
#include <math.h>

/*
	수평선 체크를 위한 info 정리 및 초기화
*/
static void	check_horizion_init(double x, double y, double rad, t_ray_dest *ray)
{
	ray->hx = x;
	ray->hy = y;
	ray->a_tan = -1 / tan(rad);
	ray->distance_h = 100000000;
	ray->dof = 0;
	if (rad > M_PI)
	{
		ray->ry = (((int)y >> 6) << 6) - 0.0001;
		ray->rx = (y - ray->ry) * ray->a_tan + x;
		ray->yo = -64;
		ray->xo = -ray->yo * ray->a_tan;
	}
	if (rad < M_PI)
	{
		ray->ry = (((int)y >> 6) << 6) + 64;
		ray->rx = (y - ray->ry) * ray->a_tan + x;
		ray->yo = 64;
		ray->xo = -ray->yo * ray->a_tan;
	}
	if (rad == 0 || rad == M_PI)
	{
		ray->rx = x;
		ray->ry = y;
		ray->dof = 8;
	}
}

/*
	맵 파일에서의 좌표 및 ray의 좌표를 확인후 거리 계산
*/
static void	check_horizion(t_game *game, t_ray_dest *ray, double x, double y)
{
	while (ray->dof < 8)
	{
		ray->mx = (int)ray->rx >> 6;
		ray->my = (int)ray->ry >> 6;
		if (ray->mx < 0 || ray->mx > game->map_width
			|| ray->my < 0 || ray->my > game->map_height)
			break ;
		if (ray->mx >= 0 && ray->mx < game->map_width / 64
			&& ray->my >= 0 && ray->my < game->map_height / 64
			&& game->map[ray->my][ray->mx] == '1')
		{
			ray->hx = ray->rx;
			ray->hy = ray->ry;
			ray->distance_h = dist(x, y, ray->hx, ray->hy);
			ray->dof = 8;
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
	수직선 체크를 위한 info 정리 및 초기화
*/
static void	check_vertical_init(double x, double y, double rad, t_ray_dest *ray)
{
	ray->n_tan = -tan(rad);
	ray->dof = 0;
	ray->distance_v = 100000000;
	ray->vx = x;
	ray->vy = y;
	if (rad > M_PI_2 && rad < M_PI + M_PI_2)
	{
		ray->rx = (((int)x >> 6) << 6) - 0.0001;
		ray->ry = (x - ray->rx) * ray->n_tan + y;
		ray->xo = -64;
		ray->yo = -ray->xo * ray->n_tan;
	}
	if (rad < M_PI_2 || rad > M_PI + M_PI_2)
	{
		ray->rx = (((int)x >> 6) << 6) + 64;
		ray->ry = (x - ray->rx) * ray->n_tan + y;
		ray->xo = 64;
		ray->yo = -ray->xo * ray->n_tan;
	}
	if (rad == M_PI_2 || rad == M_PI + M_PI_2)
	{
		ray->rx = x;
		ray->ry = y;
		ray->dof = 8;
	}
}

/*
	맵 파일에서의 좌표 및 ray의 좌표를 확인후 거리 계산
*/
static void	check_vertical(t_game *game, t_ray_dest *ray, double x, double y)
{
	while (ray->dof < 8)
	{
		if (ray->rx - (ray->rx / 1) >= 0.5)
			ray->mx = ((int)ray->rx + 1) >> 6;
		else
			ray->mx = (int)ray->rx >> 6;
		if (ray->ry - (ray->ry / 1) >= 0.5)
			ray->my = ((int)ray->rx + 1) >> 6;
		else
			ray->my = (int)ray->ry >> 6;
		if (ray->mx < 0 || ray->mx > game->map_width
			|| ray->my < 0 || ray->my > game->map_height)
			break ;
		if (ray->mx >= 0
			&& ray->mx < game->map_width / 64
			&& ray->my >= 0 && ray->my < game->map_height / 64
			&& game->map[ray->my][ray->mx] == '1')
		{
			ray->vx = ray->rx;
			ray->vy = ray->ry;
			ray->distance_v = dist(x, y, ray->vx, ray->vy);
			ray->dof = 8;
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
	check_horizion_init(x, y, rad, game->ray_info);
	check_horizion(game, game->ray_info, x, y);
	check_vertical_init(x, y, rad, game->ray_info);
	check_vertical(game, game->ray_info, x, y);
	if (game->ray_info->distance_h < game->ray_info->distance_v)
	{	// 위 아래 둘중 하나
		dest->x = game->ray_info->hx;
		dest->y = game->ray_info->hy;
		dest->distance = game->ray_info->distance_h;

		if (rad > 0 && rad < M_PI) // upside
			dest->direction = 1;
		else
			dest->direction = 3;
		dest->offset = game->ray_info->hx - floor(game->ray_info->hx);
		if (!(rad > 0 && rad < M_PI)) // 하단
			dest->offset = 1 - dest->offset;
	}
	if (game->ray_info->distance_v < game->ray_info->distance_h)
	{
		dest->x = game->ray_info->vx;
		dest->y = game->ray_info->vy;
		dest->distance = game->ray_info->distance_v;
		dest->y_vert %= 1;
		dest->offset =  dest->y_vert;
		if (rad > M_PI_2 && rad < M_PI + M_PI_2) // leftside
			dest->direction = 2;
		else
			dest->direction = 0;
		dest->offset = game->ray_info->vy - floor(game->ray_info->vy);
		if (!(rad > M_PI_2 && rad < 3 * M_PI_2)) // 우측
			dest->offset = 1 - dest->offset;
	}
	return (dest);
}
