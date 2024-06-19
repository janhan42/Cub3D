/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dest_sub.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:21:20 by janhan            #+#    #+#             */
/*   Updated: 2024/06/19 12:38:52 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_mand/header_mand.h"

void	check_horizion_init(double x, double y, double rad, t_ray_dest *ray)
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
		ray->dof = 100;
	}
}

void	check_vertical_init(double x, double y, double rad, t_ray_dest *ray)
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
		ray->dof = 100;
	}
}
