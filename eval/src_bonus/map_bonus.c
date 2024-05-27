#include "cub3d_bonus.h"

void	setting_map_location(t_parse *parse, int *x, int *y, t_point *p)
{
	if (MAP_LOCATION == LEFTUP_MAP)
	{
		*x = (int)(MINIMAP_SCALE * p->x);
		*y = (int)(MINIMAP_SCALE * p->y);
	}
	else if (MAP_LOCATION == LEFTDOWN_MAP)
	{
		*x = (int)(MINIMAP_SCALE * p->x);
		*y = (int)((W_HEIGHT - MINIMAP_SCALE
					* parse->row) * TILE_SIZE + MINIMAP_SCALE * p->y);
	}
	else if (MAP_LOCATION == RIGHTUP_MAP)
	{
		*x = (int)((W_WIDTH - MINIMAP_SCALE * parse->col) * TILE_SIZE
				 + MINIMAP_SCALE * p->x);
		*y = (int)(MINIMAP_SCALE * p->y);
	}
	else if (MAP_LOCATION == RIGHTDOWN_MAP)
	{
		*x = (int)((W_WIDTH - MINIMAP_SCALE * parse->col) * TILE_SIZE
				 + MINIMAP_SCALE * p->x);
		*y = (int)((W_HEIGHT - MINIMAP_SCALE
					* parse->row) * TILE_SIZE + MINIMAP_SCALE * p->y);
	}
}

void	fill_squares(t_god *god, int x, int y, int color)
{
	int		i;
	int		j;
	t_point	p;

	set_point(&p, x, y);
	setting_map_location(&god->parse, &x, &y, &p);
	j = -1;
	while (++j <= (int)(MINIMAP_SCALE * TILE_SIZE))
	{
		i = -1;
		while (++i <= (int)(MINIMAP_SCALE * TILE_SIZE))
			god->img.data[god->map.window_width * (y + j) + (x + i)] = color;
	}
}

void	init_map(t_god *god)
{
	int	x;
	int	y;

	y = -1;
	while (++y < god->map.window_height)
	{
		x = -1;
		while (++x < god->map.window_width)
			god->img.data[god->map.window_width * y + x] = NO_COLOR;
	}
}

void	color_map(t_god *god, int row, int col)
{
	if (god->map.map[row][col] == '1')
		fill_squares(god, (int)(TILE_SIZE * col),
			(int)(TILE_SIZE * row), 0x000000);
	else if (god->map.map[row][col] == ' ')
		fill_squares(god, (int)(TILE_SIZE * col),
			(int)(TILE_SIZE * row), NO_COLOR);
	else if (ft_strchr("2F", god->map.map[row][col]) != NULL)
		fill_squares(god, (int)(TILE_SIZE * col),
			(int)(TILE_SIZE * row), 0x00ff00);
	else if (god->map.map[row][col] == '3')
		fill_squares(god, (int)(TILE_SIZE * col),
			(int)(TILE_SIZE * row), 0x00ffff);
	else if (god->map.map[row][col] == '5')
		fill_squares(god, (int)(TILE_SIZE * col),
			(int)(TILE_SIZE * row), 0x843600);
	else if (god->map.map[row][col] == '4')
		fill_squares(god, (int)(TILE_SIZE * col),
			(int)(TILE_SIZE * row), 0x883388);
	else
		fill_squares(god, (int)(TILE_SIZE * col),
			(int)(TILE_SIZE * row), 0xffffff);
}

void	render_map(t_god *god)
{
	int	col;
	int	row;

	init_map(god);
	row = -1;
	while (++row < god->parse.row)
	{
		col = -1;
		while (++col < god->parse.col)
			color_map(god, row, col);
	}
}
