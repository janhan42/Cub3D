#include "cub3d_bonus.h"

void	update_mouse(t_god *god)
{
	if (god->key.mouse_on == TRUE)
	{
		mlx_mouse_hide();
		mlx_mouse_get_pos(god->win, &god->mouse.x, &god->mouse.y);
		mlx_mouse_move(god->win, god->map.window_width / 2,
			god->map.window_height / 2);
	}
	else
		mlx_mouse_show();
}
