/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   desing_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:12:20 by janhan            #+#    #+#             */
/*   Updated: 2024/05/06 15:19:23 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int    room_a(int side, double x, double y, t_game *game)
{
    int v = (((int)x / 50)% FLOOR2_SIZE_Y * ((int)y / 50)% FLOOR2_SIZE_Y) % FLOOR2_SIZE_Y;
    int w = (((int)x / 50)% FLOOR2_SIZE_X * ((int)y / 50)% FLOOR2_SIZE_X) % FLOOR2_SIZE_X;
    int v2 = (((int)x / 50)% SUPPORT_SIZE_Y * ((int)y / 50)% SUPPORT_SIZE_Y) % SUPPORT_SIZE_Y;
    int w2 = (((int)x / 50)% SUPPORT_SIZE_X + ((int)y / 50)% SUPPORT_SIZE_X) % SUPPORT_SIZE_X;
    int v3 = (((int)game->data->cord[0] / 50)% CART1_SIZE_Y + ((int)game->data->cord[1] / 50)% CART1_SIZE_Y) % CART1_SIZE_Y;
    int w3 = (((int)game->data->cord[0] / 50)% CART1_SIZE_X + ((int)game->data->cord[1] / 50)% CART1_SIZE_X) % CART1_SIZE_X;

    if (w2)
    {
        w2 = (w2 + game->data->light / 10) % SUPPORT_SIZE_X;
        w2 += !w2;
    }
    switch (side)
    {
        case 1:
            return (*(int *)(game->data->assets.addr + (((int)round(y * 10.0 * (64.0 / 500.0)) % 64 + FLOOR2_START__Y + v * 72)  * game->data->assets.line_len + ((int)round(x * 10.0 * (64.0 / 500.0)) % 64 + FLOOR2_START__X + w * 72) * (game->data->assets.bpp / 8))));
        case -1:
            return (*(int *)(game->data->assets.addr + (((int)round(y * 10.0 * (64.0 / 500.0)) % 64 + SUPPORT_START__Y + v2 * 72) * game->data->assets.line_len + ((int)round(x * 10.0 * (64.0 / 500.0)) % 64 + SUPPORT_START__X + w2 * 72) * (game->data->assets.bpp / 8))));
        default:
            return (*(int *)(game->data->assets.addr + (((int)y + CART1_START__Y + v3 * 72) * game->data->assets.line_len + ((int)round(game->data->color[1] * 10.0 * (64.0 / 500.0)) % 64 + CART1_START__X + w3 * 72) * (game->data->assets.bpp / 8))));
    }
}

int    room_b(int side, double x, double y, t_game *game)
{
    int v = (((int)x / 50)% CONCRETE_SIZE_Y * ((int)y / 50)% CONCRETE_SIZE_Y) % CONCRETE_SIZE_Y;
    int w = (((int)x / 50)% CONCRETE_SIZE_X * ((int)y / 50)% CONCRETE_SIZE_X) % CONCRETE_SIZE_X;
    int v2 = (((int)x / 50)% LIGHT_SIZE_Y * ((int)y / 50)% LIGHT_SIZE_Y) % LIGHT_SIZE_Y;
    int w2 = (((int)x / 50)% LIGHT_SIZE_X + ((int)y / 50)% LIGHT_SIZE_X) % LIGHT_SIZE_X;
    int v3 = (((int)game->data->cord[0] / 50)% CART2_SIZE_Y + ((int)game->data->cord[1] / 50)% CART2_SIZE_Y) % CART2_SIZE_Y;
    int w3 = (((int)game->data->cord[0] / 50)% CART2_SIZE_X + ((int)game->data->cord[1] / 50)% CART2_SIZE_X) % CART2_SIZE_X;

    if (w2)
        v2 = (v2 + game->data->light / 10) % LIGHT_SIZE_Y;
	if (side == -1 && !w2 && v2)
        return (0);

    switch (side)
    {
        case 1:
            return (*(int *)(game->data->assets.addr + (((int)round(y * 10.0 * (64.0 / 500.0)) % 64 + CONCRETE_START__Y + v * 72)  * game->data->assets.line_len + ((int)round(x * 10.0 * (64.0 / 500.0)) % 64 + CONCRETE_START__X + w * 72) * (game->data->assets.bpp / 8))));
        case -1:
            return (*(int *)(game->data->assets.addr + (((int)round(y * 10.0 * (64.0 / 500.0)) % 64 + LIGHT_START__Y + v2 * 72) * game->data->assets.line_len + ((int)round(x * 10.0 * (64.0 / 500.0)) % 64 + LIGHT_START__X + w2 * 72) * (game->data->assets.bpp / 8))));
        default:
            return (*(int *)(game->data->assets.addr + (((int)y + CART2_START__Y + v3 * 72) * game->data->assets.line_len + ((int)round(game->data->color[1] * 10.0 * (64.0 / 500.0)) % 64 + CART2_START__X + w3 * 72) * (game->data->assets.bpp / 8))));
    }
}

int    room_c(int side, double x, double y, t_game *game)
{
    int v = (((int)x / 50)% STEEL_SIZE_Y + ((int)y / 50)% STEEL_SIZE_Y) % STEEL_SIZE_Y;
    int w = (((int)x / 50)% STEEL_SIZE_X * 3 * ((int)y / 50)% STEEL_SIZE_X) % STEEL_SIZE_X;
    int v2 = (((int)x / 50)% SUPPORT_P_SIZE_Y * ((int)y / 50)% SUPPORT_P_SIZE_Y) % SUPPORT_P_SIZE_Y;
    int v3 = (((int)game->data->cord[0] / 50)% TECH1_2_SIZE_Y + ((int)game->data->cord[1] / 50)% TECH1_2_SIZE_Y) % TECH1_2_SIZE_Y;
    int w3 = (((int)game->data->cord[0] / 50)% TECH1_2_SIZE_X + ((int)game->data->cord[1] / 50)% TECH1_2_SIZE_X) % TECH1_2_SIZE_X;

    if (w < 2 && v == 2 && side == 1)
        return (*(int *)(game->data->assets.addr + (((int)round(y * 10.0 * (64.0 / 500.0)) % 64 + GREED_START__Y + v * 72)  * game->data->assets.line_len + ((int)round(x * 10.0 * (64.0 / 500.0)) % 64 + GREED_START__X) * (game->data->assets.bpp / 8))));
    if (side == 1)
        return (*(int *)(game->data->assets.addr + (((int)round(y * 10.0 * (64.0 / 500.0)) % 64 + STEEL_START__Y + v * 72)  * game->data->assets.line_len + ((int)round(x * 10.0 * (64.0 / 500.0)) % 64 + STEEL_START__X + w * 72) * (game->data->assets.bpp / 8))));
	if (side == -1 && v2 == 3)
        return (*(int *)(game->data->assets.addr + (((int)round(y * 10.0 * (64.0 / 500.0)) % 64 + LIGHT_START__Y + 72 * 2) * game->data->assets.line_len + ((int)round(x * 10.0 * (64.0 / 500.0)) % 64 + LIGHT_START__X) * (game->data->assets.bpp / 8))));
    if (side == -1)
        return (*(int *)(game->data->assets.addr + (((int)round(y * 10.0 * (64.0 / 500.0)) % 64 + SUPPORT_P_START__Y + v2 * 72) * game->data->assets.line_len + ((int)round(x * 10.0 * (64.0 / 500.0)) % 64 + SUPPORT_P_START__X) * (game->data->assets.bpp / 8))));
    if ((w3 && v3 >= 6) || (!w3 && v3 >= 7))
        return (*(int *)(game->data->assets.addr + (((int)y + TECH1_2_START__Y + ((v3 + w3) % 5) * 72) * game->data->assets.line_len + ((int)round(game->data->color[1] * 10.0 * (64.0 / 500.0)) % 64 + TECH1_2_START__X + 3 * 72) * (game->data->assets.bpp / 8))));
    return (*(int *)(game->data->assets.addr + (((int)y + TECH1_2_START__Y + v3 * 72) * game->data->assets.line_len + ((int)round(game->data->color[1] * 10.0 * (64.0 / 500.0)) % 64 + TECH1_2_START__X + w3 * 72) * (game->data->assets.bpp / 8))));
}

int    room_d(int side, double x, double y, t_game *game)
{
    int v = (((int)x / 50)% FLOOR3_SIZE_Y * ((int)y / 50)% FLOOR3_SIZE_Y) % FLOOR3_SIZE_Y;
    int w = (((int)x / 50)% FLOOR3_SIZE_X * ((int)y / 50)% FLOOR3_SIZE_X) % FLOOR3_SIZE_X;
    int v2 = (((int)x / 50)% SUPPORT_G_SIZE_Y * ((int)y / 50)% SUPPORT_G_SIZE_Y) % SUPPORT_G_SIZE_Y;
    int w2 = (((int)x / 50)% SUPPORT_G_SIZE_X + ((int)y / 50)% SUPPORT_G_SIZE_X) % SUPPORT_G_SIZE_X;
    int v3 = (((int)game->data->cord[0] / 50)% LAB_SIZE_Y * ((int)game->data->cord[1] / 50)% LAB_SIZE_Y) % LAB_SIZE_Y;
    int w3 = (((int)game->data->cord[0] / 50)% LAB_SIZE_X * ((int)game->data->cord[1] / 50)% LAB_SIZE_X) % LAB_SIZE_X;

    if (w2)
    {
        w2 = (w2 + game->data->light / 15) % 3;
        w2 += 2 * !w2;
    }
    if (v3 == 2 && w3 >= 2)
        v3 = 0;
    if (w3 == 4)
        v3 = (w2 + game->data->light / 3) % 2;
    if (side == 1 && v == 3)
        return (*(int *)(game->data->assets.addr + (((int)round(y * 10.0 * (64.0 / 500.0)) % 64 + FLOOR3_START__Y + (((int)(x * (game->data->light % 400 + 200) / 2) / 50) % 3) * 72)  * game->data->assets.line_len + ((int)round(x * 10.0 * (64.0 / 500.0)) % 64 + FLOOR3_START__X - 72) * (game->data->assets.bpp / 8))));
    switch (side)
    {
        case 1:
            return (*(int *)(game->data->assets.addr + (((int)round(y * 10.0 * (64.0 / 500.0)) % 64 + FLOOR3_START__Y + v * 72)  * game->data->assets.line_len + ((int)round(x * 10.0 * (64.0 / 500.0)) % 64 + FLOOR3_START__X + w * 72) * (game->data->assets.bpp / 8))));
	    case -1:
            return (*(int *)(game->data->assets.addr + (((int)round(y * 10.0 * (64.0 / 500.0)) % 64 + SUPPORT_G_START__Y + v2 * 72) * game->data->assets.line_len + ((int)round(x * 10.0 * (64.0 / 500.0)) % 64 + SUPPORT_G_START__X + w2 * 72) * (game->data->assets.bpp / 8))));
        default:
            return (*(int *)(game->data->assets.addr + (((int)y + LAB_START__Y + v3 * 72) * game->data->assets.line_len + ((int)round(game->data->color[1] * 10.0 * (64.0 / 500.0)) % 64 + LAB_START__X + w3 * 72) * (game->data->assets.bpp / 8))));
    }
}

int    room_e(int side, double x, double y, t_game *game)
{
    int v2 = (((int)x / 50)% SUPPORT_F_SIZE_Y * ((int)y / 50)% SUPPORT_F_SIZE_Y) % SUPPORT_F_SIZE_Y;
    int w2 = (((int)x / 50)% SUPPORT_F_SIZE_X + ((int)y / 50)% SUPPORT_F_SIZE_X) % SUPPORT_F_SIZE_X;
    int v3 = (((int)game->data->cord[0] / 50)% LAB_B_SIZE_Y * ((int)game->data->cord[1] / 50)% LAB_B_SIZE_Y) % LAB_B_SIZE_Y;
    int w3 = (((int)game->data->cord[0] / 50)% LAB_B_SIZE_X * ((int)game->data->cord[1] / 50)% LAB_B_SIZE_X) % LAB_B_SIZE_X;

    if (!w2 && v2)
        v2 = 0;
    if (w2 == 2)
        v2 = game->data->light % 2;
    if (v3 == 2 && w3 >= 2)
        v3 = 0;
    if (w3 == 4)
        v3 = (w2 + game->data->light / 3) % 2;

    if (side == 1 && game->data->map[(int)y / 50][(int)x / 50] == '0' && (game->data->map[(int)y / 50 - 1][(int)x / 50] != game->data->map[(int)y / 50 + 1][(int)x / 50] || game->data->map[(int)y / 50][(int)x / 50 - 1] != game->data->map[(int)y / 50][(int)x / 50 + 1]))
        return (*(int *)(game->data->assets.addr + (((int)round(y * 10.0 * (64.0 / 500.0) + game->data->light) % 64 + SLIME_START__Y)  * game->data->assets.line_len + ((int)round(x * 10.0 * (64.0 / 500.0) + game->data->light) % 64 + SLIME_START__X) * (game->data->assets.bpp / 8))));
    if (side == 1)
        return (*(int *)(game->data->assets.addr + (((int)round(y * 10.0 * (64.0 / 500.0)) % 64 + SLIME_START__Y + 72)  * game->data->assets.line_len + ((int)round(x * 10.0 * (64.0 / 500.0)) % 64 + SLIME_START__X) * (game->data->assets.bpp / 8))));
	if (side == -1 && (game->data->map[(int)y / 50 - 1][(int)x / 50] == '1' || game->data->map[(int)y / 50 + 1][(int)x / 50] == '1' || !(((int)x / 50) % 5)))
        return (*(int *)(game->data->assets.addr + (((int)round(y * 10.0 * (64.0 / 500.0)) % 64 + PIPES_START__Y) * game->data->assets.line_len + ((int)round(x * 10.0 * (64.0 / 500.0)) % 64 + PIPES_START__X ) * (game->data->assets.bpp / 8))));
    if (side == -1)
        return (*(int *)(game->data->assets.addr + (((int)round(y * 10.0 * (64.0 / 500.0)) % 64 + SUPPORT_F_START__Y + v2 * 72) * game->data->assets.line_len + ((int)round(x * 10.0 * (64.0 / 500.0)) % 64 + SUPPORT_F_START__X + w2 * 72) * (game->data->assets.bpp / 8))));
    return (*(int *)(game->data->assets.addr + (((int)y + LAB_B_START__Y + v3 * 72) * game->data->assets.line_len + ((int)round(game->data->color[1] * 10.0 * (64.0 / 500.0)) % 64 + LAB_B_START__X + w3 * 72) * (game->data->assets.bpp / 8))));
}

int    room_f(int side, double x, double y, t_game *game)
{
    int v = (((int)x / 50)% FLOOR1_SIZE_Y * ((int)y / 50)% FLOOR1_SIZE_Y) % FLOOR1_SIZE_Y;
    int w = (((int)x / 50)% FLOOR1_SIZE_X * ((int)y / 50)% FLOOR1_SIZE_X) % FLOOR1_SIZE_X;
    int v2 = (((int)x / 50)% SUPPORT_PP_SIZE_Y * ((int)y / 50)% SUPPORT_PP_SIZE_Y) % SUPPORT_PP_SIZE_Y;
    int v3 = (((int)game->data->cord[0] / 50)% TECH3_SIZE_Y + ((int)game->data->cord[1] / 50)% TECH3_SIZE_Y) % TECH3_SIZE_Y;
    int w3 = (((int)game->data->cord[0] / 50)% TECH3_SIZE_X + ((int)game->data->cord[1] / 50)% TECH3_SIZE_X) % TECH3_SIZE_X;

    if (w3 == 2)
        v3 = (v3 + 2 * (game->data->light / 6)) % 6;
    if (v == 4 && side == 1)
        return (*(int *)(game->data->assets.addr + (((int)round(y * 10.0 * (64.0 / 500.0)) % 64 + GREED_START__Y + (((int)(x * (game->data->light % 400 + 200) / 2) / 50) % 3) * 72)  * game->data->assets.line_len + ((int)round(x * 10.0 * (64.0 / 500.0)) % 64 + GREED_START__X) * (game->data->assets.bpp / 8))));
    if (side == 1)
        return (*(int *)(game->data->assets.addr + (((int)round(y * 10.0 * (64.0 / 500.0)) % 64 + FLOOR1_START__Y + v * 72)  * game->data->assets.line_len + ((int)round(x * 10.0 * (64.0 / 500.0)) % 64 + FLOOR1_START__X + w * 72) * (game->data->assets.bpp / 8))));
    if (side == -1)
        return (*(int *)(game->data->assets.addr + (((int)round(y * 10.0 * (64.0 / 500.0)) % 64 + SUPPORT_PP_START__Y + v2 * 72) * game->data->assets.line_len + ((int)round(x * 10.0 * (64.0 / 500.0)) % 64 + SUPPORT_PP_START__X) * (game->data->assets.bpp / 8))));
    if ((w3 == 3 && v3 > 1) || (!w3 && v3 > 4))
        return (*(int *)(game->data->assets.addr + (((int)y + TECH3_START__Y + ((v3 + w3) % 2) * 72) * game->data->assets.line_len + ((int)round(game->data->color[1] * 10.0 * (64.0 / 500.0)) % 64 + TECH3_START__X + 3 * 72) * (game->data->assets.bpp / 8))));
    if (w3 == 4 && v3 < 2)
        return (*(int *)(game->data->assets.addr + (((int)y + TECH3_START__Y + ((v3 + w3) % 2) * 72) * game->data->assets.line_len + ((int)round(game->data->color[1] * 10.0 * (64.0 / 500.0)) % 64 + TECH3_START__X + 8 * 72) * (game->data->assets.bpp / 8))));
    if (w3 == 4)
        return (*(int *)(game->data->assets.addr + (((int)y + TECH3_START__Y + ((v3 + game->data->light / 30 + ((v3 + game->data->light / 30) % 4 == 2)) % 4) * 72) * game->data->assets.line_len + ((int)round(game->data->color[1] * 10.0 * (64.0 / 500.0)) % 64 + TECH3_START__X + 12 * 72) * (game->data->assets.bpp / 8))));
    return (*(int *)(game->data->assets.addr + (((int)y + TECH3_START__Y + v3 * 72) * game->data->assets.line_len + ((int)round(game->data->color[1] * 10.0 * (64.0 / 500.0)) % 64 + TECH3_START__X + w3 * 72) * (game->data->assets.bpp / 8))));
}

int    room_g(int side, double x, double y, t_game *game)
{
    int v = (((int)x / 50)% TILE_SIZE_Y * ((int)y / 50)% TILE_SIZE_Y) % TILE_SIZE_Y;
    int w = (((int)x / 50)% TILE_SIZE_X * ((int)y / 50)% TILE_SIZE_X) % TILE_SIZE_X;
    int v3 = (((int)game->data->cord[0] / 50)% SZ_SIZE_Y + ((int)game->data->cord[1] / 50)% SZ_SIZE_Y) % SZ_SIZE_Y;
    int w3 = (((int)game->data->cord[0] / 50)% SZ_SIZE_X + ((int)game->data->cord[1] / 50)% SZ_SIZE_X) % SZ_SIZE_X;

    switch (side)
    {
        case 1:
            return (*(int *)(game->data->assets.addr + (((int)(y * 10.0 * (64.0 / 500.0)) % 64 + TILE_START__Y + v * 72)  * game->data->assets.line_len + ((int)(x * 10.0 * (64.0 / 500.0)) % 64 + TILE_START__X + w * 72) * (game->data->assets.bpp / 8))));
        case -1:
            return (*(int *)(game->data->img_c.addr + (((int)(y / 4 + game->data->light / 2 + game->data->light) % 500 + 500) % 500 * game->data->img_c.line_len + ((int)(x / 4 + game->data->light) % 500 + 500) % 500 * (game->data->img_c.bpp / 8))));
        default:
            return (*(int *)(game->data->assets.addr + (((int)y + SZ_START__Y + v3 * 72) * game->data->assets.line_len + ((int)round(game->data->color[1] * 10.0 * (64.0 / 500.0)) % 64 + SZ_START__X + w3 * 72) * (game->data->assets.bpp / 8))));
    }
}

int    set_design(int side, double x, double y, char design, t_game *game)
{
    int door;
    int d;

    door = (side != 3 && y >= 0 && x >= 0 && y / 50 < game->data->h_map && x / 50 < game->data->w_map[(int)y / 50] && game->data->map[(int)y / 50][(int)x / 50] == 'H' && game->data->door.c)
            || (side == 3 && game->data->door.hit_wall);
    if (game->data->door.dor && game->data->color[0] && side == 3)
    {
        int l = fabs(game->data->door.cord[0] - game->data->dir.x - 17) <= 150 && fabs(game->data->door.cord[1] - game->data->dir.y - 17) <= 150;
        if (((int)round(game->data->door.color[1] * 10.0 * (64.0 / 500.0)) % 64) - game->data->door.op * l >= 0)
        {
            d = *(unsigned int *)(game->data->door.door[0][1].addr + ((int)y * game->data->door.door[0][1].line_len + ((int)round(game->data->door.color[1] * 10.0 * (64.0 / 500.0) - game->data->door.op * l) % 64) * (game->data->door.door[0][1].bpp / 8)));
            if ((unsigned int)d < 0xff000000)
                return (d);
        }
        d = (int)round(game->data->door.color[1] * 10.0 * (64.0 / 500.0)) % 64;
        if (d + game->data->door.op * l < 64)
            return (*(int *)(game->data->door.door[0][0].addr + ((int)y * game->data->door.door[0][0].line_len + (d + game->data->door.op * l % 64) * (game->data->door.door[0][0].bpp / 8))));
        return (0xff000000);
    }
	if (door)
	{
	    switch (side)
	    {
	        case 1:
	            return (*(int *)(game->data->assets.addr + (((int)(y * 10.0 * (64.0 / 500.0)) % 64 + DOOR_START__Y)  * game->data->assets.line_len + ((int)(x * 10.0 * (64.0 / 500.0)) % 64 + DOOR_START__X) * (game->data->assets.bpp / 8))));
	        case -1:
	            return (*(int *)(game->data->assets.addr + (((int)y % 64 + DOOR_START__Y) * game->data->assets.line_len + ((int)x % 64 + DOOR_START__X) * (game->data->assets.bpp / 8))));
	        default:
	            return (0);
	    }
	}
	switch (design)
	{
		case 'A':
			return (room_a(side, x, y, game));
		case 'B':
			return (room_b(side, x, y, game));
		case 'C':
			return (room_c(side, x, y, game));
		case 'D':
			return (room_d(side, x, y, game));
		case 'E':
			return (room_e(side, x, y, game));
		case 'F':
			return (room_f(side, x, y, game));
		case 'G':
			return (room_g(side, x, y, game));
		default:
			return (0);
	}
}
