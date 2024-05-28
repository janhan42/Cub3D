/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 20:26:51 by sangshin          #+#    #+#             */
/*   Updated: 2024/05/28 18:34:03 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_mand/header_mand.h"

/*

dots.start_x, dots.start_y, dots.dest_x, dots.dest_y
 x0            y0              x1          y1
*/
void	one_line(t_img *img, t_2dot *dots, int color)
{
	const int	dx = dots->dest_x - dots->start_x;
	const int	dy = dots->dest_y - dots->start_y;
	t_vec2d		vec;
	int			steps;
	int			i;

	i = 0;
	vec.x = dots->start_x;
	vec.y = dots->start_y;
	steps = abs(dx) * (abs(dx) > abs(dy)) + abs(dy) * (abs(dx) <= abs(dy));
	while (i <= steps)
	{
		put_pixel_on_img(img, (int)vec.x, (int)vec.y, color);
		vec.x += dx / (double)steps;
		vec.y += dy / (double)steps;
		i++;
	}
}

void	draw_line(t_img *img, t_2dot dots, int color)
{
	int	offset;

	if (dots.start_x == dots.dest_x)
	{
		offset = (dots.start_y > dots.dest_y) * -1
			+ (dots.start_y < dots.dest_y) * 1;
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
		while (dots.start_x != dots.dest_x)
		{
			put_pixel_on_img(img, dots.start_x, dots.start_y, color);
			dots.start_x += offset;
		}
	}
	else
		one_line(img, &dots, color);
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
	char	*dst;

	if (x >= img->width || y >= img->height || x < 0 || y < 0)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bit_per_pixel >> 3));
	*(unsigned int *)dst = color;
}

// TODO: 이미지 스케일링 함수인데 전달 방식 및 처리 방식의 개편이 필요
/**
 * @brief
 *
 * @param src 변환전 오리지널 이미지 구조체.
 * @param dst 스케일링후 이미지를 넣을 구조체.
 * @param scale_factor 스케일
 */
void	scale_texture(t_img *src, t_img *dst, float scale_factor)
{
	t_single_scale	info;

	info.scale = 1.0 / scale_factor;
	info.new_y = 0;
	while (info.new_y < dst->height)
	{
		info.new_x = 0;
		while (info.new_x < dst->width)
		{
			info.x = (int)(info.new_x * info.scale);
			info.y = (int)(info.new_y * info.scale);
			if (info.x >= src->width || info.y >= src->height)
				continue ;
			info.color = *(int *)(src->addr + (info.y * src->line_length
						+ info.x * (src->bit_per_pixel / 8)));
			*(int *)(dst->addr + (info.new_y * dst->line_length + info.new_x
						* (dst->bit_per_pixel / 8))) = info.color;
			info.new_x++;
		}
		info.new_y++;
	}
}
