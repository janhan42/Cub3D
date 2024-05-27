#include "cub3d.h"

void	ray_init(t_ray *ray, double rayAngle)
{
	ray->ray_angle = normalize_angle(rayAngle);
	ray->facing_down = ray->ray_angle > 0 && ray->ray_angle < PI;
	ray->facing_up = !ray->facing_down;
	ray->facing_right = ray->ray_angle < 0.5 * PI || ray->ray_angle > 1.5 * PI;
	ray->facing_left = !ray->facing_right;
}

void	set_wall_diretion(t_god *god, int i)
{
	if (god->rray[i].hit_vertical == TRUE
		&& (god->player.x - god->rray[i].wall_hitx) > 0)
		god->ray.wall_paper = T_WE;
	else if (god->rray[i].hit_vertical == TRUE
		&& (god->player.x - god->rray[i].wall_hitx) < 0)
		god->ray.wall_paper = T_EA;
	else if (god->rray[i].hit_vertical == FALSE
		&& (god->player.y - god->rray[i].wall_hity) > 0)
		god->ray.wall_paper = T_NO;
	else
		god->ray.wall_paper = T_SO;
}

void	init_3D(t_god *god, t_3d *v, int i)
{
	if (god->rray[i].distance == 0)
		god->rray[i].distance = 0.1;
	v->correct_distance = god->rray[i].distance
		* cos(god->rray[i].angle - god->player.rota_angle);
	v->distance_plane = (god->map.window_width / 2) / tan(FOV_ANGLE / 2);
	v->projected_height = (int)((TILE_SIZE / v->correct_distance)
			* v->distance_plane);
	v->top = (god->map.window_height / 2)
		- (v->projected_height / 2) - god->player.updown_sight;
	v->correct_top = ternaries_func(v->top < 0, 1, v->top);
	v->bottom = (god->map.window_height / 2)
		+ (v->projected_height / 2) - god->player.updown_sight;
	v->correct_bottom = ternaries_func(v->bottom > god->map.window_height,
			god->map.window_height, v->bottom);
	v->height = v->bottom - v->top;
}

void	init_map_malloc(t_god *god)
{
	int	y;
	int	row;
	int	col;

	god->map.map = (char **)malloc(sizeof(char *) * god->map.map_rows);
	y = -1;
	while (++y < god->map.map_rows)
		god->map.map[y] = (char *)malloc(sizeof(char)
				* (god->map.map_cols + 1));
	row = -1;
	while (++row < god->parse.row)
	{
		col = -1;
		while (god->parse.map[row][++col] != '\0')
			god->map.map[row][col] = god->parse.map[row][col];
		col--;
		while (++col < god->map.map_cols)
			god->map.map[row][col] = ' ';
		god->map.map[row][col] = '\0';
	}
	free_array_memory((void **)god->parse.map, god->parse.row);
}
