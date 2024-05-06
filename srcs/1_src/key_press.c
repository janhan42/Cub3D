/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:01:33 by janhan            #+#    #+#             */
/*   Updated: 2024/05/06 15:23:56 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void    key_press_intro(int key, t_game *game)
{
    key = 0;
    game->data->mouse.on_click = 1;
}

void    key_press_setting(int key, t_game *game)
{
    int o;

    o = game->data->mouse.on_hov[0] + 2 * game->data->mouse.on_hov[1] + 3 * game->data->mouse.on_hov[2];
    if (key == UP && !o)
        game->data->mouse.on_hov[2] = 1;
    else if (key == UP)
    {
        game->data->mouse.on_hov[o - 1] = 0;
        game->data->mouse.on_hov[o % 3] = 0;
        game->data->mouse.on_hov[(o + 1) % 3] = 1;
    }
    if (key == DOWN && !o)
            game->data->mouse.on_hov[0] = 1;
    else if (key == DOWN)
    {
        game->data->mouse.on_hov[o - 1] = 0;
        game->data->mouse.on_hov[o % 3] = 1;
        game->data->mouse.on_hov[(o + 1) % 3] = 0;
    }
    if (key == ENTER && o)
        game->data->mouse.on_clk[o - 1] = 1;
}

void    key_press_setting2(int key, t_game *game)
{
    int o;

    o = 2 * game->data->mouse.on_hov[1] + 3 * game->data->mouse.on_hov[2] + 4 * game->data->mouse.on_hov[3] + 5 * game->data->mouse.on_hov[4];
    if (key == UP && !o)
        game->data->mouse.on_hov[2] = 1;
    else if (key == UP)
    {
        game->data->mouse.on_hov[o - 1] = 0;
        game->data->mouse.on_hov[o % 5 + (o > 4)] = 0;
        game->data->mouse.on_hov[(o + 1) % 5 + ((o + 1) > 4)] = 0;
        game->data->mouse.on_hov[(o + 2) % 5 + ((o + 2) > 4)] = 1;
    }
    if (key == DOWN && !o)
            game->data->mouse.on_hov[3] = 1;
    else if (key == DOWN)
    {
        game->data->mouse.on_hov[o - 1] = 0;
        game->data->mouse.on_hov[o % 5 + (o > 4)] = 1;
        game->data->mouse.on_hov[(o + 1) % 5 + ((o + 1) > 4)] = 0;
        game->data->mouse.on_hov[(o + 2) % 5 + ((o + 2) > 4)] = 0;
    }
    if (key == ENTER && o)
        game->data->mouse.on_clk[o - 1] = 1;
    if (key == ESC)
        game->data->mode = ANIMATE_SETT2_OUT;
}

int key_not_in_use(int key, t_game *game)
{
    int i;

    i = -1;
    while (++i < 12)
        if (key == game->data->intro.g_k[i] && !game->data->intro.on_clk[i + 4])
            return (0);
    return (1);
}

void    key_press_control(int key, t_game *game)
{
    int i;
    int pos;

    pos = -1;
    if (key == ESC)
        game->data->mode = SETTING * !game->data->mouse.sett2 + SETTING2 * game->data->mouse.sett2;
    if (key_not_in_use(key, game))
    {
        i = -1;
        while (++i < 12)
            if (game->data->intro.on_clk[i + 4])
                pos = i;
        if (game->data->intro.keys[key] && pos != -1)
            game->data->intro.g_k[pos] = key;
    }
    i = -1;
    while (++i < 16)
        game->data->intro.on_clk[i] = 0;
}

void    key_press_map(int key, t_game *game)
{
    if (key == game->data->intro.g_k[10])
        game->data->intro.up = !game->data->intro.up,
        game->data->mv_x = 0,
        game->data->mv_y = 0,
        game->data->keys[game->data->intro.g_k[7]] = 0;
}

void    key_press_game(int key, t_game *game)
{
	if (game->data->objects.health > 0)
	{
		if (key == F1 && game->data->mouse.show)
			mlx_mouse_hide(),
			game->data->mouse.show = 0;
		else if (key == F1)
			mlx_mouse_show(),
			game->data->mouse.show = 1;
		if (key == game->data->intro.g_k[10])
			game->data->mode = G_MAP,
			game->data->intro.up = !game->data->intro.up;
		if (key == game->data->intro.g_k[6])
			game->data->fov.crouching = !game->data->fov.crouching,
			game->data->fov.jumping = 0;
		if (key == game->data->intro.g_k[5] && ((!game->data->fov.jumping && game->data->dir.ph == 0.5) || game->data->fov.crouching))
			game->data->fov.jumping = !game->data->fov.jumping,
			game->data->fov.crouching = 0;

		game->data->keys[key] = 1;
		if (key == game->data->intro.g_k[7] && game->data->use_gun > 100)
			game->data->use_gun = 0;
		if (key == SPACE)
			game->data->fov.crouching = 0;
	}
	if (key == ESC)
		game->data->mode = ANIMATE_SETT2_IN,
		set_char_to_win(game),
		game->data->intro.animate_sett = 700;
}

void	key_press_animate_sett_in(int key, t_game *game)
{
	if (key == ESC)
		game->data->mode = ANIMATE_SETT2_OUT;
}

void    key_press_animate_sett_out(int key, t_game *game)
{
	if (key == ESC)
		game->data->mode = ANIMATE_SETT2_IN;
}

int key_press(int key, void *d, t_game *game)
{
	d = NULL;
	if (game->data->mode == INTRO)
		key_press_intro(key, game);
	else if (game->data->mode == SETTING)
		key_press_setting(key, game);
	else if (game->data->mode == SETTING2)
		key_press_setting2(key, game);
	else if (game->data->mode == ANIMATE_SETT2_IN)
		key_press_animate_sett_in(key, game);
	else if (game->data->mode == ANIMATE_SETT2_OUT)
		key_press_animate_sett_out(key, game);
	else if (game->data->mode == S_CONTROL)
		key_press_control(key, game);
	else if (game->data->mode == G_MAP)
		key_press_map(key, game);
	else if (game->data->mode == GAME)
		key_press_game(key, game);
	return (0);
}
