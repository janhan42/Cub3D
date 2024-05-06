/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:52:32 by janhan            #+#    #+#             */
/*   Updated: 2024/05/04 19:26:03 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"
#include "includes/struct.h"
#include "mlx/mlx.h"
#include "srcs/libft/libft.h"
#include <sys/_types/_null.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <pthread.h>

int	get_img_color(t_img *img, int x, int y)
{
	return (*(int *)(img->addr + (y * img->line_len + x * (img->bpp / 8))));
}

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char    *pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}
void	paint_img(t_game *game, t_img *img, char *path, int res_x, int res_y)
{
	t_img	img2;
	int		x;
	int		y;

	img2.mlx_img = mlx_xpm_file_to_image(game->data->mlx.mlx_ptr, path, &img2.x, &img2.y);
	img2.addr = mlx_get_data_addr(img2.mlx_img, &img2.bpp, &img2.line_len, &img2.endian);
	y = -1;
	while (++y < res_y)
	{
		x = -1;
		while (++x < res_x)
			img_pix_put(img, x, y, get_img_color(&img2, (int)((double)x * ((double)img2.x / (double)res_x)), (int)((double)y * ((double)img2.y / (double)res_y))));
	}
	mlx_destroy_image(game->data->mlx.mlx_ptr, img2.mlx_img);
}

void    paint_color(t_img *img, int color, int x_s, int y_s)
{
	int x;
	int y;

	y = -1;
	while (++y < y_s)
	{
		x = -1;
		while (++x < x_s)
				img_pix_put(img, x, y, color);
	}
}

void	set_minimap(t_game *game)
{
	int	w;
	int	h;

	pthread_t t;
	pthread_t t2;

	w = 50;
	h = 50;

	game->data->mlx.mlx_ptr = mlx_init();
	game->data->mlx.win_ptr = mlx_new_window(game->data->mlx.mlx_ptr, RES_X, RES_Y, "map");

	game->data->img.mlx_img = mlx_new_image(game->data->mlx.mlx_ptr, RES_X, RES_Y);
	game->data->img.addr = mlx_get_data_addr(game->data->img.mlx_img, &game->data->img.bpp, &game->data->img.line_len, &game->data->img.endian);
	game->data->img2.mlx_img = mlx_new_image(game->data->mlx.mlx_ptr, RES_X, RES_Y);
	game->data->img2.addr = mlx_get_data_addr(game->data->img.mlx_img, &game->data->img2.bpp, &game->data->img2.line_len, &game->data->img2.endian);
	game->data->img3.mlx_img = mlx_new_image(game->data->mlx.mlx_ptr, RES_X / 3, RES_Y);
	game->data->img3.addr = mlx_get_data_addr(game->data->img.mlx_img, &game->data->img3.bpp, &game->data->img3.line_len, &game->data->img3.endian);

	game->data->img_c.mlx_img = mlx_xpm_file_to_image(game->data->mlx.mlx_ptr, "img/ceill.xpm", &w, &h);
	game->data->assets.mlx_img = mlx_xpm_file_to_image(game->data->mlx.mlx_ptr, "img/textures.xpm", &w, &h);
	game->data->guns.mlx_img = mlx_xpm_file_to_image(game->data->mlx.mlx_ptr, "img/weapons.xpm", &w, &h);
	game->data->blood_hit.mlx_img = mlx_xpm_file_to_image(game->data->mlx.mlx_ptr, "img/blood_hiy.xpm", &w, &h);
	game->data->blood_hit2.mlx_img = mlx_xpm_file_to_image(game->data->mlx.mlx_ptr, "img/blood_hit.xpm", &w, &h);

	game->data->img_c.addr = mlx_get_data_addr(game->data->img_c.mlx_img, &game->data->img_c.bpp, &game->data->img_c.line_len, &game->data->img_c.endian);
    game->data->assets.addr = mlx_get_data_addr(game->data->assets.mlx_img, &game->data->assets.bpp, &game->data->assets.line_len, &game->data->assets.endian);
    game->data->guns.addr = mlx_get_data_addr(game->data->guns.mlx_img, &game->data->guns.bpp, &game->data->guns.line_len, &game->data->guns.endian);
    game->data->blood_hit.addr = mlx_get_data_addr(game->data->blood_hit.mlx_img, &game->data->blood_hit.bpp, &game->data->blood_hit.line_len, &game->data->blood_hit.endian);
    game->data->blood_hit2.addr = mlx_get_data_addr(game->data->blood_hit2.mlx_img, &game->data->blood_hit2.bpp, &game->data->blood_hit2.line_len, &game->data->blood_hit2.endian);


    game->data->mlx.player = mlx_xpm_file_to_image(game->data->mlx.mlx_ptr, "img/cursor/4.xpm", &w, &h);

    game->data->objects.time[0].mlx_img = mlx_xpm_file_to_image(game->data->mlx.mlx_ptr, "img/num/0.xpm", &w, &h);
    game->data->objects.time[1].mlx_img = mlx_xpm_file_to_image(game->data->mlx.mlx_ptr, "img/num/1.xpm", &w, &h);
    game->data->objects.time[2].mlx_img = mlx_xpm_file_to_image(game->data->mlx.mlx_ptr, "img/num/2.xpm", &w, &h);
    game->data->objects.time[3].mlx_img = mlx_xpm_file_to_image(game->data->mlx.mlx_ptr, "img/num/3.xpm", &w, &h);
    game->data->objects.time[4].mlx_img = mlx_xpm_file_to_image(game->data->mlx.mlx_ptr, "img/num/4.xpm", &w, &h);
    game->data->objects.time[5].mlx_img = mlx_xpm_file_to_image(game->data->mlx.mlx_ptr, "img/num/5.xpm", &w, &h);
    game->data->objects.time[6].mlx_img = mlx_xpm_file_to_image(game->data->mlx.mlx_ptr, "img/num/6.xpm", &w, &h);
    game->data->objects.time[7].mlx_img = mlx_xpm_file_to_image(game->data->mlx.mlx_ptr, "img/num/7.xpm", &w, &h);
    game->data->objects.time[8].mlx_img = mlx_xpm_file_to_image(game->data->mlx.mlx_ptr, "img/num/8.xpm", &w, &h);
    game->data->objects.time[9].mlx_img = mlx_xpm_file_to_image(game->data->mlx.mlx_ptr, "img/num/9.xpm", &w, &h);

    game->data->objects.time[0].addr = mlx_get_data_addr(game->data->objects.time[0].mlx_img, &game->data->objects.time[0].bpp, &game->data->objects.time[0].line_len, &game->data->objects.time[0].endian);
    game->data->objects.time[1].addr = mlx_get_data_addr(game->data->objects.time[1].mlx_img, &game->data->objects.time[1].bpp, &game->data->objects.time[1].line_len, &game->data->objects.time[1].endian);
    game->data->objects.time[2].addr = mlx_get_data_addr(game->data->objects.time[2].mlx_img, &game->data->objects.time[2].bpp, &game->data->objects.time[2].line_len, &game->data->objects.time[2].endian);
    game->data->objects.time[3].addr = mlx_get_data_addr(game->data->objects.time[3].mlx_img, &game->data->objects.time[3].bpp, &game->data->objects.time[3].line_len, &game->data->objects.time[3].endian);
    game->data->objects.time[4].addr = mlx_get_data_addr(game->data->objects.time[4].mlx_img, &game->data->objects.time[4].bpp, &game->data->objects.time[4].line_len, &game->data->objects.time[4].endian);
    game->data->objects.time[5].addr = mlx_get_data_addr(game->data->objects.time[5].mlx_img, &game->data->objects.time[5].bpp, &game->data->objects.time[5].line_len, &game->data->objects.time[5].endian);
    game->data->objects.time[6].addr = mlx_get_data_addr(game->data->objects.time[6].mlx_img, &game->data->objects.time[6].bpp, &game->data->objects.time[6].line_len, &game->data->objects.time[6].endian);
    game->data->objects.time[7].addr = mlx_get_data_addr(game->data->objects.time[7].mlx_img, &game->data->objects.time[7].bpp, &game->data->objects.time[7].line_len, &game->data->objects.time[7].endian);
    game->data->objects.time[8].addr = mlx_get_data_addr(game->data->objects.time[8].mlx_img, &game->data->objects.time[8].bpp, &game->data->objects.time[8].line_len, &game->data->objects.time[8].endian);
    game->data->objects.time[9].addr = mlx_get_data_addr(game->data->objects.time[9].mlx_img, &game->data->objects.time[9].bpp, &game->data->objects.time[9].line_len, &game->data->objects.time[9].endian);


    game->data->nums[0].mlx_img = mlx_new_image(game->data->mlx.mlx_ptr, 15, 23);
    game->data->nums[1].mlx_img = mlx_new_image(game->data->mlx.mlx_ptr, 15, 23);
    game->data->nums[2].mlx_img = mlx_new_image(game->data->mlx.mlx_ptr, 15, 23);
    game->data->nums[3].mlx_img = mlx_new_image(game->data->mlx.mlx_ptr, 15, 23);
    game->data->nums[4].mlx_img = mlx_new_image(game->data->mlx.mlx_ptr, 15, 23);
    game->data->nums[5].mlx_img = mlx_new_image(game->data->mlx.mlx_ptr, 15, 23);
    game->data->nums[6].mlx_img = mlx_new_image(game->data->mlx.mlx_ptr, 15, 23);
    game->data->nums[7].mlx_img = mlx_new_image(game->data->mlx.mlx_ptr, 15, 23);
    game->data->nums[8].mlx_img = mlx_new_image(game->data->mlx.mlx_ptr, 15, 23);
    game->data->nums[9].mlx_img = mlx_new_image(game->data->mlx.mlx_ptr, 15, 23);
    game->data->nums[0].addr = mlx_get_data_addr(game->data->nums[0].mlx_img, &game->data->nums[0].bpp, &game->data->nums[0].line_len, &game->data->nums[0].endian);
    game->data->nums[1].addr = mlx_get_data_addr(game->data->nums[1].mlx_img, &game->data->nums[1].bpp, &game->data->nums[1].line_len, &game->data->nums[1].endian);
    game->data->nums[2].addr = mlx_get_data_addr(game->data->nums[2].mlx_img, &game->data->nums[2].bpp, &game->data->nums[2].line_len, &game->data->nums[2].endian);
    game->data->nums[3].addr = mlx_get_data_addr(game->data->nums[3].mlx_img, &game->data->nums[3].bpp, &game->data->nums[3].line_len, &game->data->nums[3].endian);
    game->data->nums[4].addr = mlx_get_data_addr(game->data->nums[4].mlx_img, &game->data->nums[4].bpp, &game->data->nums[4].line_len, &game->data->nums[4].endian);
    game->data->nums[5].addr = mlx_get_data_addr(game->data->nums[5].mlx_img, &game->data->nums[5].bpp, &game->data->nums[5].line_len, &game->data->nums[5].endian);
    game->data->nums[6].addr = mlx_get_data_addr(game->data->nums[6].mlx_img, &game->data->nums[6].bpp, &game->data->nums[6].line_len, &game->data->nums[6].endian);
    game->data->nums[7].addr = mlx_get_data_addr(game->data->nums[7].mlx_img, &game->data->nums[7].bpp, &game->data->nums[7].line_len, &game->data->nums[7].endian);
    game->data->nums[8].addr = mlx_get_data_addr(game->data->nums[8].mlx_img, &game->data->nums[8].bpp, &game->data->nums[8].line_len, &game->data->nums[8].endian);
    game->data->nums[9].addr = mlx_get_data_addr(game->data->nums[9].mlx_img, &game->data->nums[9].bpp, &game->data->nums[9].line_len, &game->data->nums[9].endian);
    paint_img(game, &game->data->nums[0], "img/num/0.xpm", 15, 23);
    paint_img(game, &game->data->nums[1], "img/num/1.xpm", 15, 23);
    paint_img(game, &game->data->nums[2], "img/num/2.xpm", 15, 23);
    paint_img(game, &game->data->nums[3], "img/num/3.xpm", 15, 23);
    paint_img(game, &game->data->nums[4], "img/num/4.xpm", 15, 23);
    paint_img(game, &game->data->nums[5], "img/num/5.xpm", 15, 23);
    paint_img(game, &game->data->nums[6], "img/num/6.xpm", 15, 23);
    paint_img(game, &game->data->nums[7], "img/num/7.xpm", 15, 23);
    paint_img(game, &game->data->nums[8], "img/num/8.xpm", 15, 23);
    paint_img(game, &game->data->nums[9], "img/num/9.xpm", 15, 23);
    game->data->sl = mlx_xpm_file_to_image(game->data->mlx.mlx_ptr, "img/num/sl.xpm", &w, &h);

    game->data->mouse.img = mlx_xpm_file_to_image(game->data->mlx.mlx_ptr, "img/cursor.xpm", &w, &h);


    // game->data->mlx.wall = mlx_xpm_file_to_image(game->data->mlx.mlx_ptr, "img/wall.xpm", &w, &h);
    game->data->mlx.none = mlx_new_image(game->data->mlx.mlx_ptr, RES_X, RES_Y);
    // game->data->mlx.cadre1 = mlx_xpm_file_to_image(game->data->mlx.mlx_ptr, "img/2_1.xpm", &w, &h);
    // game->data->mlx.cadre2 = mlx_xpm_file_to_image(game->data->mlx.mlx_ptr, "img/2_2.xpm", &w, &h);
    game->data->mlx.floor.mlx_img = mlx_xpm_file_to_image(game->data->mlx.mlx_ptr, "img/f.xpm", &w, &h);
    game->data->mlx.floor.addr = mlx_get_data_addr(game->data->mlx.floor.mlx_img, &game->data->mlx.floor.bpp, &game->data->mlx.floor.line_len, &game->data->mlx.floor.endian);

    // game->data->mlx.wall.mlx_img = mlx_xpm_file_to_image(game->data->mlx.mlx_ptr, "img/wall.xpm", &w, &h);
    // game->data->mlx.wall.addr = mlx_get_data_addr(game->data->mlx.wall.mlx_img, &game->data->mlx.wall.bpp, &game->data->mlx.wall.line_len, &game->data->mlx.wall.endian);

    game->data->mlx.space.mlx_img = mlx_xpm_file_to_image(game->data->mlx.mlx_ptr, "img/sp.xpm", &w, &h);
    game->data->mlx.space.addr = mlx_get_data_addr(game->data->mlx.space.mlx_img, &game->data->mlx.space.bpp, &game->data->mlx.space.line_len, &game->data->mlx.space.endian);

    game->data->intro.int1.mlx_img = mlx_new_image(game->data->mlx.mlx_ptr, RES_X, RES_Y);
    game->data->intro.int1.addr = mlx_get_data_addr(game->data->intro.int1.mlx_img, &game->data->intro.int1.bpp, &game->data->intro.int1.line_len, &game->data->intro.int1.endian);
    paint_img(game, &game->data->intro.int1, "img/int_1.xpm", RES_X, RES_Y);

    game->data->intro.int2.mlx_img = mlx_new_image(game->data->mlx.mlx_ptr, RES_X, RES_Y);
    game->data->intro.int2.addr = mlx_get_data_addr(game->data->intro.int2.mlx_img, &game->data->intro.int2.bpp, &game->data->intro.int2.line_len, &game->data->intro.int2.endian);
    paint_img(game, &game->data->intro.int2, "img/int_2.xpm", RES_X, RES_Y);

    game->data->intro.tr.mlx_img = mlx_new_image(game->data->mlx.mlx_ptr, RES_X, RES_Y);
    game->data->intro.tr.addr = mlx_get_data_addr(game->data->intro.tr.mlx_img, &game->data->intro.tr.bpp, &game->data->intro.tr.line_len, &game->data->intro.tr.endian);
    paint_color(&game->data->intro.tr, ((int)(255 * 0.15) << 24), RES_X, RES_Y);

    game->data->intro.tr2.mlx_img = mlx_new_image(game->data->mlx.mlx_ptr, RES_X, RES_Y);
    game->data->intro.tr2.addr = mlx_get_data_addr(game->data->intro.tr2.mlx_img, &game->data->intro.tr2.bpp, &game->data->intro.tr2.line_len, &game->data->intro.tr2.endian);
    paint_color(&game->data->intro.tr2, ((int)(255 * 0.5) << 24), RES_X, RES_Y);

    game->data->intro.up_logo.mlx_img = mlx_new_image(game->data->mlx.mlx_ptr, RES_X / 3, RES_Y / 6);
    game->data->intro.up_logo.addr = mlx_get_data_addr(game->data->intro.up_logo.mlx_img, &game->data->intro.up_logo.bpp, &game->data->intro.up_logo.line_len, &game->data->intro.up_logo.endian);
    paint_img(game, &game->data->intro.up_logo, "img/logo.xpm", RES_X / 3, RES_Y / 6);

    /////////////////
    game->data->intro.start.mlx_img = mlx_xpm_file_to_image(game->data->mlx.mlx_ptr, "img/sett/start.xpm", &game->data->intro.start.x, &game->data->intro.start.y);
    game->data->intro.start.addr = mlx_get_data_addr(game->data->intro.start.mlx_img, &game->data->intro.start.bpp, &game->data->intro.start.line_len, &game->data->intro.start.endian);

    game->data->intro.sett.mlx_img = mlx_xpm_file_to_image(game->data->mlx.mlx_ptr, "img/sett/setting.xpm", &game->data->intro.sett.x, &game->data->intro.sett.y);
    game->data->intro.sett.addr = mlx_get_data_addr(game->data->intro.sett.mlx_img, &game->data->intro.sett.bpp, &game->data->intro.sett.line_len, &game->data->intro.sett.endian);

    game->data->intro.exit.mlx_img = mlx_xpm_file_to_image(game->data->mlx.mlx_ptr, "img/sett/exit.xpm", &game->data->intro.exit.x, &game->data->intro.exit.y);
    game->data->intro.exit.addr = mlx_get_data_addr(game->data->intro.exit.mlx_img, &game->data->intro.exit.bpp, &game->data->intro.exit.line_len, &game->data->intro.exit.endian);

    game->data->intro.cont.mlx_img = mlx_xpm_file_to_image(game->data->mlx.mlx_ptr, "img/sett/cont.xpm", &game->data->intro.cont.x, &game->data->intro.cont.y);
    game->data->intro.cont.addr = mlx_get_data_addr(game->data->intro.cont.mlx_img, &game->data->intro.cont.bpp, &game->data->intro.cont.line_len, &game->data->intro.cont.endian);

    game->data->intro.restart.mlx_img = mlx_xpm_file_to_image(game->data->mlx.mlx_ptr, "img/sett/restart.xpm", &game->data->intro.restart.x, &game->data->intro.restart.y);
    game->data->intro.restart.addr = mlx_get_data_addr(game->data->intro.restart.mlx_img, &game->data->intro.restart.bpp, &game->data->intro.restart.line_len, &game->data->intro.restart.endian);

    game->data->intro.reset.mlx_img = mlx_xpm_file_to_image(game->data->mlx.mlx_ptr, "img/sett/reset.xpm", &game->data->intro.reset.x, &game->data->intro.reset.y);
    game->data->intro.reset.addr = mlx_get_data_addr(game->data->intro.reset.mlx_img, &game->data->intro.reset.bpp, &game->data->intro.reset.line_len, &game->data->intro.reset.endian);

    game->data->intro.back.mlx_img = mlx_xpm_file_to_image(game->data->mlx.mlx_ptr, "img/sett/back.xpm", &game->data->intro.back.x, &game->data->intro.back.y);
    game->data->intro.back.addr = mlx_get_data_addr(game->data->intro.back.mlx_img, &game->data->intro.back.bpp, &game->data->intro.back.line_len, &game->data->intro.back.endian);
    ////////////////

    game->data->intro.gun.mlx_img = mlx_xpm_file_to_image(game->data->mlx.mlx_ptr, "img/gun.xpm", &game->data->intro.gun.x, &game->data->intro.gun.y);
    game->data->intro.gun.addr = mlx_get_data_addr(game->data->intro.gun.mlx_img, &game->data->intro.gun.bpp, &game->data->intro.gun.line_len, &game->data->intro.gun.endian);

    game->data->intro.vol_icon[0].mlx_img = mlx_new_image(game->data->mlx.mlx_ptr, 50, 50);
    game->data->intro.vol_icon[0].addr = mlx_get_data_addr(game->data->intro.vol_icon[0].mlx_img, &game->data->intro.vol_icon[0].bpp, &game->data->intro.vol_icon[0].line_len, &game->data->intro.vol_icon[0].endian);
    paint_img(game, &game->data->intro.vol_icon[0], "img/mute.xpm", 50, 50);
    game->data->intro.vol_icon[1].mlx_img = mlx_new_image(game->data->mlx.mlx_ptr, 50, 50);
    game->data->intro.vol_icon[1].addr = mlx_get_data_addr(game->data->intro.vol_icon[1].mlx_img, &game->data->intro.vol_icon[1].bpp, &game->data->intro.vol_icon[1].line_len, &game->data->intro.vol_icon[1].endian);
    paint_img(game, &game->data->intro.vol_icon[1], "img/half_volume.xpm", 50, 50);
    game->data->intro.vol_icon[2].mlx_img = mlx_new_image(game->data->mlx.mlx_ptr, 50, 50);
    game->data->intro.vol_icon[2].addr = mlx_get_data_addr(game->data->intro.vol_icon[2].mlx_img, &game->data->intro.vol_icon[2].bpp, &game->data->intro.vol_icon[2].line_len, &game->data->intro.vol_icon[2].endian);
    paint_img(game, &game->data->intro.vol_icon[2], "img/volume.xpm", 50, 50);

    game->data->intro.vol[0].mlx_img = mlx_new_image(game->data->mlx.mlx_ptr, 200, 10);
    game->data->intro.vol[0].addr = mlx_get_data_addr(game->data->intro.vol[0].mlx_img, &game->data->intro.vol[0].bpp, &game->data->intro.vol[0].line_len, &game->data->intro.vol[0].endian);
    paint_color(&game->data->intro.vol[0], 0xB2BEB5, 200, 10);
    paint_color(&game->data->intro.vol[0], 0xff0000, game->data->intro.volume, 10);

    game->data->intro.vol[1].mlx_img = mlx_new_image(game->data->mlx.mlx_ptr, 25, 40);
    game->data->intro.vol[1].addr = mlx_get_data_addr(game->data->intro.vol[1].mlx_img, &game->data->intro.vol[1].bpp, &game->data->intro.vol[1].line_len, &game->data->intro.vol[1].endian);
    paint_color(&game->data->intro.vol[1], 0xffffff, 25, 40);


    game->data->intro.light_icon[1].mlx_img = mlx_xpm_file_to_image(game->data->mlx.mlx_ptr, "img/light.xpm", &game->data->intro.light_icon[1].x, &game->data->intro.light_icon[1].y);

    game->data->intro.lt.mlx_img = mlx_new_image(game->data->mlx.mlx_ptr, RES_X, RES_Y);
    game->data->intro.lt.addr = mlx_get_data_addr(game->data->intro.lt.mlx_img, &game->data->intro.lt.bpp, &game->data->intro.lt.line_len, &game->data->intro.lt.endian);
    paint_color(&game->data->intro.lt, (255 << 24), RES_X, RES_Y);

    game->data->intro.lgt[0].mlx_img = mlx_new_image(game->data->mlx.mlx_ptr, 200, 10);
    game->data->intro.lgt[0].addr = mlx_get_data_addr(game->data->intro.lgt[0].mlx_img, &game->data->intro.lgt[0].bpp, &game->data->intro.lgt[0].line_len, &game->data->intro.lgt[0].endian);
    paint_color(&game->data->intro.lgt[0], 0xB2BEB5, 200, 10);
    paint_color(&game->data->intro.lgt[0], 0xff0000, game->data->intro.light, 10);

    game->data->intro.lgt[1].mlx_img = mlx_new_image(game->data->mlx.mlx_ptr, 25, 40);
    game->data->intro.lgt[1].addr = mlx_get_data_addr(game->data->intro.lgt[1].mlx_img, &game->data->intro.lgt[1].bpp, &game->data->intro.lgt[1].line_len, &game->data->intro.lgt[1].endian);
    paint_color(&game->data->intro.lgt[1], 0xffffff, 25, 40);
    init_guns();
    init_motion();

    game->data->door.door[0][0].mlx_img = mlx_xpm_file_to_image(game->data->mlx.mlx_ptr, "img/dor1_0.xpm", &w, &h);
    game->data->door.door[0][0].addr = mlx_get_data_addr(game->data->door.door[0][0].mlx_img, &game->data->door.door[0][0].bpp, &game->data->door.door[0][0].line_len, &game->data->door.door[0][0].endian);
    game->data->door.door[0][1].mlx_img = mlx_xpm_file_to_image(game->data->mlx.mlx_ptr, "img/dor1_1.xpm", &w, &h);
    game->data->door.door[0][1].addr = mlx_get_data_addr(game->data->door.door[0][1].mlx_img, &game->data->door.door[0][1].bpp, &game->data->door.door[0][1].line_len, &game->data->door.door[0][1].endian);

    game->data->cross.mlx_img = mlx_xpm_file_to_image(game->data->mlx.mlx_ptr, "img/cross3.xpm", &w, &h);
    game->data->cross.addr = mlx_get_data_addr(game->data->cross.mlx_img, &game->data->cross.bpp, &game->data->cross.line_len, &game->data->cross.endian);

    game->data->health_enm.mlx_img = mlx_new_image(game->data->mlx.mlx_ptr, 1020, 40);
    game->data->health_enm.addr = mlx_get_data_addr(game->data->health_enm.mlx_img, &game->data->health_enm.bpp, &game->data->health_enm.line_len, &game->data->health_enm.endian);

    game->data->lose.mlx_img = mlx_xpm_file_to_image(game->data->mlx.mlx_ptr, "img/lose.xpm", &game->data->lose.x, &game->data->lose.y);
    game->data->lose.addr = mlx_get_data_addr(game->data->lose.mlx_img, &game->data->lose.bpp, &game->data->lose.line_len, &game->data->lose.endian);

}
int	main(int ac, char **av)
{
	t_game	*game;

	check_argument(ac, av);
	game = ft_calloc(1, sizeof(t_game));
	if (game == NULL)
		error_exit("game calloc failed.");
	init_maps(av, game);
	parsing(game);
	set_minimap(game);
}
