#include "cub3d_bonus.h"

void	render_player(t_god *god)
{
	int		x;
	int		y;
	int		row;
	int		col;
	t_point	p;

	set_point(&p, god->player.x, god->player.y);
	setting_map_location(&god->parse, &x, &y, &p);
	row = -(god->player.thickness) / 2 - 1;
	while (++row <= (god->player.thickness) / 2)
	{
		col = -(god->player.thickness) / 2 - 1;
		while (++col <= (god->player.thickness) / 2)
			god->img.data[god->map.window_width * (y + row)
				+ (x + col)] = 0x0000FF;
	}
}
