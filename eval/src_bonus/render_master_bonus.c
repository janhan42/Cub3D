#include "cub3d_bonus.h"

int	update_master(t_god *god)
{
	update_player(god);
	update_mouse(god);
	update_3Dvalue(god);
	update_door(god);
	update_ray(god);
	return (0);
}

int	ft_loop(t_god *god)
{
	update_master(god);
	render_map(god);
	is_in_door(god);
	is_in_room(god);
	render_ray(god);
	render_sprite(god);
	render_3d(god);
	render_player(god);
	mlx_put_image_to_window(god->mlx, god->win, god->img.ptr, 0, 0);
	return (0);
}

void	player_init(t_player *player)
{
	player->thickness = PLAYER_THICKNESS;
	player->walk_speed = WALKSPEED;
	player->turn_speed = TURNSPEED;
}

void	render_master(t_god *god)
{
	player_init(&(god->player));
	mlx_hook(god->win, X_EVENT_KEY_PRESS, (1L << 0), &key_press, &(god->key));
	mlx_hook(god->win, X_EVENT_KEY_RELEASE, (1L << 1),
		&key_release, &(god->key));
	mlx_hook(god->win, X_EVENT_KEY_EXIT, 0, &key_exit, god);
	mlx_loop_hook(god->mlx, ft_loop, god);
}
