/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:28:41 by janhan            #+#    #+#             */
/*   Updated: 2024/05/06 15:40:58 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int cnt;
int c;
int ac;
int a;
int i;
int f;

void path_name(char *path, char *p, int i, int len)
{
	int j;

	ft_memcpy(path, p, len);
	j = len;
	if (i / 100)
		path[j++] = '0' + (i / 100);
	if (i / 10)
		path[j++] = '0' + (i % 100) / 10;
	path[j++] = '0' + (i % 10);
	path[j++] = '.';
	path[j++] = 'x';
	path[j++] = 'p';
	path[j++] = 'm';
	path[j++] = 0;
}

int get_img_color(t_img *img, int x, int y, t_game *game)
{
	return (*(int *)(img->addr + (y * img->line_len + x * (img->bpp / 8))));
}

void    render_intro(t_game *game)
{
	char path[100];
	t_img img;
	int x;
	int y;

	path_name(path, "img/intro/", i, 10);
	img.mlx_img = mlx_xpm_file_to_image(game->data->mlx.mlx_ptr, path, &x, &y);

	mlx_clear_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr);
	mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, img.mlx_img, (RES_X - 498) / 2, (RES_Y - 280) / 2);
	mlx_destroy_image(game->data->mlx.mlx_ptr, img.mlx_img);

	img.mlx_img = mlx_new_image(game->data->mlx.mlx_ptr, 498, 280);
	img.addr = mlx_get_data_addr(img.mlx_img, &img.bpp, &img.line_len, &img.endian);
	y = -1;
	while (++y < 280)
	{
		x = -1;
		while (++x < 498)
		{
			if (x < 125)
				img_pix_put(&img, x, y, ((x * 2) << 24));
			else if (x > 498 - 125)
				img_pix_put(&img, x, y, (((-x + 498 - 125) * 2) << 24));
			else if (y < 10)
				img_pix_put(&img, x, y, ((y * 20) << 24));
			else if (y > 280 - 10)
				img_pix_put(&img, x, y, (((-y + 280 - 10) * 20) << 24));
			else
				img_pix_put(&img, x, y, (255 << 24));
		}
	}
	mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, img.mlx_img, (RES_X - 498) / 2, (RES_Y - 280) / 2);
	mlx_destroy_image(game->data->mlx.mlx_ptr, img.mlx_img);

	i++;
	if (i == 182)
		f = 1;
	i = i * (i < 182);
	if (f)
	{
		img.mlx_img = mlx_xpm_file_to_image(game->data->mlx.mlx_ptr, "img/press_to_continue.xpm", &x, &y);
		img.addr = mlx_get_data_addr(img.mlx_img, &img.bpp, &img.line_len, &img.endian);
		y = -1;
		while (++y < 53)
		{
			x = -1;
			while (++x < 439)
				if (game->data->mouse.on_click && (unsigned int)get_img_color(&img, x, y, game) != 0xff000000)
					img_pix_put(&img, x, y, 0xffffff);
				else if (!game->data->mouse.hover && (unsigned int)get_img_color(&img, x, y, game) != 0xff000000)
					img_pix_put(&img, x, y, get_img_color(&img, x, y, game) + ((i * 2) << 24));
				else if ((unsigned int)get_img_color(&img, x, y, game) == 0x000000)
					img_pix_put(&img, x, y, get_img_color(&img, x, y, game) + 0xac51e38);
		}
		mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, img.mlx_img, (RES_X - 498) / 2 + 35, (RES_Y + 280) / 2 + 70);
		mlx_destroy_image(game->data->mlx.mlx_ptr, img.mlx_img);
	}
	if (game->data->mouse.clicked)
	{
		img.mlx_img = mlx_new_image(game->data->mlx.mlx_ptr, RES_X, RES_Y);
		img.addr = mlx_get_data_addr(img.mlx_img, &img.bpp, &img.line_len, &img.endian);
		y = -1;
		while (++y < RES_Y)
		{
			x = -1;
			while (++x < RES_X)
					img_pix_put(&img, x, y, 0x000000 + ((255 - game->data->mouse.clicked * 2) << 24));
		}
		mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, img.mlx_img, 0, 0);
		mlx_destroy_image(game->data->mlx.mlx_ptr, img.mlx_img);
		game->data->mouse.clicked++;
	}
}

int mm;

void    render_intro1(t_game *game)
{
	char    path[100];
	void    *img;
	int     y;
	int     x;

	path_name(path, "img/intro1/", mm++, 11);
	mlx_clear_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr);
	img = mlx_xpm_file_to_image(game->data->mlx.mlx_ptr, path, &x, &y);
	mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, img, 0, 0);
	mlx_destroy_image(game->data->mlx.mlx_ptr, img);
	// usleep(12000);
	// mm++;
	if (mm >= 175)
		game->data->mode = INTRO2;
}

void    render_intr(t_img *img, t_game *game)
{
	t_img	img2;
	int		x;
	int		y;

	mlx_clear_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr);
	img2.mlx_img = mlx_new_image(game->data->mlx.mlx_ptr, RES_X, RES_Y);
	img2.addr = mlx_get_data_addr(img2.mlx_img, &img2.bpp, &img2.line_len, &img2.endian);
	y = -1;
	while (++y < RES_Y)
	{
		x = -1;
		while (++x < RES_X)
				img_pix_put(&img2, x, y, get_img_color(img, x, y, game) + (((255 - i * 4) * !f + ((i * 4) % 256) * f) << 24));
	}
	mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, img2.mlx_img, 0, 0);
	mlx_destroy_image(game->data->mlx.mlx_ptr, img2.mlx_img);
}

void    render_intro2(t_game *game)
{
	if (i < 64 * 2)
		render_intr(&game->data->intro.int1, game);
	else
		render_intr(&game->data->intro.int2, game);
	i++;
	if (i == 64)
		f = 1;
	if (i == 64 * 2)
		f = 0;
	if (i == 64 * 3)
		i = 0,
		f = 0,
		game->data->mouse.clicked = 0,
		game->data->mode = SETTING;
}

void    setting_render(t_img *img, int x, int y, int type, t_game *game)
{
	int i;
	int j;
	t_img img2;

	img2.mlx_img = mlx_new_image(game->data->mlx.mlx_ptr, img->x, img->y);
	img2.addr = mlx_get_data_addr(img2.mlx_img, &img2.bpp, &img2.line_len, &img2.endian);
	i = -1;
	while (++i < img->x)
	{
		j = -1;
		while (++j < img->y)
			img_pix_put(&img2, i, j, get_img_color(img, i, j, game) + 0xffffff * ((unsigned int)get_img_color(img, i, j, game) != 0xff000000 && game->data->mouse.on_clk[type]) + 0xff0000 * ((unsigned int)get_img_color(img, i, j, game) != 0xff000000 && game->data->mouse.on_hov[type] && !game->data->mouse.on_clk[type]));
	}
	mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, img2.mlx_img, x, y);
	mlx_destroy_image(game->data->mlx.mlx_ptr, img2.mlx_img);
}

void    animate_sett_in(t_game *game)
{
	int a;

	a = game->data->intro.animate_sett--;
	mlx_clear_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr);
	mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->img.mlx_img, 0, 0);
    mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->objects.time[game->data->objects.t4].mlx_img, RES_X - 142, 30);
    mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->objects.time[game->data->objects.t3].mlx_img, RES_X - 142 + 30, 30);
    mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->objects.time[game->data->objects.t2].mlx_img, RES_X - 132 + 60, 30);
    mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->objects.time[game->data->objects.t1].mlx_img, RES_X - 132 + 90, 30);
	mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.tr2.mlx_img, 0, 0);

	setting_render(&game->data->intro.cont, (RES_X - game->data->intro.cont.x) / 2 - a * (a > 0), (RES_Y - game->data->intro.cont.y) / 2 - RES_Y / 6, 3, game);
	setting_render(&game->data->intro.restart, (RES_X - game->data->intro.restart.x) / 2 + (a + 400) * (a + 400 > 0), (RES_Y - game->data->intro.restart.y) / 2 - RES_Y / 12, 4, game);
	setting_render(&game->data->intro.sett, (RES_X - game->data->intro.sett.x) / 2 - (a + 800) * (a + 800 > 0), (RES_Y - game->data->intro.sett.y) / 2, 1, game);
	setting_render(&game->data->intro.exit, (RES_X - game->data->intro.exit.x) / 2 + (a + 1200) * (a + 1200 > 0), (RES_Y - game->data->intro.exit.y) / 2 + RES_Y / 12, 2, game);
	game->data->intro.animate_sett -= 60;
	if (game->data->intro.animate_sett < -1200)
		game->data->mode = SETTING2;
}

void    animate_sett_out(t_game *game)
{
	int a;

	a = game->data->intro.animate_sett++;
	mlx_clear_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr);
	mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->img.mlx_img, 0, 0);
    mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->objects.time[game->data->objects.t4].mlx_img, RES_X - 142, 30);
    mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->objects.time[game->data->objects.t3].mlx_img, RES_X - 142 + 30, 30);
    mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->objects.time[game->data->objects.t2].mlx_img, RES_X - 132 + 60, 30);
    mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->objects.time[game->data->objects.t1].mlx_img, RES_X - 132 + 90, 30);
	mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.tr2.mlx_img, 0, 0);

	setting_render(&game->data->intro.cont, (RES_X - game->data->intro.cont.x) / 2 - a * (a > 0), (RES_Y - game->data->intro.cont.y) / 2 - RES_Y / 6, 3, game);
	setting_render(&game->data->intro.restart, (RES_X - game->data->intro.restart.x) / 2 + (a + 400) * (a + 400 > 0), (RES_Y - game->data->intro.restart.y) / 2 - RES_Y / 12, 4, game);
	setting_render(&game->data->intro.sett, (RES_X - game->data->intro.sett.x) / 2 - (a + 800) * (a + 800 > 0), (RES_Y - game->data->intro.sett.y) / 2, 1, game);
	setting_render(&game->data->intro.exit, (RES_X - game->data->intro.exit.x) / 2 + (a + 1200) * (a + 1200 > 0), (RES_Y - game->data->intro.exit.y) / 2 + RES_Y / 12, 2, game);
	game->data->intro.animate_sett += 60;
	if (game->data->intro.animate_sett > 700)
		game->data->mode = GAME;
}

void    render_setting2(t_game *game)
{
	mlx_clear_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr);
	mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->img.mlx_img, 0, 0);
    mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->objects.time[game->data->objects.t4].mlx_img, RES_X - 142, 30);
    mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->objects.time[game->data->objects.t3].mlx_img, RES_X - 142 + 30, 30);
    mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->objects.time[game->data->objects.t2].mlx_img, RES_X - 132 + 60, 30);
    mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->objects.time[game->data->objects.t1].mlx_img, RES_X - 132 + 90, 30);
	mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.tr2.mlx_img, 0, 0);

	setting_render(&game->data->intro.cont, (RES_X - game->data->intro.cont.x) / 2, (RES_Y - game->data->intro.cont.y) / 2 - RES_Y / 6, 3, game);
	setting_render(&game->data->intro.restart, (RES_X - game->data->intro.restart.x) / 2, (RES_Y - game->data->intro.restart.y) / 2 - RES_Y / 12, 4, game);
	setting_render(&game->data->intro.sett, (RES_X - game->data->intro.sett.x) / 2, (RES_Y - game->data->intro.sett.y) / 2, 1, game);
	setting_render(&game->data->intro.exit, (RES_X - game->data->intro.exit.x) / 2, (RES_Y - game->data->intro.exit.y) / 2 + RES_Y / 12, 2, game);
	if (game->data->mouse.on_clk[3])
		mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.gun.mlx_img, (RES_X - game->data->intro.cont.x) / 2 - 40, (RES_Y - game->data->intro.cont.y) / 2 - RES_Y / 6 + 40);
	else if (game->data->mouse.on_clk[4])
		mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.gun.mlx_img, (RES_X - game->data->intro.restart.x) / 2 - 40, (RES_Y - game->data->intro.restart.y) / 2 - RES_Y / 12 + 40);
	else if (game->data->mouse.on_clk[1])
		mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.gun.mlx_img, (RES_X - game->data->intro.start.x) / 2 - 70, (RES_Y - game->data->intro.sett.y) / 2 + 40);
	else if (game->data->mouse.on_clk[2])
		mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.gun.mlx_img, (RES_X - game->data->intro.start.x) / 2 - 40, (RES_Y - game->data->intro.exit.y) / 2 + RES_Y / 12 + 40);
	else if (game->data->mouse.on_hov[3])
		mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.gun.mlx_img, (RES_X - game->data->intro.cont.x) / 2 - 40, (RES_Y - game->data->intro.cont.y) / 2 - RES_Y / 6 + 40);
	else if (game->data->mouse.on_hov[4])
		mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.gun.mlx_img, (RES_X - game->data->intro.restart.x) / 2 - 40, (RES_Y - game->data->intro.restart.y) / 2 - RES_Y / 12 + 40);
	else if (game->data->mouse.on_hov[1])
		mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.gun.mlx_img, (RES_X - game->data->intro.start.x) / 2 - 70, (RES_Y - game->data->intro.sett.y) / 2 + 40);
	else if (game->data->mouse.on_hov[2])
		mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.gun.mlx_img, (RES_X - game->data->intro.start.x) / 2 - 40, (RES_Y - game->data->intro.exit.y) / 2 + RES_Y / 12 + 40);
}

void    render_setting(t_game *game)
{
	mlx_clear_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr);
	mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.int2.mlx_img, 0, 0);
	mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.tr.mlx_img, 0, 0);
	mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.up_logo.mlx_img, RES_X / 3, RES_Y / 12);

	setting_render(&game->data->intro.start, (RES_X - game->data->intro.start.x) / 2, (RES_Y - game->data->intro.start.y) / 2 - RES_Y / 6, 0, game);
	setting_render(&game->data->intro.sett, (RES_X - game->data->intro.sett.x) / 2, (RES_Y - game->data->intro.sett.y) / 2 - RES_Y / 12, 1, game);
	setting_render(&game->data->intro.exit, (RES_X - game->data->intro.exit.x) / 2, (RES_Y - game->data->intro.exit.y) / 2, 2, game);
	if (game->data->mouse.on_clk[0])
		mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.gun.mlx_img, (RES_X - game->data->intro.start.x) / 2 - 40, (RES_Y - game->data->intro.start.y) / 2 - RES_Y / 6 + 40);
	else if (game->data->mouse.on_clk[1])
		mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.gun.mlx_img, (RES_X - game->data->intro.start.x) / 2 - 70, (RES_Y - game->data->intro.sett.y) / 2 - RES_Y / 12 + 40);
	else if (game->data->mouse.on_clk[2])
		mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.gun.mlx_img, (RES_X - game->data->intro.start.x) / 2 - 40, (RES_Y - game->data->intro.exit.y) / 2 + 40);
	else if (game->data->mouse.on_hov[0])
		mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.gun.mlx_img, (RES_X - game->data->intro.start.x) / 2 - 40, (RES_Y - game->data->intro.start.y) / 2 - RES_Y / 6 + 40);
	else if (game->data->mouse.on_hov[1])
		mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.gun.mlx_img, (RES_X - game->data->intro.start.x) / 2 - 70, (RES_Y - game->data->intro.sett.y) / 2 - RES_Y / 12 + 40);
	else if (game->data->mouse.on_hov[2])
		mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.gun.mlx_img, (RES_X - game->data->intro.start.x) / 2 - 40, (RES_Y - game->data->intro.exit.y) / 2 + 40);
}

void    paint_img2(t_img *img, int x_w, int y_w, int color, t_game *game)
{
	t_img img2;
	int x;
	int y;

	img2.mlx_img = mlx_new_image(game->data->mlx.mlx_ptr, img->x, img->y);
	img2.addr = mlx_get_data_addr(img2.mlx_img, &img2.bpp, &img2.line_len, &img2.endian);
	y = -1;
	while (++y < img->y)
	{
		x = -1;
		while (++x < img->x)
			if ((unsigned int)get_img_color(img, x, y, game) != 0xff000000 && color >= 2)
				img_pix_put(&img2, x, y, 0xffffff * (mm % 200 < 100) + 0xff0000 * (mm % 200 >= 100));
			else if ((unsigned int)get_img_color(img, x, y, game) != 0xff000000 && color)
				img_pix_put(&img2, x, y, 0xff0000);
			else
				img_pix_put(&img2, x, y, get_img_color(img, x, y, game));
	}
	mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, img2.mlx_img, x_w, y_w);
	mlx_destroy_image(game->data->mlx.mlx_ptr, img2.mlx_img);
	mm++;
}

void    render_control(t_game *game)
{
	mlx_clear_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr);
	if (!game->data->mouse.sett2)
	{
		mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.int2.mlx_img, 0, 0);
		mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.tr.mlx_img, 0, 0);
	}
	else
	{
		mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->img.mlx_img, 0, 0);
		mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->objects.time[game->data->objects.t4].mlx_img, RES_X - 142, 30);
		mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->objects.time[game->data->objects.t3].mlx_img, RES_X - 142 + 30, 30);
		mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->objects.time[game->data->objects.t2].mlx_img, RES_X - 132 + 60, 30);
		mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->objects.time[game->data->objects.t1].mlx_img, RES_X - 132 + 90, 30);
		mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.tr2.mlx_img, 0, 0);
	}
	mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.guide[0].mlx_img, 100, 120);
	mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.guide[game->data->intro.g_k[0] + 1].mlx_img, 450, 130);
	paint_img2(&game->data->intro.guide[3], 400, 120, game->data->intro.on_hov[3], game);
	paint_img2(&game->data->intro.guide[4], 574, 120, game->data->intro.on_hov[4], game);

	// mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.vol_icon[(game->data->intro.volume > 99) + (game->data->intro.volume == 200) + !!(game->data->intro.volume % 100)].mlx_img, 825, 115);
	// mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.vol[0].mlx_img, 900, 135);
	// mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.vol[1].mlx_img, 900 + game->data->intro.volume - 12, 120);

	// mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.light_icon[1].mlx_img, 1200, 115);
	// mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.lgt[0].mlx_img, 1275, 135);
	// mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.lgt[1].mlx_img, 1275 + game->data->intro.light - 12, 120);

	mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.vol_icon[(game->data->intro.volume > 99) + (game->data->intro.volume == 200) + !!(game->data->intro.volume % 100)].mlx_img, 1025, 70);
	mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.vol[0].mlx_img, 1100, 90);
	mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.vol[1].mlx_img, 1100 + game->data->intro.volume - 12, 75);

	mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.light_icon[1].mlx_img, 1025, 165);
	mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.lgt[0].mlx_img, 1100, 185);
	mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.lgt[1].mlx_img, 1100 + game->data->intro.light - 12, 170);

	paint_img2(&game->data->intro.guide[5], 100, 280, game->data->intro.on_clk[5] + game->data->intro.on_hov[5], game);
	mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.keys[game->data->intro.g_k[1]], 450, 260 - 20);

	paint_img2(&game->data->intro.guide[6], 800, 280, game->data->intro.on_clk[6] + game->data->intro.on_hov[6], game);
	mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.keys[game->data->intro.g_k[2]], 800 + 350, 280 - 20);

	paint_img2(&game->data->intro.guide[7], 100, 400, game->data->intro.on_clk[7] + game->data->intro.on_hov[7], game);
	mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.keys[game->data->intro.g_k[3]], 450, 400 - 20);

	paint_img2(&game->data->intro.guide[8], 800, 400, game->data->intro.on_clk[8] + game->data->intro.on_hov[8], game);
	mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.keys[game->data->intro.g_k[4]], 800 + 350, 400 - 20);

	paint_img2(&game->data->intro.guide[9], 100, 520, game->data->intro.on_clk[9] + game->data->intro.on_hov[9], game);
	mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.keys[game->data->intro.g_k[5]], 450, 520 - 25);

	paint_img2(&game->data->intro.guide[10], 800, 520, game->data->intro.on_clk[10] + game->data->intro.on_hov[10], game);
	mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.keys[game->data->intro.g_k[6]], 800 + 350, 520 - 25);

	paint_img2(&game->data->intro.guide[11], 100, 640, game->data->intro.on_clk[11] + game->data->intro.on_hov[11], game);
	mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.keys[game->data->intro.g_k[7]], 450, 640 - 25);

	paint_img2(&game->data->intro.guide[12], 800, 640, game->data->intro.on_clk[12] + game->data->intro.on_hov[12], game);
	mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.keys[game->data->intro.g_k[8]], 800 + 350, 640 - 25);

	paint_img2(&game->data->intro.guide[13], 100, 760, game->data->intro.on_clk[13] + game->data->intro.on_hov[13], game);
	mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.keys[game->data->intro.g_k[9]], 450, 760 - 25);

	paint_img2(&game->data->intro.guide[14], 800, 760, game->data->intro.on_clk[14] + game->data->intro.on_hov[14], game);
	mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.keys[game->data->intro.g_k[10]], 800 + 350, 760 - 25);

	paint_img2(&game->data->intro.guide[15], 100, 880, game->data->intro.on_clk[15] + game->data->intro.on_hov[15], game);
	mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.keys[game->data->intro.g_k[11]], 450, 880 - 25);

	setting_render(&game->data->intro.back, RES_X / 2 - 300, RES_Y - 100, 5, game);
	setting_render(&game->data->intro.reset, RES_X / 2, RES_Y - 100, 6, game);
}

int get_lava_color(int x, int y, t_game *game)
{
    return (*(int *)(game->data->blood_hit.addr + (y * game->data->blood_hit.line_len + x * (game->data->blood_hit.bpp / 8))));
}
void	paint_hit_blood(t_game *game)
{
	int i;
	int j;

	i = -1;
	while (++i < RES_Y)
	{
		j = -1;
		while (++j < RES_X)
			if ((unsigned int)get_lava_color(j, i, game) != 0xff000000)
				img_pix_put(&game->data->blood_hit2, j, i, get_lava_color(j, i, game) + ((((game->data->bld * !(((game->data->bld) / 25) % 2)) % 25 + ((25 - game->data->bld % 25) * (((game->data->bld) / 25) % 2)) % 25) * 3 + 175) << 24));
	}
}

void    render_game(t_game *game)
{
	if (cnt == 10)
	{
		// usleep(20000);
		cnt = 0;
		if (game->data->objects.health > 0)
		{
			if (game->data->keys[game->data->intro.g_k[1]] && !game->data->keys[game->data->intro.g_k[9]] && (!game->data->fov.jumping && game->data->dir.ph >= 0.5))
				game->data->c += 3 * (!!((game->data->mv / 5) % 2) - !((game->data->mv / 5) % 2)),
				game->data->g_mv -= 3 * (!!((game->data->mv / 5) % 2) - !((game->data->mv++ / 5) % 2)),
				up(game->data);
			if (game->data->keys[game->data->intro.g_k[2]] && !game->data->keys[game->data->intro.g_k[9]])
				game->data->c += 3 * (!!((game->data->mv / 5) % 2) - !((game->data->mv / 5) % 2)),
				game->data->g_mv -= 3 * (!!((game->data->mv / 5) % 2) - !((game->data->mv++ / 5) % 2)),
				down(game->data);
			if (game->data->gun[game->data->objects.w].bullet && game->data->keys[game->data->intro.g_k[8]] && game->data->aim < 10)
			{
				if (game->data->objects.w == 17)
					game->data->gun[game->data->objects.w].frame = 53 + game->data->aim;
				game->data->aim++;
			}
			else if ((!game->data->keys[game->data->intro.g_k[8]] || !game->data->gun[game->data->objects.w].bullet) && game->data->aim > 0)
			{
				if (game->data->objects.w == 17)
					game->data->gun[game->data->objects.w].frame = 53 + game->data->aim;
				if (game->data->objects.w == 17 && game->data->aim == 1)
					game->data->gun[game->data->objects.w].frame = 15;
				if (game->data->zoom > 0)
					game->data->zoom--;
				else
					game->data->aim--;
			}
			if (game->data->objects.w == 4 && game->data->use_gun++ > 100)
			{
				game->data->gun[game->data->objects.w].frame++;
				if (game->data->gun[game->data->objects.w].frame < game->data->gun[game->data->objects.w].f_reload)
					game->data->gun[game->data->objects.w].frame = game->data->gun[game->data->objects.w].f_reload;
				if (game->data->gun[game->data->objects.w].frame == 51)
					game->data->gun[game->data->objects.w].frame = 0,
					game->data->use_gun = 0;
			}
			else if (game->data->objects.w == 17 && (game->data->gun[game->data->objects.w].bullet || game->data->gun[game->data->objects.w].case_bullet) && (game->data->keys[game->data->intro.g_k[7]] || game->data->gun[game->data->objects.w].frame || !game->data->gun[game->data->objects.w].bullet))
			{
				if (game->data->aim && game->data->objects.w == 17)
				{
					if (game->data->keys[game->data->intro.g_k[7]] || game->data->gun[game->data->objects.w].frame > 63)
						game->data->gun[game->data->objects.w].frame++;
					if (game->data->gun[game->data->objects.w].frame > 80 && game->data->gun[game->data->objects.w].bullet)
						game->data->gun[game->data->objects.w].frame = 63,
						game->data->gun[game->data->objects.w].bullet--;
				}
				else
				{
					game->data->gun[game->data->objects.w].frame++;
					if (!game->data->gun[game->data->objects.w].bullet && game->data->gun[game->data->objects.w].frame < game->data->gun[game->data->objects.w].f_shoot)
						game->data->gun[game->data->objects.w].frame = game->data->gun[game->data->objects.w].f_shoot;
					if (game->data->gun[game->data->objects.w].frame > game->data->gun[game->data->objects.w].f_shoot && game->data->gun[game->data->objects.w].bullet)
						game->data->gun[game->data->objects.w].frame = 0,
						game->data->gun[game->data->objects.w].bullet--;
					if (game->data->gun[game->data->objects.w].frame > game->data->gun[game->data->objects.w].f_reload && !game->data->gun[game->data->objects.w].bullet)
						game->data->gun[game->data->objects.w].frame = 0,
						game->data->gun[game->data->objects.w].case_bullet--,
						game->data->gun[game->data->objects.w].bullet = 12;
					game->data->use_gun = 0;
					if (game->data->gun[game->data->objects.w].frame < 2 && game->data->objects.w == 13 && game->data->keys[game->data->intro.g_k[7]] && (game->data->gun[game->data->objects.w].bullet || game->data->gun[game->data->objects.w].case_bullet))
						game->data->gun[game->data->objects.w].frame = 2;
				}
			}
			else if (game->data->objects.w != 17 && (game->data->gun[game->data->objects.w].bullet || game->data->gun[game->data->objects.w].case_bullet) && (game->data->keys[game->data->intro.g_k[7]] || game->data->gun[game->data->objects.w].frame || !game->data->gun[game->data->objects.w].bullet))
			{
				if (!game->data->gun[game->data->objects.w].frame && game->data->show_health && game->data->color_maping[RES_Y / 2][RES_X / 2] == '*' && game->data->enemy[0].health > 0)
					game->data->enemy[i].hit = (game->data->enemy[0].health % 2),
					game->data->enemy[i].motion = 5,
					game->data->enemy[0].health -= 105,
					game->data->enemy[i].frm = 1;
				else if (!game->data->gun[game->data->objects.w].frame && game->data->show_health && game->data->color_maping[RES_Y / 2][RES_X / 2] == '*' && game->data->enemy[0].health <= 0)
				{
					game->data->enemy[i].hit = -1;
					game->data->enemy[i].motion = 6;
					if (game->data->enemy[i].frm == game->data->motion[6].frame - 1)
						game->data->enemy[i].frm = 66;
				}
				game->data->gun[game->data->objects.w].frame++;



				if (!game->data->gun[game->data->objects.w].bullet && game->data->gun[game->data->objects.w].frame < game->data->gun[game->data->objects.w].f_shoot)
					game->data->gun[game->data->objects.w].frame = game->data->gun[game->data->objects.w].f_shoot;
				if (game->data->gun[game->data->objects.w].frame > game->data->gun[game->data->objects.w].f_shoot && game->data->gun[game->data->objects.w].bullet)
					game->data->gun[game->data->objects.w].frame = 0,
					game->data->gun[game->data->objects.w].bullet--;
				if (game->data->gun[game->data->objects.w].frame > game->data->gun[game->data->objects.w].f_reload && !game->data->gun[game->data->objects.w].bullet)
					game->data->gun[game->data->objects.w].frame = 0,
					game->data->gun[game->data->objects.w].case_bullet--,
					game->data->gun[game->data->objects.w].bullet = 12;
				game->data->use_gun = 0;
				if (game->data->gun[game->data->objects.w].frame < 2 && game->data->objects.w == 13 && game->data->keys[game->data->intro.g_k[7]] && (game->data->gun[game->data->objects.w].bullet || game->data->gun[game->data->objects.w].case_bullet))
					game->data->gun[game->data->objects.w].frame = 2;
			}
			else if (game->data->objects.w == 9 && (game->data->keys[game->data->intro.g_k[7]] || game->data->gun[game->data->objects.w].frame))
			{
				game->data->gun[game->data->objects.w].frame++;
				if (game->data->gun[game->data->objects.w].frame > game->data->gun[game->data->objects.w].f_shoot)
					game->data->gun[game->data->objects.w].frame = 0;
			}

			if (!game->data->intro.g_k[0])
			{
				if (game->data->keys[UP])
					game->data->c -= 25 * (-game->data->c + 25 < RES_Y - 200);
				if (game->data->keys[DOWN])
					game->data->c += 25 * (game->data->c + 25 < RES_Y - 200);
				if (game->data->keys[LEFT])
					left_angle(game, game->data);
				if (game->data->keys[RIGHT])
					right_angle(game, game->data);
			}
			if (game->data->keys[game->data->intro.g_k[3]])
				game->data->c += 3 * (!!((game->data->mv / 5) % 2) - !((game->data->mv / 5) % 2)),
				game->data->g_mv -= 3 * (!!((game->data->mv / 5) % 2) - !((game->data->mv++ / 5) % 2)),
				left(game->data);
			if (game->data->keys[game->data->intro.g_k[4]])
				game->data->c += 3 * (!!((game->data->mv / 5) % 2) - !((game->data->mv / 5) % 2)),
				game->data->g_mv -= 3 * (!!((game->data->mv / 5) % 2) - !((game->data->mv++ / 5) % 2)),
				right(game->data);
			if (game->data->fov.jumping && game->data->dir.ph > 0.2)
				game->data->speed = -1,
				game->data->dir.ph -= 0.07,
				up(game->data);
			else if (ac >= 2)
				game->data->fov.jumping = 0;
			else if (game->data->fov.jumping)
				ac++,
				up(game->data);
			if (!game->data->fov.jumping && game->data->dir.ph < 0.5)
				ac = 0,
				game->data->speed = -1,
				game->data->dir.ph += 0.07,
				up(game->data);

			if (!game->data->sound.breath && !game->data->keys[game->data->intro.g_k[2]] && game->data->keys[game->data->intro.g_k[9]] && abs(game->data->c) < 10 && (!game->data->fov.jumping && game->data->dir.ph >= 0.5))
				c++,
				game->data->speed = 3,
				game->data->c = (ac++ % 4) * (c % 4 - !(c % 4)),
				up(game->data);
			else if (!game->data->sound.breath && !game->data->keys[game->data->intro.g_k[2]] && game->data->keys[game->data->intro.g_k[9]] && (!game->data->fov.jumping && game->data->dir.ph >= 0.5))
				c++,
				game->data->speed = 3,
				game->data->c += (15 * (game->data->c < 0) - 15 * (game->data->c > 0)) * !!(c % 3) + (3 * (game->data->c > 0) - 3 * (game->data->c < 0)) * !(c % 3),
				up(game->data);

			if (game->data->sound.breath && abs(game->data->c) < 40)
				c++,
				game->data->c = 3.0 / 20.0 * (ac++ % 20) * (c % 20 - !(c % 20));
			else if (game->data->sound.breath)
				c++,
				game->data->c += 3.0 / 18.0 * (15 * (game->data->c < 0) - 15 * (game->data->c > 0)) * !!(c % 18) + (18 * (game->data->c > 0) - 18 * (game->data->c < 0)) * !(c % 18);

			if (game->data->fov.crouching && game->data->dir.ph < 0.8)
				game->data->dir.ph += 0.05;
			if (!game->data->fov.crouching && game->data->dir.ph > 0.5)
				game->data->dir.ph -= 0.05;
		}
		game->data->door.is_op = 1;
		if (game->data->keys[game->data->intro.g_k[6]] || game->data->keys[999 - SCROLL_UP] || game->data->keys[999 - SCROLL_DOWN] || game->data->keys[game->data->intro.g_k[9]] || game->data->keys[UP] || game->data->keys[game->data->intro.g_k[1]] || game->data->keys[DOWN] || game->data->keys[game->data->intro.g_k[2]] || game->data->keys[LEFT] || game->data->keys[RIGHT] || game->data->keys[game->data->intro.g_k[3]] || game->data->keys[game->data->intro.g_k[4]])
			set_char_to_win(game),
			mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.lt.mlx_img, 0, 0);
		game->data->speed = -3 * game->data->fov.crouching;
		if (game->data->door.map[(game->data->dir.y + 17) / 50][(game->data->dir.x + 17) / 50] == 'E' && game->data->objects.health
			&& game->data->map[(int)game->data->dir.y / 50][(int)game->data->dir.x / 50] == '0'
			&& (game->data->map[(int)game->data->dir.y / 50 - 1][(int)game->data->dir.x / 50] != game->data->map[(int)game->data->dir.y / 50 + 1][(int)game->data->dir.x / 50]
			|| game->data->map[(int)game->data->dir.y / 50][(int)game->data->dir.x / 50 - 1] != game->data->map[(int)game->data->dir.y / 50][(int)game->data->dir.x / 50 + 1])
			&& game->data->dir.ph >= 0.5)
			paint_hit_blood(game),
			mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->blood_hit2.mlx_img, 0, 0),
			game->data->bld += !(game->data->light % 5),
			game->data->bld = game->data->bld * (game->data->bld != 50),
			game->data->objects.health -= !(game->data->light % 5),
			game->data->sound.hit = !(game->data->objects.health % 3);

			if ((!game->data->keys[game->data->intro.g_k[9]] || (game->data->keys[game->data->intro.g_k[9]] && game->data->sound.breath)) && game->data->objects.breath < 100)
				game->data->objects.breath += !(game->data->light % 5);
	}
	cnt++;
	if (game->data->door.op > 0 && game->data->door.is_op)
		game->data->door.op -= cnt / 7;
	if (game->data->door.op < 45 && !game->data->door.is_op)
		game->data->door.op += cnt / 7;
	if (!game->data->mouse.sett2)
		game->data->mouse.sett2 = 1;
}

void	render_map(t_game *game)
{
	usleep(1000);
	if (game->data->intro.up && game->data->intro.map < 75 && !game->data->intro.map++)
		set_char_to_win(game);
	if (!game->data->intro.up)
		game->data->intro.map--;
	if (!game->data->intro.up && !game->data->intro.map)
		game->data->mode = GAME;
	mlx_clear_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr);
    mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->img.mlx_img, 0, 0);

    mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->objects.time[game->data->objects.t4].mlx_img, RES_X - 142, 30);
    mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->objects.time[game->data->objects.t3].mlx_img, RES_X - 142 + 30, 30);
    mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->objects.time[game->data->objects.t2].mlx_img, RES_X - 132 + 60, 30);
    mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->objects.time[game->data->objects.t1].mlx_img, RES_X - 132 + 90, 30);

	if (game->data->intro.map > 25)
		mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.tr2.mlx_img, 0, 0);
	else
		mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.lt.mlx_img, 0, 0);
	map_appending();
	if (game->data->intro.map > 25)
		mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->mouse.img, game->data->mouse.x, game->data->mouse.y);
}

int rendering(void *d,t_game *game)
{
	d = NULL;
	if (game->data->mouse.clicked == 128)
		i = 0,
		f = 0,
		game->data->mouse.clicked = 0,
		game->data->mode = INTRO2;
	if (game->data->mode == INTRO)
		render_intro(game);
	if (game->data->mode == INTRO1)
		render_intro1(game);
	if (game->data->mode == INTRO2)
		render_intro2(game);
	if (game->data->mode == SETTING)
		render_setting(game);
	if (game->data->mode == SETTING2)
		render_setting2(game);
	if (game->data->mode == ANIMATE_SETT2_IN)
		animate_sett_in(game);
	if (game->data->mode == ANIMATE_SETT2_OUT)
		animate_sett_out(game);
	if (game->data->mode == S_CONTROL)
		render_control(game);
	if (game->data->mode == G_MAP)
		render_map(game);
	if (game->data->mode == GAME)
		game->data->intro.map = 0,
		render_game(game);
	else if (game->data->mouse.x != 10000 && game->data->mode != G_MAP && game->data->mode != GAME)
		mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->mouse.img, game->data->mouse.x, game->data->mouse.y),
		mlx_put_image_to_window(game->data->mlx.mlx_ptr, game->data->mlx.win_ptr, game->data->intro.lt.mlx_img, 0, 0);
	return (0);
}
