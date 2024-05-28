/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mini_map_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:26:52 by janhan            #+#    #+#             */
/*   Updated: 2024/05/28 17:24:56 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"

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
