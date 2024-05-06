/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_press.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:44:52 by janhan            #+#    #+#             */
/*   Updated: 2024/05/06 15:39:23 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void    mouse_press_intro(int key, t_game *game)
{
    if (key == LEFT_CLICK)
        game->data->mouse.on_click = 1;
}

void    mouse_press_setting(int key, int x, int y, t_game *game)
{
    if (key == LEFT_CLICK)
    {
        if (game->data->mode == SETTING)
        {
            if (x >= (RES_X - game->data->intro.start.x) / 2 && y >= (RES_Y - game->data->intro.start.y) / 2 - RES_Y / 6 && x < (RES_X + game->data->intro.start.x) / 2 && y < (RES_Y + game->data->intro.start.y) / 2 - RES_Y / 6)
                game->data->mouse.on_clk[0] = 1;
            if (x >= (RES_X - game->data->intro.sett.x) / 2 && y >= (RES_Y - game->data->intro.sett.y) / 2 - RES_Y / 12 && x < (RES_X + game->data->intro.sett.x) / 2 && y < (RES_Y + game->data->intro.sett.y) / 2 - RES_Y / 12)
                game->data->mouse.on_clk[1] = 1;
            if (x >= (RES_X - game->data->intro.exit.x) / 2 && y >= (RES_Y - game->data->intro.exit.y) / 2 && x < (RES_X + game->data->intro.exit.x) / 2 && y < (RES_Y + game->data->intro.exit.y) / 2)
                game->data->mouse.on_clk[2] = 1;
        }
        if (game->data->mode == SETTING2)
        {
            if (x >= (RES_X - game->data->intro.cont.x) / 2 && y >= (RES_Y - game->data->intro.cont.y) / 2 - RES_Y / 6 && x < (RES_X + game->data->intro.cont.x) / 2 && y < (RES_Y + game->data->intro.cont.y) / 2 - RES_Y / 6)
                game->data->mouse.on_clk[3] = 1;
            if (x >= (RES_X - game->data->intro.restart.x) / 2 && y >= (RES_Y - game->data->intro.restart.y) / 2 - RES_Y / 12 && x < (RES_X + game->data->intro.restart.x) / 2 && y < (RES_Y + game->data->intro.restart.y) / 2 - RES_Y / 12)
                game->data->mouse.on_clk[4] = 1;
            if (x >= (RES_X - game->data->intro.sett.x) / 2 && y >= (RES_Y - game->data->intro.sett.y) / 2 && x < (RES_X + game->data->intro.sett.x) / 2 && y < (RES_Y + game->data->intro.sett.y) / 2)
                game->data->mouse.on_clk[1] = 1;
            if (x >= (RES_X - game->data->intro.exit.x) / 2 && y >= (RES_Y - game->data->intro.exit.y) / 2 + RES_Y / 12 && x < (RES_X + game->data->intro.exit.x) / 2 && y < (RES_Y + game->data->intro.exit.y) / 2 + RES_Y / 12)
                game->data->mouse.on_clk[2] = 1;
        }
        if (game->data->mode == S_CONTROL)
        {
            if (x >= RES_X / 2 - 225 && y >= RES_Y - 100 && x < RES_X / 2 - 75 && y < RES_Y - 40)
                game->data->mouse.on_clk[5] = 1;
            if (x >= RES_X / 2 + 75 && y >= RES_Y - 100 && x < RES_X / 2 + 225 && y < RES_Y - 40)
                game->data->mouse.on_clk[6] = 1;
        }
    }
}


void    mouse_press_control(int key, int x, int y, t_game *game)
{
    int i;
    int inc_y;
    int pos;

    pos = -1;
    i = -1;
        while (++i < 12)
            if (game->data->intro.on_clk[i + 4])
                pos = i;
    if (key == LEFT_CLICK && pos == -1)
    {
        i = 5;
        inc_y = 280;
        pos = 3 * (x > 390 && x < 436 && y > 120 && y < 160)
            + 4 * (x > 564 && x < 610 && y > 120 && y < 160);
        while (i < 16)
        {
            pos += i++ * (x - 100 > 0 && x - 100 < 500 && y - inc_y > -25 && y - inc_y < 65);
            if (i < 16)
                pos += i++ * (x - 800 > 0 && x - 800 < 500 && y - inc_y > -25 && y - inc_y < 65);
            inc_y += 120;
        }
        if (pos && !game->data->intro.on_clk[pos])
        {
            if (pos == 3 || pos == 4)
                game->data->intro.g_k[0] = !game->data->intro.g_k[0];
            else
                game->data->intro.on_clk[pos] = 3;
            game->data->sound.click = 1;
        }
        i = 0;
        while (++i < 15)
            game->data->intro.on_clk[(pos + i) % 16] = 0;
    }
    else if (key == LEFT_CLICK && key_not_in_use(M_LEFT_CLICK, game))
        game->data->intro.on_clk[pos + 4] = 0,
        game->data->intro.g_k[pos] = M_LEFT_CLICK;
    else if (key == RIGHT_CLICK && key_not_in_use(M_RIGHT_CLICK, game))
        game->data->intro.on_clk[pos + 4] = 0,
        game->data->intro.g_k[pos] = M_RIGHT_CLICK;
    else
        game->data->intro.on_clk[pos + 4] = 0;
    if (key == LEFT_CLICK && x >= 1100 - 25 && y >= 75 && x <= 1300 && y <= 115)
    {
        game->data->intro.volume = x - 1100 + 12;
        if (game->data->intro.volume > 200)
            game->data->intro.volume = 200;
        if (game->data->intro.volume < 0)
            game->data->intro.volume = 0;
        paint_color(&game->data->intro.vol[1], 0xff3333, 25, 40);
        paint_color(&game->data->intro.vol[0], 0xB2BEB5, 200, 10);
        paint_color(&game->data->intro.vol[0], 0xff0000, game->data->intro.volume, 10);
        game->data->intro.vol_click = 1;
    }
    if (key == LEFT_CLICK && x >= 1025 && y >= 70 && x <= 1075 && y <= 120)
    {
        game->data->sound.click = 1;
        game->data->intro.vol_click = 1;
        game->data->intro.volume = !game->data->intro.volume * 100;
        paint_color(&game->data->intro.vol[0], 0xB2BEB5, 200, 10);
        paint_color(&game->data->intro.vol[0], 0xff0000, game->data->intro.volume, 10);
    }

    if (key == LEFT_CLICK && x >= 1100 - 25 && y >= 170 && x <= 1300 && y <= 210)
    {
        game->data->intro.light = x - 1100 + 12;
        if (game->data->intro.light > 200)
            game->data->intro.light = 200;
        if (game->data->intro.light < 0)
            game->data->intro.light = 0;
        paint_color(&game->data->intro.lgt[1], 0xff3333, 25, 40);
        paint_color(&game->data->intro.lgt[0], 0xB2BEB5, 200, 10);
        paint_color(&game->data->intro.lgt[0], 0xff0000, game->data->intro.light, 10);
        game->data->intro.lgt_click = 1;
    }
    if (key == LEFT_CLICK && x >= 1025 && y >= 165 && x <= 1075 && y <= 215)
    {
        game->data->sound.click = 1;
        game->data->intro.lgt_click = 1;
        game->data->intro.light = !game->data->intro.light * 200;
        paint_color(&game->data->intro.lgt[0], 0xB2BEB5, 200, 10);
        paint_color(&game->data->intro.lgt[0], 0xff0000, game->data->intro.light, 10);
    }
    mouse_press_setting(key, x, y, game);
}


void    mouse_press_game(int key, t_game *game)
{
    if (key == SCROLL_UP && !game->data->keys[game->data->intro.g_k[8]])
        game->data->objects.w++,
        game->data->sound.scroll = 1,
        game->data->keys[1000 - SCROLL_UP - 1] = 1;
    else if (key == SCROLL_UP && game->data->zoom > 0)
        game->data->zoom--;

    if (!game->data->keys[game->data->intro.g_k[8]] && key == SCROLL_DOWN && !game->data->keys[game->data->intro.g_k[8]])
        game->data->objects.w--,
        game->data->sound.scroll = 1,
        game->data->keys[1000 - SCROLL_DOWN - 1] = 1;
    else if (key == SCROLL_DOWN && game->data->zoom < 20)
        game->data->zoom++;

    if (game->data->objects.w < 0)
        game->data->objects.w = 26;
    if (game->data->objects.w > 26)
        game->data->objects.w = 0;

    if (game->data->intro.g_k[7] == M_LEFT_CLICK && key == LEFT_CLICK)
        game->data->keys[game->data->intro.g_k[7]] = 1;
    if (game->data->intro.g_k[8] == M_RIGHT_CLICK && key == RIGHT_CLICK)
        game->data->keys[game->data->intro.g_k[8]] = 1;
    if (game->data->intro.g_k[7] == M_LEFT_CLICK && key == LEFT_CLICK && game->data->use_gun > 100)
        game->data->use_gun = 0,
        game->data->gun[game->data->objects.w].frame = 0;
}

void    mouse_press_map(int key, t_game *game)
{
    if (game->data->intro.g_k[7] == M_LEFT_CLICK && key == LEFT_CLICK)
        game->data->keys[game->data->intro.g_k[7]] = 1;
    if (game->data->intro.g_k[8] == M_RIGHT_CLICK && key == RIGHT_CLICK)
        game->data->keys[game->data->intro.g_k[8]] = 1;

    if (key == SCROLL_UP && game->data->map_zoom > -1.9)
        game->data->map_zoom -= 0.1;
    if (key == SCROLL_DOWN && game->data->map_zoom < 1.9)
        game->data->map_zoom += 0.1;
}

int	mouse_press(int key, int x, int y, void *w, t_game *game)
{
	w = NULL;
	if (game->data->mode == INTRO)
		mouse_press_intro(key, game);
	else if (game->data->mode == SETTING || game->data->mode == SETTING2)
		mouse_press_setting(key, x, y, game);
	else if (game->data->mode == S_CONTROL)
		mouse_press_control(key, x, y, game);
	else if (game->data->mode == G_MAP)
		mouse_press_map(key, game);
	else if (game->data->mode == GAME && game->data->objects.health > 0)
		mouse_press_game(key, game);
	return (0);
}
