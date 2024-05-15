#include "cub3d.h"

int	draw_sky(t_god *god, int ray_num, int wall_top, int color)
{
	int	y;
	int	x;

	y = -1;
	while (++y < wall_top)
	{
		x = -1;
		while (++x < WALL_STRIP_WIDTH)
			if (god->img.data[god->map.window_width * y
					+ (x + ray_num * WALL_STRIP_WIDTH)] == NO_COLOR)
				god->img.data[god->map.window_width * y
					+ (x + ray_num * WALL_STRIP_WIDTH)] = color;
	}
	return (0);
}

int	draw_bottom(t_god *god, int ray_num, int wall_bottom, int color)
{
	int	x;
	int	y;

	y = wall_bottom - 1;
	while (++y < god->map.window_height)
	{
		x = -1;
		while (++x < WALL_STRIP_WIDTH)
			if (god->img.data[god->map.window_width * y
					+ (x + ray_num * WALL_STRIP_WIDTH)] == NO_COLOR)
				god->img.data[god->map.window_width * y
					+ (x + ray_num * WALL_STRIP_WIDTH)] = color;
	}
	return (0);
}

int	set_wall_color(t_god *god, t_3d *v, int r, int i)
{
	int	col;
	int	paper;
	int	row;

	set_wall_diretion(god, i);
	paper = god->ray.wall_paper;
	if (paper == T_WE || paper == T_EA)
		col = ((int)god->rray[i].wall_hity % TILE_SIZE)
			* (god->parse.tex[paper].width / TILE_SIZE);
	else
		col = (int)god->rray[i].wall_hitx % TILE_SIZE
			* (god->parse.tex[paper].width / TILE_SIZE);
	row = (((v->correct_top - v->top + r)
				* god->parse.tex[paper].height) / v->height);
	return (god->parse.tex[paper].texture[(int)god->parse.tex[paper].width
			* row + col]);
}

void	render_3D_project_walls(t_god *god, int i)
{
	t_3d	v;
	int		r;
	int		x;
	int		y;

	init_3D(god, &v, i);
	r = 0;
	y = v.correct_top - 1;
	while (++y < v.correct_bottom)
	{
		x = -1;
		while (++x < WALL_STRIP_WIDTH)
			if (god->img.data[god->map.window_width * y
					+ (x + i * WALL_STRIP_WIDTH)] == NO_COLOR)
				god->img.data[god->map.window_width * y
					+ (x + i * WALL_STRIP_WIDTH)]
					= set_wall_color(god, &v, r, i);
		r++;
	}
	draw_sky(god, i, v.correct_top, god->parse.ceiling_color);
	draw_bottom(god, i, v.correct_bottom, god->parse.floor_color);
}

void	render_3d(t_god *god)
{
	int	i;

	i = -1;
	while (++i < god->map.ray_count)
		render_3D_project_walls(god, i);
}
