/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 22:34:45 by sangshin          #+#    #+#             */
/*   Updated: 2024/05/15 15:00:43 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	render_mini_map(t_img *img, char **map)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	y = 0;
	while (map[i])
	{
		j = 0;
		x = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
				draw_square_on_img(img, x, y, 0x00FFFFFF);
			else
				draw_square_on_img(img, x, y, 0x00000000);
			x += MINI_MAP_PIXEL;
			j++;
		}
		y += MINI_MAP_PIXEL;
		i++;
	}
}
void	draw_player(t_img *img, t_game *game)
{
	const int r = 8;
	int	i;
	int	j;
	t_2dot dots;

	i = -r;
	while (i < r)
	{
		j = -r;
		while (j < r)
		{
			if (i * i + j * j <= r * r)
				put_pixel_on_img(img, game->player->player_x / (int)(PIXEL / MINI_MAP_PIXEL) + j,
					game->player->player_y / (int)(PIXEL / MINI_MAP_PIXEL) + i, 0x00FF0000);
			j++;
		}
		i++;
	}
	dots.start_x = game->player->player_x;
	dots.start_y = game->player->player_y;
	dots.dest_x = game->player->player_x + 20 * cos(game->player->player_rad);
	dots.dest_y = game->player->player_y + 20 * sin(game->player->player_rad);
	draw_line(img, dots, 0x00FF0000);
}

void	render_3d(t_game *game)
{
	t_dest	*f_dest;
	/*
	 * f_dest[0] = x좌표
	 * f_dest[1] = y
	 * f_dest[2] = distance
	 * f_dest[3] = direction
	 */
	double	ray_direction;
	double	ca;
	int t;

	t = 0;
	ray_direction = game->player->player_rad - (0.002 * 320);
	while (ray_direction <= game->player->player_rad + (0.002 * 320))
	{
		f_dest = get_dest(game->player->player_x, game->player->player_y,
					ray_direction, game);
		//printf("x, y : (%d, %d)\n", f_dest->x, f_dest->y);
		//draw_line(img, game->player_x, game->player_y, f_dest[0], f_dest[1], 0x00FF0000);
		ca = game->player->player_rad - ray_direction;
		f_dest->distance = f_dest->distance * cos(ca);
		render(game, f_dest->distance, t, f_dest->direction);
		//texture_map(game, f_dest, t);
		free(f_dest);
		//printf("%f\n", ray_direction);
		ray_direction += 0.002;
		t++;
	}
}

int	color_spoid(int x, int y, t_img *img)
{
	char *dst;

	dst = img->addr + (y * img->line_length + x * (img->bit_per_pixel >> 3));
	return (*(int *)dst);
}
void	texture_map(t_game *game, t_dest *dest, int t)
{
	// 테스트용
	const int	wall_x = (dest->x + 1) & 63;
	const int	wall_y = (dest->y + 1) & 63;

	//printf("wall_x : [%d] wall_y : [%d]\n", wall_x, wall_y);
	int	texture_x;

	if (wall_x > wall_y)
		texture_x = wall_x;
	else
		texture_x = wall_y;
	double	line_h = 1080 / dest->distance * 70; // -> line의 길이
	double	step = 0.9 * game->texture->height / line_h;
	texture_x = texture_x * game->texture->width / 70;
	//printf("step [%f]\n", step);
	int		color;
	int	x;
	int	y;
	int	h_offset;
	double	step_x;
	double	step_y;

	h_offset = (int)(1080 / 2) - (line_h / 2) + game->player->player_fov_off_y;
	// 화면 중앙 빼기 -
	step_y = 0;
	y = 0;
	x = t * 3;
	while ((int)step_y < game->texture->height)
	{
		color = color_spoid(texture_x, (int)step_y, game->texture);
		put_pixel_on_img(game->render, x, y + h_offset, color);
		put_pixel_on_img(game->render, x + 1, y + h_offset, color);
		put_pixel_on_img(game->render, x + 2, y + h_offset, color);
		step_y += step;
		y++;
	}
}

void	render(t_game *game, double distance, int time, int side)
{
	t_img	*render;
	double	line_h;
	int		mid;
	t_2dot	dots;
	int	color;
	int	i;
	i = 0;

	if (side == 0) // left
		color = 0x00996666;
	else if (side == 1) // up
		color = 0x00ff6600;
	else if (side == 2) // right
		color = 0x00ff9933;
	else				// down
		color = 0x00cc6600;

	mid = 1080/2;
	mid += game->player->player_fov_off_y;
	line_h = (1080/(distance)) * 70;
	render = game->render;
	dots.start_x = time * 3;
	dots.start_y = mid;
	dots.dest_x = time * 3;
	while (i < 3)
	{
		dots.dest_y = mid - line_h / 2;
			dots.start_x += 1;
			dots.dest_x += 1;
		if (dots.dest_y < 0)
			dots.dest_y = 0;
		draw_line(render, dots, color/*create_color_hex(255, 255, 255, distance / 255)*/);
		dots.dest_y = mid + line_h/2;
		if (dots.dest_y > WINDOW_H)
			dots.dest_y = WINDOW_H;
		draw_line(render, dots, color/*create_color_hex(255, 255, 255, distance / 255)*/);
		i++;
	}
	// draw_line(render, time * 3, mid, time * 3, mid - line_h/2, 0x0000FF00);
	// draw_line(render, time * 3, mid, time * 3, mid + line_h/2, 0x0000FF00);

}
