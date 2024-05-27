#include "cub3d_bonus.h"

void	update_3Dvalue(t_god *god)
{
	god->player.updown_sight += UPDOWNSPEED * (god->key.updown_sight);
	if (god->key.mouse_on == TRUE)
		if (++god->mouse.delay_y > 5)
			god->player.updown_sight += 2
				* (god->mouse.y - god->map.window_height / 2);
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
	if (god->key.mouse_on == TRUE)
		if (++god->mouse.delay_x > 5)
			god->player.rota_angle += ((god->mouse.x
						- god->map.window_width / 2) / (100 * PI));
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
	if (is_door(god, u.new_x, u.new_y) != CLOSE_DOOR
		&& !is_wall(god, u.new_x, u.new_y)
		&& !is_sprite(god, u.new_x, u.new_y)
		&& !check_edge(god, &p1, &p2))
	{
		god->player.x = u.new_x;
		god->player.y = u.new_y;
	}
}

void	update_door(t_god *god)
{
	int	x;
	int	y;

	x = (int)god->player.x / TILE_SIZE;
	y = (int)god->player.y / TILE_SIZE;
	if (god->key.open_door == TRUE)
	{
		if (god->map.map[y - 1][x] == '3')
			god->map.map[y - 1][x] = '4';
		else if (god->map.map[y + 1][x] == '3')
			god->map.map[y + 1][x] = '4';
	}
	else if (god->key.open_door == FALSE)
	{
		if (god->map.map[y - 1][x] == '4')
			god->map.map[y - 1][x] = '3';
		else if (god->map.map[y + 1][x] == '4')
			god->map.map[y + 1][x] = '3';
	}
}
