/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 22:34:45 by sangshin          #+#    #+#             */
/*   Updated: 2024/05/27 08:32:11 by janhan           ###   ########.fr       */
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
			else if (map[i][j] == 'D')
				draw_square_on_img(img, x, y, 0xD0D7FE);
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
	dots.start_x = game->player->player_x / (int)(PIXEL / MINI_MAP_PIXEL);
	dots.start_y = game->player->player_y / (int)(PIXEL / MINI_MAP_PIXEL);
	dots.dest_x = game->player->player_x / (int)(PIXEL / MINI_MAP_PIXEL) + 20 * cos(game->player->player_rad);
	dots.dest_y = game->player->player_y / (int)(PIXEL / MINI_MAP_PIXEL)+ 20 * sin(game->player->player_rad);
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
	const double	ray_destination = game->player->player_rad + (0.000545415391 * WINDOW_W / 2);
	double	ca;
	int t;

	t = 0;
	ray_direction = game->player->player_rad - (0.000545415391 * WINDOW_W / 2);
	while (ray_direction <= ray_destination)
	{
		f_dest = get_dest(game->player->player_x, game->player->player_y,
					ray_direction, game);
		ca = game->player->player_rad - ray_direction;
		f_dest->distance = f_dest->distance * cos(ca);
		texture_map(game, f_dest, t);
		free(f_dest);
		ray_direction += 0.000545415391;
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
	int	wall_x;
	int	wall_y;
	int	texture_x;
	t_img	*texture;


	texture = get_texture(game, dest);
	wall_x = (dest->x + 1) & 63;
	wall_y = (dest->y + 1) & 63;
	if (wall_x > wall_y)
		texture_x = wall_x * game->texture->width >> 6;
	else
		texture_x = wall_y * game->texture->width >> 6;

	if (dest->distance < 1)
		dest->distance = 1;
	int	line_h = (WINDOW_H / dest->distance) * 100; // -> line의 길이
	double	step = 1.0 * game->texture->height / line_h;
	//texture_x = texture_x * game->texture->width / 70;
	//printf("step [%f]\n", step);
	int		color;
	int	x;
	int	y;
	int	h_offset;
	double	step_y;

	h_offset = (int)(WINDOW_H / 2) - (line_h / 2) + game->player->player_fov_off_y;
	// 화면 중앙 빼기 -
	step_y = 0;
	y = 0;
	x = t;
	int	i = 0;
	while (i < h_offset)
	{
		put_pixel_on_img(game->render, x, i, game->ceiling_color);
		i++;
	}
	while (y < line_h) // 라인의 길이
	{
		if (y + h_offset > WINDOW_H)
			return ;
		while (y + h_offset < 0)
		{
			step_y += step;
			y++;
		}
		color = color_spoid(texture_x, (int)step_y, texture);
		put_pixel_on_img(game->render, x, y + h_offset, color);
		step_y += step;
		y++;
	}
	while (y + h_offset < WINDOW_H)
	{
		put_pixel_on_img(game->render, x, y + h_offset, game->floor_color);
		y++;
	}
}
/*
 * line_h / 64
 */

/* wall_x 0 ~ 63
 *  -> 0 ~ 1023
 *
 *  64: 1024 = wall_x : texture_x
 *
 *  1024 * wx = 64 * tx;
 *  tx = 1024 * wx / 64
 */

t_img	*get_texture(t_game *game, t_dest *dest)
{
	if (dest->wall_type == EAST)
		return (&game->texture[EAST]);
	if (dest->wall_type == NORTH)
		return (&game->texture[NORTH]);
	if (dest->wall_type == WEST)
		return (&game->texture[WEST]);
	if (dest->wall_type == SOUTH)
		return (&game->texture[SOUTH]);
	else // door
		return (&game->texture[DOOR]);
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
	dots.start_x = time;// * 3;
	dots.start_y = mid;
	dots.dest_x = time;// * 3;
	while (i < 1)
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
