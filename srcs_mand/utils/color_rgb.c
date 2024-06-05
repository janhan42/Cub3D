/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:35:34 by janhan            #+#    #+#             */
/*   Updated: 2024/06/05 19:20:05 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_mand/header_mand.h"

int	color_spoid(int x, int y, t_img *img)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bit_per_pixel >> 3));
	return (*(int *)dst);
}

void	int_to_rgb(int rgb, int *r, int *g, int *b)
{
	*r = (rgb >> 16) & 0xFF;
	*g = (rgb >> 8) & 0xFF;
	*b = rgb & 0xFF;
}

int	rgb_to_int(int r, int g, int b)
{
	int	result;

	result = (r << 16) | (g << 8) | b;
	return (result);
}
