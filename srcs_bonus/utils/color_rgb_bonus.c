/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_rgb_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:35:34 by janhan            #+#    #+#             */
/*   Updated: 2024/05/30 15:51:33 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"

int	color_spoid(int x, int y, t_img *img)
{
	char	*dst;
	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
	{
		return 0;
	}
	dst = img->addr + (y * img->line_length + x * (img->bit_per_pixel >> 3));
	return (*(int *)dst);
}
