#include "cub3d.h"

int	exit_cub3d(t_god *god, int exit_code)
{
	if (god->img.ptr)
		mlx_destroy_image(god->mlx, god->img.ptr);
	if (god->win)
		mlx_destroy_window(god->mlx, god->win);
	if (god)
		exit(exit_code);
	else
		exit(0);
	return (exit_code);
}

int	exit_error(t_god *god, int exit_code, const char *message)
{
	write(2, "ERROR\n", 6);
	if (message)
	{
		write(2, message, ft_strlen(message));
		write(2, "\n", 1);
	}
	exit_cub3d(god, exit_code);
	return (exit_code);
}
