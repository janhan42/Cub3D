/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_animation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:41:32 by janhan            #+#    #+#             */
/*   Updated: 2024/05/06 15:43:23 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int get_minimap_color2(int x, int y, t_game *game)
{
    double  c;
    double  s;

    c = cos((game->data->dir.angle + game->data->map_rotation + 90 + 7.2 * (double)game->data->intro.map * (game->data->intro.map < 51)) * M_PI / 180);
    s = sin((game->data->dir.angle + game->data->map_rotation + 90 + 7.2 * (double)game->data->intro.map * (game->data->intro.map < 51)) * M_PI / 180);

    x -= 1345;
    y -= 935;

    double xnew = x * c - y * s + 1345;
    double ynew = x * s + y * c + 935;

    if (xnew < MX)
        x = (double)game->data->dir.x - fabs(MX - xnew) * (2 - game->data->map_zoom) - 16.5;
    else
        x = (double)game->data->dir.x + fabs(MX - xnew) * (2 - game->data->map_zoom) - 16.5;
    if (ynew < MY)
        y = (double)game->data->dir.y - fabs(MY - ynew) * (2 - game->data->map_zoom) - 16.5;
    else
        y = (double)game->data->dir.y + fabs(MY - ynew) * (2 - game->data->map_zoom) - 16.5;

    if (x <= 0 || y <= 0 || y / 50 >= game->data->h_map || x / 50 >= game->data->w_map[y / 50])
        return (0xff000000);
    switch (game->data->door.map[y / 50][x / 50])
    {
        case '1':
            return (*(int *)(game->data->assets.addr + (((int)(y * 64.0 / 50.0) % 64 + FLOOR2_START__Y) * game->data->assets.line_len + ((int)(x * 64.0 / 50.0) % 64 + FLOOR2_START__X) * (game->data->assets.bpp / 8))));
        case 'A':
            return (0x36454F);
        case 'B':
            return (0x231A1A);
        case 'C':
            return (0x645F5F);
        case 'D':
            return (0x393801);
        case 'E':
            if (game->data->map[(int)y / 50][(int)x / 50] == '0' && (game->data->map[(int)y / 50 - 1][(int)x / 50] != game->data->map[(int)y / 50 + 1][(int)x / 50] || game->data->map[(int)y / 50][(int)x / 50 - 1] != game->data->map[(int)y / 50][(int)x / 50 + 1]))
                return (*(int *)(game->data->assets.addr + (((int)(y * 64.0 / 50.0 + game->data->light) % 64 + 576) * game->data->assets.line_len + ((int)(x * 64.0 / 50.0 + game->data->light) % 64 + 1680) * (game->data->assets.bpp / 8))));
            else
                return (*(int *)(game->data->assets.addr + (((int)(y * 64.0 / 50.0 + game->data->light) % 64 + 648) * game->data->assets.line_len + ((int)(x * 64.0 / 50.0 + game->data->light) % 64 + 1680) * (game->data->assets.bpp / 8))));
        case 'F':
            return (0xB2BEB5);
        case 'G':
            return (0xE5E4E2);
        default:
            return (0xff000000);
    }
}

void    map_1(t_img img, int r, t_game *game)
{
    int i;
    int j;

    img.mlx_img = mlx_new_image(game->data->mlx.mlx_ptr, (121 + r) * 2, (121 + r) * 2);
    img.addr = mlx_get_data_addr(img.mlx_img, &img.bpp, &img.line_len, &img.endian);

    i = 1345 - 114 - r;
    while (++i < 1345 + 129 + r)
    {
        j = 935 - 116 - r;
        while (++j < 935 + 127 + r)
            if ((X - i + 45)*(X - i + 45) + (Y - j + 40)*(Y - j + 40) - (115 + r) * (115 + r) <= 0)
                img_pix_put(&img, i - 1345 + 113 + r, j - 935 + 115 + r, get_minimap_color2(i, j, game));
            else if ((X - i + 45)*(X - i + 45) + (Y - j  + 40)*(Y - j + 40) - (120 + r) * (120 + r) <= 0)
                img_pix_put(&img, i - 1345 + 113 + r, j - 935 + 115 + r, 0xffffff);
            else
                img_pix_put(&img, i - 1345 + 113 + r, j - 935 + 115 + r, 0xff000000);
    }
    if (game->data->intro.map < 26)
    {
        mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, img.mlx_img, RES_X - 121 * 2 - 40 - 24 * game->data->intro.map, RES_Y - 121 * 2 - 25 - 15 * game->data->intro.map);
        mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->mlx.player, RES_X - 121  - 60 - 24 * game->data->intro.map, RES_Y - 121  - 45 - 15 * game->data->intro.map);
    }
    else
    {
        mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, img.mlx_img, RES_X - 121 * 2 - 40 - 24 * 25 - r, RES_Y - 121 * 2 - 25 - 15 * 25 - r);
        mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->mlx.player, RES_X - 121  - 60 - 24 * 25, RES_Y - 121  - 45 - 15 * 25);
    }
    mlx_destroy_image(game->data->mlx.mlx_ptr, img.mlx_img);
}

int r;

void    *tmp(void *d, t_game *game)
{
    int x;
    int y;
    int i;
    int j;
    t_img *img;

    img = (t_img *)d;
    x = 280 + r;
    y = 100 + (2 * r) / 3;
    i = 1345 - 114 - r;
    while (++i < 1345)
    {
        j = 935 - 116 - r;
        while (++j < 935 + 127 + r)
            if ((X - i + 45)*(X - i + 45) + (Y - j + 40)*(Y - j + 40) - 215 * 215 <= 0)
                img_pix_put(img, i - 1345 + 113 + r, j - 935 + 115 + r, get_minimap_color2(i - game->data->mv_x, j - game->data->mv_y, game));
            else if (i > X + 45 - x / 2 && j > Y + 40 - y / 2 && i < X + 45 + x / 2 && j < Y + 40 + y / 2)
                img_pix_put(img, i - 1345 + 113 + r, j - 935 + 115 + r, get_minimap_color2(i - game->data->mv_x, j - game->data->mv_y, game));
            else if ((X - i + 45)*(X - i + 45) + (Y - j  + 40)*(Y - j + 40) - 220 * 220 <= 0)
                img_pix_put(img, i - 1345 + 113 + r, j - 935 + 115 + r, 0xffffff);
            else if (i > X + 45 - x / 2 - 5 && j > Y + 40 - y / 2 - 5 && i < X + 45 + x / 2 + 5 && j < Y + 40 + y / 2 + 5)
                img_pix_put(img, i - 1345 + 113 + r, j - 935 + 115 + r, 0xffffff);
            else
                img_pix_put(img, i - 1345 + 113 + r, j - 935 + 115 + r, 0xff000000);
    }
    return (0);
}

void    map_2(t_img img, int r, pthread_t p, t_game *game)
{
    int x;
    int y;
    int i;
    int j;

    img.mlx_img = mlx_new_image(game->data->mlx.mlx_ptr, (121 + r) * 2, (121 + r) * 2);
    img.addr = mlx_get_data_addr(img.mlx_img, &img.bpp, &img.line_len, &img.endian);
    pthread_create(&p, NULL, &tmp, &img);
    usleep(100);
    x = 280 + r;
    y = 100 + (2 * r) / 3;
    i = 1345 - 1;
    while (++i < 1345 + 129 + r)
    {
        j = 935 - 116 - r;
        while (++j < 935 + 127 + r)
            if ((X - i + 45)*(X - i + 45) + (Y - j + 40)*(Y - j + 40) - 215 * 215 <= 0)
                img_pix_put(&img, i - 1345 + 113 + r, j - 935 + 115 + r, get_minimap_color2(i - game->data->mv_x, j - game->data->mv_y));
            else if (i > X + 45 - x / 2 && j > Y + 40 - y / 2 && i < X + 45 + x / 2 && j < Y + 40 + y / 2)
                img_pix_put(&img, i - 1345 + 113 + r, j - 935 + 115 + r, get_minimap_color2(i - game->data->mv_x, j - game->data->mv_y));
            else if ((X - i + 45)*(X - i + 45) + (Y - j  + 40)*(Y - j + 40) - 220 * 220 <= 0)
                img_pix_put(&img, i - 1345 + 113 + r, j - 935 + 115 + r, 0xffffff);
            else if (i > X + 45 - x / 2 - 5 && j > Y + 40 - y / 2 - 5 && i < X + 45 + x / 2 + 5 && j < Y + 40 + y / 2 + 5)
                img_pix_put(&img, i - 1345 + 113 + r, j - 935 + 115 + r, 0xffffff);
            else
                img_pix_put(&img, i - 1345 + 113 + r, j - 935 + 115 + r, 0xff000000);
    }
    pthread_join(p, NULL);
    if (game->data->intro.map < 26)
    {
        mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, img.mlx_img, RES_X - 121 * 2 - 40 - 24 * game->data->intro.map, RES_Y - 121 * 2 - 25 - 15 * game->data->intro.map);
        mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->mlx.player, RES_X - 121  - 60 - 24 * game->data->intro.map, RES_Y - 121  - 45 - 15 * game->data->intro.map);
    }
    else
    {
        mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, img.mlx_img, RES_X - 121 * 2 - 40 - 24 * 25 - r, RES_Y - 121 * 2 - 25 - 15 * 25 - r);
        if (!game->data->mv_x && !game->data->mv_y)
            mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->mlx.player, RES_X - 121  - 60 - 24 * 25 + game->data->mv_x, RES_Y - 121  - 45 - 15 * 25 + game->data->mv_y);
    }
    mlx_destroy_image(game->data->mlx.mlx_ptr, img.mlx_img);
}

void    map_appending(t_game *game)
{
    pthread_t p;
    t_img img;

    p = NULL;
    img.mlx_img = NULL;
    r = 4 * (game->data->intro.map - 25) * (game->data->intro.map > 25) + 12 * (game->data->intro.map - 50) * (game->data->intro.map > 50);
    if (game->data->intro.map < 51)
        map_1(img, r, game);
    else
        map_2(img, r, p, game);
}
