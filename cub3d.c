/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:52:32 by janhan            #+#    #+#             */
/*   Updated: 2024/05/06 14:18:26 by janhan           ###   ########.fr       */
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
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

//void	init_img_control(t_game *game)
//{
//	//int arr[20];

//}

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

void	paint_color(t_img *img, int color, int x_s, int y_s)
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

void	put_color(int i, int j, char p, t_game *game)
{
	if (game->data->map[i][j] != '0')
		return ;
	game->data->door.map[i][j] = p;
	put_color(i + 1, j, p, game);
	put_color(i - 1, j, p, game);
	put_color(i, j + 1, p, game);
	put_color(i, j - 1, p, game);
}

void    init_virtual_map(t_game *game)
{
	int	i;
	int	j;
	int	p;

	p = 'A';
	i = -1;
	while (game->data->map[++i])
	{
		j = -1;
		while (game->data->door.map[i][++j])
			if (game->data->door.map[i][j] == '0')
				put_color(i, j, p++, game);
		if (p == 'H')
			p = 'A';
	}
}

void	set_minimap(t_game *game, t_data *data)
{
	int	w;
	int	h;

	//pthread_t t;
	//pthread_t t2;

	w = 50;
	h = 50;

	data->mlx.mlx_ptr = mlx_init();
	data->mlx.win_ptr = mlx_new_window(data->mlx.mlx_ptr, RES_X, RES_Y, "map");

	data->img.mlx_img = mlx_new_image(data->mlx.mlx_ptr, RES_X, RES_Y);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, &data->img.line_len, &data->img.endian);
	data->img2.mlx_img = mlx_new_image(data->mlx.mlx_ptr, RES_X, RES_Y);
	data->img2.addr = mlx_get_data_addr(data->img.mlx_img, &data->img2.bpp, &data->img2.line_len, &data->img2.endian);
	data->img3.mlx_img = mlx_new_image(data->mlx.mlx_ptr, RES_X / 3, RES_Y);
	data->img3.addr = mlx_get_data_addr(data->img.mlx_img, &data->img3.bpp, &data->img3.line_len, &data->img3.endian);

	data->img_c.mlx_img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, "img/ceill.xpm", &w, &h);
	data->assets.mlx_img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, "img/textures.xpm", &w, &h);
	data->guns.mlx_img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, "img/weapons.xpm", &w, &h);
	data->blood_hit.mlx_img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, "img/blood_hiy.xpm", &w, &h);
	data->blood_hit2.mlx_img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, "img/blood_hit.xpm", &w, &h);
	data->img_c.addr = mlx_get_data_addr(data->img_c.mlx_img, &data->img_c.bpp, &data->img_c.line_len, &data->img_c.endian);
	data->assets.addr = mlx_get_data_addr(data->assets.mlx_img, &data->assets.bpp, &data->assets.line_len, &data->assets.endian);
	data->guns.addr = mlx_get_data_addr(data->guns.mlx_img, &data->guns.bpp, &data->guns.line_len, &data->guns.endian);
	data->blood_hit.addr = mlx_get_data_addr(data->blood_hit.mlx_img, &data->blood_hit.bpp, &data->blood_hit.line_len, &data->blood_hit.endian);
	data->blood_hit2.addr = mlx_get_data_addr(data->blood_hit2.mlx_img, &data->blood_hit2.bpp, &data->blood_hit2.line_len, &data->blood_hit2.endian);
	data->mlx.player = mlx_xpm_file_to_image(data->mlx.mlx_ptr, "img/cursor/4.xpm", &w, &h);
	data->objects.time[0].mlx_img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, "img/num/0.xpm", &w, &h);
	data->objects.time[1].mlx_img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, "img/num/1.xpm", &w, &h);
	data->objects.time[2].mlx_img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, "img/num/2.xpm", &w, &h);
	data->objects.time[3].mlx_img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, "img/num/3.xpm", &w, &h);
	data->objects.time[4].mlx_img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, "img/num/4.xpm", &w, &h);
	data->objects.time[5].mlx_img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, "img/num/5.xpm", &w, &h);
	data->objects.time[6].mlx_img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, "img/num/6.xpm", &w, &h);
	data->objects.time[7].mlx_img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, "img/num/7.xpm", &w, &h);
	data->objects.time[8].mlx_img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, "img/num/8.xpm", &w, &h);
	data->objects.time[9].mlx_img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, "img/num/9.xpm", &w, &h);
	data->objects.time[0].addr = mlx_get_data_addr(data->objects.time[0].mlx_img, &data->objects.time[0].bpp, &data->objects.time[0].line_len, &data->objects.time[0].endian);
	data->objects.time[1].addr = mlx_get_data_addr(data->objects.time[1].mlx_img, &data->objects.time[1].bpp, &data->objects.time[1].line_len, &data->objects.time[1].endian);
	data->objects.time[2].addr = mlx_get_data_addr(data->objects.time[2].mlx_img, &data->objects.time[2].bpp, &data->objects.time[2].line_len, &data->objects.time[2].endian);
	data->objects.time[3].addr = mlx_get_data_addr(data->objects.time[3].mlx_img, &data->objects.time[3].bpp, &data->objects.time[3].line_len, &data->objects.time[3].endian);
	data->objects.time[4].addr = mlx_get_data_addr(data->objects.time[4].mlx_img, &data->objects.time[4].bpp, &data->objects.time[4].line_len, &data->objects.time[4].endian);
	data->objects.time[5].addr = mlx_get_data_addr(data->objects.time[5].mlx_img, &data->objects.time[5].bpp, &data->objects.time[5].line_len, &data->objects.time[5].endian);
	data->objects.time[6].addr = mlx_get_data_addr(data->objects.time[6].mlx_img, &data->objects.time[6].bpp, &data->objects.time[6].line_len, &data->objects.time[6].endian);
	data->objects.time[7].addr = mlx_get_data_addr(data->objects.time[7].mlx_img, &data->objects.time[7].bpp, &data->objects.time[7].line_len, &data->objects.time[7].endian);
	data->objects.time[8].addr = mlx_get_data_addr(data->objects.time[8].mlx_img, &data->objects.time[8].bpp, &data->objects.time[8].line_len, &data->objects.time[8].endian);
	data->objects.time[9].addr = mlx_get_data_addr(data->objects.time[9].mlx_img, &data->objects.time[9].bpp, &data->objects.time[9].line_len, &data->objects.time[9].endian);
	data->nums[0].mlx_img = mlx_new_image(data->mlx.mlx_ptr, 15, 23);
	data->nums[1].mlx_img = mlx_new_image(data->mlx.mlx_ptr, 15, 23);
	data->nums[2].mlx_img = mlx_new_image(data->mlx.mlx_ptr, 15, 23);
	data->nums[3].mlx_img = mlx_new_image(data->mlx.mlx_ptr, 15, 23);
	data->nums[4].mlx_img = mlx_new_image(data->mlx.mlx_ptr, 15, 23);
	data->nums[5].mlx_img = mlx_new_image(data->mlx.mlx_ptr, 15, 23);
	data->nums[6].mlx_img = mlx_new_image(data->mlx.mlx_ptr, 15, 23);
	data->nums[7].mlx_img = mlx_new_image(data->mlx.mlx_ptr, 15, 23);
	data->nums[8].mlx_img = mlx_new_image(data->mlx.mlx_ptr, 15, 23);
	data->nums[9].mlx_img = mlx_new_image(data->mlx.mlx_ptr, 15, 23);
	data->nums[0].addr = mlx_get_data_addr(data->nums[0].mlx_img, &data->nums[0].bpp, &data->nums[0].line_len, &data->nums[0].endian);
	data->nums[1].addr = mlx_get_data_addr(data->nums[1].mlx_img, &data->nums[1].bpp, &data->nums[1].line_len, &data->nums[1].endian);
	data->nums[2].addr = mlx_get_data_addr(data->nums[2].mlx_img, &data->nums[2].bpp, &data->nums[2].line_len, &data->nums[2].endian);
	data->nums[3].addr = mlx_get_data_addr(data->nums[3].mlx_img, &data->nums[3].bpp, &data->nums[3].line_len, &data->nums[3].endian);
	data->nums[4].addr = mlx_get_data_addr(data->nums[4].mlx_img, &data->nums[4].bpp, &data->nums[4].line_len, &data->nums[4].endian);
	data->nums[5].addr = mlx_get_data_addr(data->nums[5].mlx_img, &data->nums[5].bpp, &data->nums[5].line_len, &data->nums[5].endian);
	data->nums[6].addr = mlx_get_data_addr(data->nums[6].mlx_img, &data->nums[6].bpp, &data->nums[6].line_len, &data->nums[6].endian);
	data->nums[7].addr = mlx_get_data_addr(data->nums[7].mlx_img, &data->nums[7].bpp, &data->nums[7].line_len, &data->nums[7].endian);
	data->nums[8].addr = mlx_get_data_addr(data->nums[8].mlx_img, &data->nums[8].bpp, &data->nums[8].line_len, &data->nums[8].endian);
	data->nums[9].addr = mlx_get_data_addr(data->nums[9].mlx_img, &data->nums[9].bpp, &data->nums[9].line_len, &data->nums[9].endian);
	paint_img(game, &data->nums[0], "img/num/0.xpm", 15, 23);
	paint_img(game, &data->nums[1], "img/num/1.xpm", 15, 23);
	paint_img(game, &data->nums[2], "img/num/2.xpm", 15, 23);
	paint_img(game, &data->nums[3], "img/num/3.xpm", 15, 23);
	paint_img(game, &data->nums[4], "img/num/4.xpm", 15, 23);
	paint_img(game, &data->nums[5], "img/num/5.xpm", 15, 23);
	paint_img(game, &data->nums[6], "img/num/6.xpm", 15, 23);
	paint_img(game, &data->nums[7], "img/num/7.xpm", 15, 23);
	paint_img(game, &data->nums[8], "img/num/8.xpm", 15, 23);
	paint_img(game, &data->nums[9], "img/num/9.xpm", 15, 23);
	data->sl = mlx_xpm_file_to_image(data->mlx.mlx_ptr, "img/num/sl.xpm", &w, &h);
	data->mouse.img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, "img/cursor.xpm", &w, &h);
	// data->mlx.wall = mlx_xpm_file_to_image(data->mlx.mlx_ptr, "img/wall.xpm", &w, &h);
	data->mlx.none = mlx_new_image(data->mlx.mlx_ptr, RES_X, RES_Y);
	// data->mlx.cadre1 = mlx_xpm_file_to_image(data->mlx.mlx_ptr, "img/2_1.xpm", &w, &h);
	// data->mlx.cadre2 = mlx_xpm_file_to_image(data->mlx.mlx_ptr, "img/2_2.xpm", &w, &h);
	data->mlx.floor.mlx_img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, "img/f.xpm", &w, &h);
	data->mlx.floor.addr = mlx_get_data_addr(data->mlx.floor.mlx_img, &data->mlx.floor.bpp, &data->mlx.floor.line_len, &data->mlx.floor.endian);
	// data->mlx.wall.mlx_img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, "img/wall.xpm", &w, &h);
	// data->mlx.wall.addr = mlx_get_data_addr(data->mlx.wall.mlx_img, &data->mlx.wall.bpp, &data->mlx.wall.line_len, &data->mlx.wall.endian);
	data->mlx.space.mlx_img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, "img/sp.xpm", &w, &h);
	data->mlx.space.addr = mlx_get_data_addr(data->mlx.space.mlx_img, &data->mlx.space.bpp, &data->mlx.space.line_len, &data->mlx.space.endian);
	data->intro.int1.mlx_img = mlx_new_image(data->mlx.mlx_ptr, RES_X, RES_Y);
	data->intro.int1.addr = mlx_get_data_addr(data->intro.int1.mlx_img, &data->intro.int1.bpp, &data->intro.int1.line_len, &data->intro.int1.endian);
	paint_img(game, &data->intro.int1, "img/int_1.xpm", RES_X, RES_Y);
	data->intro.int2.mlx_img = mlx_new_image(data->mlx.mlx_ptr, RES_X, RES_Y);
	data->intro.int2.addr = mlx_get_data_addr(data->intro.int2.mlx_img, &data->intro.int2.bpp, &data->intro.int2.line_len, &data->intro.int2.endian);
	paint_img(game, &data->intro.int2, "img/int_2.xpm", RES_X, RES_Y);
	data->intro.tr.mlx_img = mlx_new_image(data->mlx.mlx_ptr, RES_X, RES_Y);
	data->intro.tr.addr = mlx_get_data_addr(data->intro.tr.mlx_img, &data->intro.tr.bpp, &data->intro.tr.line_len, &data->intro.tr.endian);
	paint_color(&data->intro.tr, ((int)(255 * 0.15) << 24), RES_X, RES_Y);
	data->intro.tr2.mlx_img = mlx_new_image(data->mlx.mlx_ptr, RES_X, RES_Y);
	data->intro.tr2.addr = mlx_get_data_addr(data->intro.tr2.mlx_img, &data->intro.tr2.bpp, &data->intro.tr2.line_len, &data->intro.tr2.endian);
	paint_color(&data->intro.tr2, ((int)(255 * 0.5) << 24), RES_X, RES_Y);
	data->intro.up_logo.mlx_img = mlx_new_image(data->mlx.mlx_ptr, RES_X / 3, RES_Y / 6);
	data->intro.up_logo.addr = mlx_get_data_addr(data->intro.up_logo.mlx_img, &data->intro.up_logo.bpp, &data->intro.up_logo.line_len, &data->intro.up_logo.endian);
	paint_img(game, &data->intro.up_logo, "img/logo.xpm", RES_X / 3, RES_Y / 6);
	/////////////////
	data->intro.start.mlx_img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, "img/sett/start.xpm", &data->intro.start.x, &data->intro.start.y);
	data->intro.start.addr = mlx_get_data_addr(data->intro.start.mlx_img, &data->intro.start.bpp, &data->intro.start.line_len, &data->intro.start.endian);
	data->intro.sett.mlx_img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, "img/sett/setting.xpm", &data->intro.sett.x, &data->intro.sett.y);
	data->intro.sett.addr = mlx_get_data_addr(data->intro.sett.mlx_img, &data->intro.sett.bpp, &data->intro.sett.line_len, &data->intro.sett.endian);
	data->intro.exit.mlx_img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, "img/sett/exit.xpm", &data->intro.exit.x, &data->intro.exit.y);
	data->intro.exit.addr = mlx_get_data_addr(data->intro.exit.mlx_img, &data->intro.exit.bpp, &data->intro.exit.line_len, &data->intro.exit.endian);
	data->intro.cont.mlx_img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, "img/sett/cont.xpm", &data->intro.cont.x, &data->intro.cont.y);
	data->intro.cont.addr = mlx_get_data_addr(data->intro.cont.mlx_img, &data->intro.cont.bpp, &data->intro.cont.line_len, &data->intro.cont.endian);
	data->intro.restart.mlx_img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, "img/sett/restart.xpm", &data->intro.restart.x, &data->intro.restart.y);
	data->intro.restart.addr = mlx_get_data_addr(data->intro.restart.mlx_img, &data->intro.restart.bpp, &data->intro.restart.line_len, &data->intro.restart.endian);
	data->intro.reset.mlx_img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, "img/sett/reset.xpm", &data->intro.reset.x, &data->intro.reset.y);
	data->intro.reset.addr = mlx_get_data_addr(data->intro.reset.mlx_img, &data->intro.reset.bpp, &data->intro.reset.line_len, &data->intro.reset.endian);
	data->intro.back.mlx_img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, "img/sett/back.xpm", &data->intro.back.x, &data->intro.back.y);
	data->intro.back.addr = mlx_get_data_addr(data->intro.back.mlx_img, &data->intro.back.bpp, &data->intro.back.line_len, &data->intro.back.endian);
	////////////////
	data->intro.gun.mlx_img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, "img/gun.xpm", &data->intro.gun.x, &data->intro.gun.y);
	data->intro.gun.addr = mlx_get_data_addr(data->intro.gun.mlx_img, &data->intro.gun.bpp, &data->intro.gun.line_len, &data->intro.gun.endian);
	data->intro.vol_icon[0].mlx_img = mlx_new_image(data->mlx.mlx_ptr, 50, 50);
	data->intro.vol_icon[0].addr = mlx_get_data_addr(data->intro.vol_icon[0].mlx_img, &data->intro.vol_icon[0].bpp, &data->intro.vol_icon[0].line_len, &data->intro.vol_icon[0].endian);
	paint_img(game, &data->intro.vol_icon[0], "img/mute.xpm", 50, 50);
	data->intro.vol_icon[1].mlx_img = mlx_new_image(data->mlx.mlx_ptr, 50, 50);
	data->intro.vol_icon[1].addr = mlx_get_data_addr(data->intro.vol_icon[1].mlx_img, &data->intro.vol_icon[1].bpp, &data->intro.vol_icon[1].line_len, &data->intro.vol_icon[1].endian);
	paint_img(game, &data->intro.vol_icon[1], "img/half_volume.xpm", 50, 50);
	data->intro.vol_icon[2].mlx_img = mlx_new_image(data->mlx.mlx_ptr, 50, 50);
	data->intro.vol_icon[2].addr = mlx_get_data_addr(data->intro.vol_icon[2].mlx_img, &data->intro.vol_icon[2].bpp, &data->intro.vol_icon[2].line_len, &data->intro.vol_icon[2].endian);
	paint_img(game, &data->intro.vol_icon[2], "img/volume.xpm", 50, 50);
	data->intro.vol[0].mlx_img = mlx_new_image(data->mlx.mlx_ptr, 200, 10);
	data->intro.vol[0].addr = mlx_get_data_addr(data->intro.vol[0].mlx_img, &data->intro.vol[0].bpp, &data->intro.vol[0].line_len, &data->intro.vol[0].endian);
	paint_color(&data->intro.vol[0], 0xB2BEB5, 200, 10);
	paint_color(&data->intro.vol[0], 0xff0000, data->intro.volume, 10);
	data->intro.vol[1].mlx_img = mlx_new_image(data->mlx.mlx_ptr, 25, 40);
	data->intro.vol[1].addr = mlx_get_data_addr(data->intro.vol[1].mlx_img, &data->intro.vol[1].bpp, &data->intro.vol[1].line_len, &data->intro.vol[1].endian);
	paint_color(&data->intro.vol[1], 0xffffff, 25, 40);
	data->intro.light_icon[1].mlx_img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, "img/light.xpm", &data->intro.light_icon[1].x, &data->intro.light_icon[1].y);
	data->intro.lt.mlx_img = mlx_new_image(data->mlx.mlx_ptr, RES_X, RES_Y);
	data->intro.lt.addr = mlx_get_data_addr(data->intro.lt.mlx_img, &data->intro.lt.bpp, &data->intro.lt.line_len, &data->intro.lt.endian);
	paint_color(&data->intro.lt, (255 << 24), RES_X, RES_Y);
	data->intro.lgt[0].mlx_img = mlx_new_image(data->mlx.mlx_ptr, 200, 10);
	data->intro.lgt[0].addr = mlx_get_data_addr(data->intro.lgt[0].mlx_img, &data->intro.lgt[0].bpp, &data->intro.lgt[0].line_len, &data->intro.lgt[0].endian);
	paint_color(&data->intro.lgt[0], 0xB2BEB5, 200, 10);
	paint_color(&data->intro.lgt[0], 0xff0000, data->intro.light, 10);
	data->intro.lgt[1].mlx_img = mlx_new_image(data->mlx.mlx_ptr, 25, 40);
	data->intro.lgt[1].addr = mlx_get_data_addr(data->intro.lgt[1].mlx_img, &data->intro.lgt[1].bpp, &data->intro.lgt[1].line_len, &data->intro.lgt[1].endian);
	paint_color(&data->intro.lgt[1], 0xffffff, 25, 40);
	init_guns(game);
	init_motion(game);
	data->door.door[0][0].mlx_img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, "img/dor1_0.xpm", &w, &h);
	data->door.door[0][0].addr = mlx_get_data_addr(data->door.door[0][0].mlx_img, &data->door.door[0][0].bpp, &data->door.door[0][0].line_len, &data->door.door[0][0].endian);
	data->door.door[0][1].mlx_img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, "img/dor1_1.xpm", &w, &h);
	data->door.door[0][1].addr = mlx_get_data_addr(data->door.door[0][1].mlx_img, &data->door.door[0][1].bpp, &data->door.door[0][1].line_len, &data->door.door[0][1].endian);
	data->cross.mlx_img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, "img/cross3.xpm", &w, &h);
	data->cross.addr = mlx_get_data_addr(data->cross.mlx_img, &data->cross.bpp, &data->cross.line_len, &data->cross.endian);
	data->health_enm.mlx_img = mlx_new_image(data->mlx.mlx_ptr, 1020, 40);
	data->health_enm.addr = mlx_get_data_addr(data->health_enm.mlx_img, &data->health_enm.bpp, &data->health_enm.line_len, &data->health_enm.endian);
	data->lose.mlx_img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, "img/lose.xpm", &data->lose.x, &data->lose.y);
	data->lose.addr = mlx_get_data_addr(data->lose.mlx_img, &data->lose.bpp, &data->lose.line_len, &data->lose.endian);

	int	i;

	i = -1;
	while (++i < 1000)
	{
		data->keys[i] = 0,
		data->intro.keys[i] = NULL;
	}
	init_virtual_map(game);
	//init_img_control(game);
	//init_angles(game);
	//mlx_mouse_hide();
	//pthread_create(&t, NULL, &time_count, NULL);
	//pthread_create(&t2, NULL, &check_sound, NULL);
	//mlx_hook(data->mlx.win_ptr, 2, 1L<<0, key_press, NULL);
	//mlx_hook(data->mlx.win_ptr, 3, 1L<<1, key_release, NULL);

	//mlx_loop_hook(data->mlx.mlx_ptr, rendering, NULL);
	//mlx_hook(data->mlx.win_ptr, 17, 1, ft_close, NULL);
	//mlx_loop(data->mlx.mlx_ptr);
}
int	main(int ac, char **av)
{
	t_game	*game;

	check_argument(ac, av);
	game = ft_calloc(1, sizeof(t_game));
	if (game == NULL)
		error_exit("game calloc failed.");
	init_maps(av, game);
	printf("----------init_maps OK-----------\n");
	parsing(game);
	printf("----------parsing OK-----------\n");
	set_minimap(game, game->data);
	printf("----------set_minimap OK-----------\n");
}
