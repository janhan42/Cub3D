/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 20:26:51 by sangshin          #+#    #+#             */
/*   Updated: 2024/05/14 18:25:37 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	one_line(t_img *img, int x0, int y0, int x1, int y1, int color)
{
	const int	dx = x1 - x0;
	const int	dy = y1 - y0;
	t_vec2d		vec;
	int			steps;

	vec.x = x0;
	vec.y = y0;
	steps = abs(dx) * (abs(dx) > abs(dy)) + abs(dy) * (abs(dx) <= abs(dy));
	for (int i = 0; i <= steps; i++)
	{
		put_pixel_on_img(img, (int)vec.x, (int)vec.y, color);
		vec.x += dx / (double)steps;
		vec.y += dy / (double)steps;
	}
}

void	draw_line(t_img *img, t_2dot dots, int color)
{
	int	offset;

	if (dots.start_x == dots.dest_x)
	{
		offset = (dots.start_y > dots.dest_y) * -1
			+ (dots.start_y < dots.dest_y) * 1;
		printf("offset : [%d]\n", offset);
		while (dots.start_y != dots.dest_y)
		{
			put_pixel_on_img(img, dots.start_x, dots.start_y, color);
			dots.start_y += offset;
		}
	}
	else if (dots.start_y == dots.dest_y)
	{
		offset = (dots.start_x > dots.dest_x) * -1
			+ (dots.start_x < dots.dest_x) * 1;
		printf("offset : [%d]\n", offset);
		while (dots.start_x != dots.dest_x)
		{
			put_pixel_on_img(img, dots.start_x, dots.start_y, color);
			dots.start_x += offset;
		}
	}
	else
		one_line(img, dots.start_x, dots.start_y,
		dots.dest_x, dots.dest_y, color);
}

/**
 * @brief
 * 상단 우측 img 수정
 * @param img
 * @param x
 * @param y
 * @param color
 */
void	draw_square_on_img(t_img *img, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINI_MAP_PIXEL)
	{
		j = 0;
		while (j < MINI_MAP_PIXEL)
		{
			put_pixel_on_img(img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	put_pixel_on_img(t_img	*img, int x, int y, int color)
{
	char *dst;

	if (x >= img->width || y >= img->height || x < 0 || y < 0)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bit_per_pixel >> 3));
	*(unsigned int *)dst = color;
}
