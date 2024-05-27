#include "cub3d_bonus.h"

void	cal_ray(t_god *god, t_dpable_ray *hv, int a, int b)
{
	double	next_touchX;
	double	next_touchY;
	int		door;

	next_touchX = hv->xintercept;
	next_touchY = hv->yintercept;
	while (next_touchX >= 0 && next_touchX <= god->parse.col * TILE_SIZE
		&& next_touchY >= 0 && next_touchY <= god->parse.row * TILE_SIZE)
	{
		door = is_door(god, next_touchX + a, next_touchY + b);
		if (is_wall(god, next_touchX + a, next_touchY + b) || door != FALSE)
		{
			hv->is_door = door;
			hv->found_wall_hit = TRUE;
			hv->wall_hitx = next_touchX;
			hv->wall_hity = next_touchY;
			break ;
		}
		next_touchX += hv->xstep;
		next_touchY += hv->ystep;
	}
	cal_distance(god, hv);
}

void	cal_horz_ray(t_god *god, t_dpable_ray *horz)
{
	horz->found_wall_hit = FALSE;
	horz->wall_hitx = 0;
	horz->wall_hity = 0;
	horz->yintercept = floor(god->player.y / TILE_SIZE) * TILE_SIZE;
	horz->yintercept += ternaries_func(god->ray.facing_down, TILE_SIZE, 0);
	horz->xintercept = god->player.x + (horz->yintercept - god->player.y)
		/ tan(god->ray.ray_angle);
	horz->ystep = TILE_SIZE;
	horz->ystep *= ternaries_func(god->ray.facing_up, -1, 1);
	horz->xstep = TILE_SIZE / tan(god->ray.ray_angle);
	horz->xstep *= ternaries_func(god->ray.facing_left
			&& horz->xstep > 0, -1, 1);
	horz->xstep *= ternaries_func(god->ray.facing_right
			&& horz->xstep < 0, -1, 1);
	cal_ray(god, horz, 0, ternaries_func(god->ray.facing_up, -1, 0));
}

void	cal_vert_ray(t_god *god, t_dpable_ray *vert)
{
	vert->found_wall_hit = FALSE;
	vert->wall_hitx = 0;
	vert->wall_hity = 0;
	vert->xintercept = floor(god->player.x / TILE_SIZE) * TILE_SIZE;
	vert->xintercept += ternaries_func(god->ray.facing_right, TILE_SIZE, 0);
	vert->yintercept = god->player.y + (vert->xintercept - god->player.x)
		* tan(god->ray.ray_angle);
	vert->xstep = TILE_SIZE;
	vert->xstep *= ternaries_func(god->ray.facing_left, -1, 1);
	vert->ystep = TILE_SIZE * tan(god->ray.ray_angle);
	vert->ystep *= ternaries_func(god->ray.facing_up && vert->ystep > 0, -1, 1);
	vert->ystep *= ternaries_func(god->ray.facing_down
			&& vert->ystep < 0, -1, 1);
	cal_ray(god, vert, ternaries_func(god->ray.facing_left, -1, 0), 0);
}

void	update_one_ray(t_god *god, double angle, int i)
{
	t_dpable_ray	horz;
	t_dpable_ray	vert;

	ray_init(&god->ray, angle);
	cal_horz_ray(god, &horz);
	cal_vert_ray(god, &vert);
	if (vert.distance < horz.distance)
	{
		god->rray[i].is_door = vert.is_door;
		god->rray[i].wall_hitx = vert.wall_hitx;
		god->rray[i].wall_hity = vert.wall_hity;
		god->rray[i].distance = vert.distance;
		god->rray[i].hit_vertical = TRUE;
	}
	else
	{
		god->rray[i].is_door = horz.is_door;
		god->rray[i].wall_hitx = horz.wall_hitx;
		god->rray[i].wall_hity = horz.wall_hity;
		god->rray[i].distance = horz.distance;
		god->rray[i].hit_vertical = FALSE;
	}
	vert.is_door = FALSE;
	horz.is_door = FALSE;
	god->rray[i].angle = god->ray.ray_angle;
}

void	update_ray(t_god *god)
{
	double	angle;
	// double	maxAngle;
	int		i;

	i = 0;
	angle = god->player.rota_angle - (RAY_RANGE / 2.0);
	// maxAngle = god->player.rota_angle + (RAY_RANGE / 2.0);
	while (i < god->map.ray_count)
	{
		update_one_ray(god, angle, i);
		angle += RAY_RANGE / god->map.ray_count;
		i++;
	}
}
