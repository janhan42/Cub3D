/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_rgb_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:35:34 by janhan            #+#    #+#             */
/*   Updated: 2024/05/28 17:25:53 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"

int	color_spoid(int x, int y, t_img *img)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bit_per_pixel >> 3));
	return (*(int *)dst);
}
