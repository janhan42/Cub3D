#include "cub3d_bonus.h"

int	key_press2(int keycode, t_key *key)
{
	if (keycode == KEY_1)
		key->open_door = TRUE;
	if (keycode == KEY_2)
		key->open_door = FALSE;
	if (keycode == KEY_3)
		key->mouse_on = TRUE;
	if (keycode == KEY_4)
		key->mouse_on = FALSE;
	return (0);
}

int	key_press(int keycode, t_key *key)
{
	if (keycode == KEY_A)
		key->left = TRUE;
	if (keycode == KEY_D)
		key->right = TRUE;
	if (keycode == KEY_W)
		key->up = TRUE;
	if (keycode == KEY_S)
		key->down = TRUE;
	if (keycode == KEY_RIGHT)
		key->right_rotation = TRUE;
	if (keycode == KEY_LEFT)
		key->left_rotation = TRUE;
	if (keycode == KEY_UP)
		key->updown_sight = -1;
	if (keycode == KEY_DOWN)
		key->updown_sight = 1;
	if (keycode == KEY_ESC)
		exit(0);
	return (key_press2(keycode, key));
}

int	key_release(int keycode, t_key *key)
{
	if (keycode == KEY_A)
		key->left = FALSE;
	if (keycode == KEY_D)
		key->right = FALSE;
	if (keycode == KEY_W)
		key->up = FALSE;
	if (keycode == KEY_S)
		key->down = FALSE;
	if (keycode == KEY_RIGHT)
		key->right_rotation = FALSE;
	if (keycode == KEY_LEFT)
		key->left_rotation = FALSE;
	if (keycode == KEY_UP)
		key->updown_sight = 0;
	if (keycode == KEY_DOWN)
		key->updown_sight = 0;
	if (keycode == KEY_ESC)
		exit(0);
	if (keycode == KEY_1)
		key->open_door = 2;
	if (keycode == KEY_2)
		key->open_door = 2;
	return (0);
}

int	key_exit(void)
{
	exit(0);
	return (0);
}
