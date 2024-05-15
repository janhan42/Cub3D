#include "cub3d.h"

void	update_3Dvalue(t_god *god)
{
	god->player.updown_sight += UPDOWNSPEED * (god->key.updown_sight);
	if (god->player.updown_sight > god->map.window_height / 2)
		god->player.updown_sight = god->map.window_height / 2;
	if (god->player.updown_sight < -god->map.window_height / 2)
		god->player.updown_sight = -god->map.window_height / 2;
}

void	update_player2(t_god *god, t_dpable_update *u)
{
	if (god->key.left == TRUE && god->key.right == FALSE)
	{
		u->walk_direction = 1.0;
		u->moveside = PI / 2.0;
		if (god->key.up == TRUE && god->key.down == FALSE)
			u->moveside = HALF_PI / 2;
		if (god->key.down == TRUE && god->key.up == FALSE)
		{
			u->walk_direction = -1.0;
			u->moveside = -HALF_PI / 2;
		}
	}
	if (god->key.left_rotation == TRUE)
		u->turn_direction = -1.0;
	if (god->key.right_rotation == TRUE)
		u->turn_direction = 1.0;
	if (god->key.up == TRUE && god->key.down == FALSE)
		u->walk_direction = 1.0;
	if (god->key.down == TRUE && god->key.up == FALSE)
		u->walk_direction = -1.0;
}

void	update_player3(t_god *god, t_dpable_update *u)
{
	if (god->key.right == TRUE && god->key.left == FALSE)
	{
		u->walk_direction = -1.0;
		u->moveside = HALF_PI;
		if (god->key.up == TRUE && god->key.down == FALSE)
		{
			u->walk_direction = 1.0;
			u->moveside = -HALF_PI / 2;
		}
		if (god->key.down == TRUE && god->key.up == FALSE)
			u->moveside = HALF_PI / 2;
	}
	god->player.rota_angle += u->turn_direction * god->player.turn_speed;
}

void	update_player(t_god *god)
{
	t_dpable_update	u;
	t_point			p1;
	t_point			p2;

	ft_memset(&u, 0, sizeof(t_dpable_update));
	update_player2(god, &u);
	update_player3(god, &u);
	u.move_step = u.walk_direction * god->player.walk_speed;
	u.new_x = god->player.x + u.move_step
		* cos(god->player.rota_angle - u.moveside);
	u.new_y = god->player.y + u.move_step
		* sin(god->player.rota_angle - u.moveside);
	set_point(&p1, god->player.x, god->player.y);
	set_point(&p2, u.new_x, u.new_y);
	if (!is_wall(god, u.new_x, u.new_y)
		&& !check_edge(god, &p1, &p2))
	{
		god->player.x = u.new_x;
		god->player.y = u.new_y;
	}
}
