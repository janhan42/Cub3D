/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:35:05 by janhan            #+#    #+#             */
/*   Updated: 2024/05/06 14:43:20 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void    mouse_move_intro(int x, int y, t_game *game)
{
    if (x >= (RES_X - 498) / 2 + 35 && y >= (RES_Y + 280) / 2 + 70 && x < (RES_X + 498) / 2 + 35 && y < (RES_Y + 280) / 2 + 70 + 50)
        game->data->mouse.hover = 1;
    else
        game->data->mouse.hover = 0;
}

void    mouse_move_setting(int x, int y, t_game *game)
{
    int p;
    int i;

    p = -1;
    if (game->data->mode == SETTING)
    {
        if (!game->data->mouse.on_hov[0] && x >= (RES_X - game->data->intro.start.x) / 2 && y >= (RES_Y - game->data->intro.start.y) / 2 - RES_Y / 6 && x < (RES_X + game->data->intro.start.x) / 2 && y < (RES_Y + game->data->intro.start.y) / 2 - RES_Y / 6)
            game->data->sound.hover = 1,
            p = 0;
        if (!game->data->mouse.on_hov[1] && x >= (RES_X - game->data->intro.sett.x) / 2 && y >= (RES_Y - game->data->intro.sett.y) / 2 - RES_Y / 12 && x < (RES_X + game->data->intro.sett.x) / 2 && y < (RES_Y + game->data->intro.sett.y) / 2 - RES_Y / 12)
            game->data->sound.hover = 1,
            p = 1;
        if (!game->data->mouse.on_hov[2] && x >= (RES_X - game->data->intro.exit.x) / 2 && y >= (RES_Y - game->data->intro.exit.y) / 2 && x < (RES_X + game->data->intro.exit.x) / 2 && y < (RES_Y + game->data->intro.exit.y) / 2)
            game->data->sound.hover = 1,
            p = 2;
    }
    if (game->data->mode == SETTING2)
    {
        if (!game->data->mouse.on_hov[3] && x >= (RES_X - game->data->intro.cont.x) / 2 && y >= (RES_Y - game->data->intro.cont.y) / 2 - RES_Y / 6 && x < (RES_X + game->data->intro.cont.x) / 2 && y < (RES_Y + game->data->intro.cont.y) / 2 - RES_Y / 6)
            game->data->sound.hover = 1,
            p = 3;
        if (!game->data->mouse.on_hov[4] && x >= (RES_X - game->data->intro.restart.x) / 2 && y >= (RES_Y - game->data->intro.restart.y) / 2 - RES_Y / 12 && x < (RES_X + game->data->intro.restart.x) / 2 && y < (RES_Y + game->data->intro.restart.y) / 2 - RES_Y / 12)
            game->data->sound.hover = 1,
            p = 4;
        if (!game->data->mouse.on_hov[1] && x >= (RES_X - game->data->intro.sett.x) / 2 && y >= (RES_Y - game->data->intro.sett.y) / 2 && x < (RES_X + game->data->intro.sett.x) / 2 && y < (RES_Y + game->data->intro.sett.y) / 2)
            game->data->sound.hover = 1,
            p = 1;
        if (!game->data->mouse.on_hov[2] && x >= (RES_X - game->data->intro.exit.x) / 2 && y >= (RES_Y - game->data->intro.exit.y) / 2 + RES_Y / 12 && x < (RES_X + game->data->intro.exit.x) / 2 && y < (RES_Y + game->data->intro.exit.y) / 2 + RES_Y / 12)
            game->data->sound.hover = 1,
            p = 2;
    }
    if (game->data->mode == S_CONTROL)
    {
        if (x >= RES_X / 2 - 225 && y >= RES_Y - 100 && x < RES_X / 2 - 75 && y < RES_Y - 40)
            game->data->sound.hover = !game->data->mouse.on_hov[5],
            p = 5;
        else if (x >= RES_X / 2 + 75 && y >= RES_Y - 100 && x < RES_X / 2 + 225 && y < RES_Y - 40)
            game->data->sound.hover = !game->data->mouse.on_hov[6],
            p = 6;
        else
            p = 0;
    }
    if (p != -1)
    {
        game->data->mouse.on_hov[p] = 1;
        i = 0;
        while (++i < 7)
            game->data->mouse.on_hov[(p + i) % 7] = 0;
    }
    game->data->mouse.x = x;
    game->data->mouse.y = y;
}

void    mouse_move_control(int x, int y, t_game *game)
{
    int i;
    int inc_y;
    int pos;

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
    if (pos && !game->data->intro.on_hov[pos])
        game->data->sound.hover = 1,
        game->data->intro.on_hov[pos] = 1;
    i = 1;
    while (++i < 15)
        game->data->intro.on_hov[(pos + i) % 16] = 0;
    if (game->data->intro.vol_click)
    {
        game->data->intro.volume = x - 1100 + 12;
        if (game->data->intro.volume > 200)
            game->data->intro.volume = 200;
        if (game->data->intro.volume < 0)
            game->data->intro.volume = 0;
        paint_color(&game->data->intro.vol[0], 0xB2BEB5, 200, 10);
        paint_color(&game->data->intro.vol[0], 0xff0000, game->data->intro.volume, 10);
    }
    if (game->data->intro.lgt_click)
    {
        game->data->intro.light = x - 1100 + 12;
        if (game->data->intro.light > 200)
            game->data->intro.light = 200;
        if (game->data->intro.light < 0)
            game->data->intro.light = 0;
        paint_color(&game->data->intro.lgt[0], 0xB2BEB5, 200, 10);
        paint_color(&game->data->intro.lgt[0], 0xff0000, game->data->intro.light, 10);
    }
    mouse_move_setting(x, y, game);
}

void    mouse_move_game(int x, int y, t_game *game)
{
    if (game->data->mouse.x == 10000)
    {
        game->data->mouse.x = x,
        game->data->mouse.y = y;
        return ;
    }

    if (game->data->intro.g_k[0])
    {
        int i = 0;
        if (game->data->mouse.x - x > 1)
            while (game->data->mouse.x - x - i++ > 1)
                left_angle(game, game->data),
                i += 10;
        else if (x - game->data->mouse.x > 1)
            while (x - game->data->mouse.x - i++ > 1)
                right_angle(game, game->data),
                i += 10;
        if (x >= 0 && x <= RES_X)
            game->data->keys[RIGHT] = 0,
            game->data->keys[LEFT] = 0;
        if (game->data->mouse.y - y > 1)
            game->data->c -= 25 * (game->data->mouse.y - y) / 5 * (-game->data->c + 25 * (game->data->mouse.y - y) / 5 < RES_Y - 200);
        else if (y - game->data->mouse.y > 1)
            game->data->c += 25 * (y - game->data->mouse.y) / 5 * (game->data->c + 25 * (y - game->data->mouse.y) / 5 < RES_Y - 200);

        if (y >= 0 && y <= RES_Y)
            game->data->keys[UP] = 0,
            game->data->keys[DOWN] = 0;
    }
    if (x >= RES_X || x <= 0 || y >= RES_Y || y <= 0)
    {
        mlx_mouse_move(game->data->mlx.win_ptr, 900, 1000);
        game->data->mouse.x = 900;
        game->data->mouse.y = 1000;
        return ;
    }
    else
        game->data->mouse.x = x,
        game->data->mouse.y = y;
}

void    inc_get_minimap_color2(int x, int y, int angle, t_game *game)
{
    double  c;
    double  s;
    double  c1;
    double  s1;

    c = cos((game->data->dir.angle + angle + 90 + 7.2 * (double)game->data->intro.map * (game->data->intro.map < 51)) * M_PI / 180);
    s = sin((game->data->dir.angle + angle + 90 + 7.2 * (double)game->data->intro.map * (game->data->intro.map < 51)) * M_PI / 180);
    c1 = cos((game->data->dir.angle + 90 + 7.2 * (double)game->data->intro.map * (game->data->intro.map < 51)) * M_PI / 180);
    s1 = sin((game->data->dir.angle + 90 + 7.2 * (double)game->data->intro.map * (game->data->intro.map < 51)) * M_PI / 180);

    x -= 1345;
    y -= 935;

    double xnew = x * c - y * s + 1345;
    double ynew = x * s + y * c + 935;

    double old_x = x * c1 - y * s1 + 1345;
    double old_y = x * s1 + y * c1 + 935;

    if (xnew < MX)
        x = (double)game->data->dir.x - fabs(MX - xnew) * (2 - game->data->map_zoom) - 16.5;
    else
        x = (double)game->data->dir.x + fabs(MX - xnew) * (2 - game->data->map_zoom) - 16.5;
    if (ynew < MY)
        y = (double)game->data->dir.y - fabs(MY - ynew) * (2 - game->data->map_zoom) - 16.5;
    else
        y = (double)game->data->dir.y + fabs(MY - ynew) * (2 - game->data->map_zoom) - 16.5;

    if (old_x < MX)
        old_x = (double)game->data->dir.x - fabs(MX - xnew) * (2 - game->data->map_zoom) - 16.5;
    else
        old_x = (double)game->data->dir.x + fabs(MX - xnew) * (2 - game->data->map_zoom) - 16.5;
    if (old_y < MY)
        old_y = (double)game->data->dir.y - fabs(MY - ynew) * (2 - game->data->map_zoom) - 16.5;
    else
        old_y = (double)game->data->dir.y + fabs(MY - ynew) * (2 - game->data->map_zoom) - 16.5;

    game->data->mv_x -= (old_x - x) * 7 * cos((game->data->dir.angle - angle + 90 + 7.2 * (double)game->data->intro.map * (game->data->intro.map < 51)) * M_PI / 180);
    game->data->mv_y -= (old_y - y) * 7 * sin((game->data->dir.angle - angle + 90 + 7.2 * (double)game->data->intro.map * (game->data->intro.map < 51)) * M_PI / 180);
}


void    mouse_move_map(int x, int y, t_game *game)
{
    if (game->data->keys[game->data->intro.g_k[7]])
        game->data->mv_x += (x - game->data->mouse.x) * 3,
        game->data->mv_y += (y - game->data->mouse.y) * 3;
    if (game->data->keys[game->data->intro.g_k[8]])
    {
        inc_get_minimap_color2(1345, 935, x - game->data->mouse.x, game);
        game->data->map_rotation += x - game->data->mouse.x;
    }
}

int mouse_move(int x, int y, void *w, t_game *game)
{
    w = NULL;

    if (game->data->mode == INTRO)
        mouse_move_intro(x, y, game);
    else if (game->data->mode == SETTING || game->data->mode == SETTING2)
        mouse_move_setting(x, y, game);
    else if (game->data->mode == S_CONTROL)
        mouse_move_control(x, y, game);
    else if (game->data->mode == G_MAP)
        mouse_move_map(x, y, game);
    if (game->data->mode == GAME && game->data->objects.health > 0)
        mouse_move_game(x, y, game);
    else
        game->data->mouse.x = x,
        game->data->mouse.y = y;
    return (0);
}
