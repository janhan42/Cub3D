#include "cub3d_bonus.h"

void	init_t_cal_ray(t_god *god, t_cal_ray *c, double *dx, double *dy)
{
	c->ray_x = god->player.x;
	c->ray_y = god->player.y;
	c->max_value = fmax(fabs(*dx), fabs(*dy));
	if (c->max_value == 0)
		return ;
	*dx /= c->max_value;
	*dy /= c->max_value;
}

void	draw_line(t_god *god, double dx, double dy)
{
	t_cal_ray	c;
	t_point		p1;
	t_point		p2;

	init_t_cal_ray(god, &c, &dx, &dy);
	while (1)
	{
		set_point(&p1, c.ray_x, c.ray_y);
		set_point(&p2, c.ray_x + dx, c.ray_y + dy);
		if (is_door(god, c.ray_x + dx, c.ray_y + dy) == 0
			&& !check_edge(god, &p1, &p2)
			&& !is_wall(god, c.ray_x + dx, c.ray_y + dy))
		{
			c.ray_x += dx;
			c.ray_y += dy;
		}
		else
			break ;
		setting_map_location(&god->parse, &c.x, &c.y, &p1);
		god->img.data[god->map.window_width * c.y + c.x] = 0xFF0000;
	}
}

void	render_ray(t_god *god)
{
	int	i;

	i = -1;
	while (++i < god->map.ray_count)
		draw_line(god, god->rray[i].wall_hitx
			- god->player.x, god->rray[i].wall_hity - god->player.y);
}
