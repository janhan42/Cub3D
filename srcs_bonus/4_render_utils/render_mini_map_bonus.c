/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mini_map_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:26:52 by janhan            #+#    #+#             */
/*   Updated: 2024/05/28 20:20:08 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"

// void	render_mini_map(t_img *img, char **map)
// {
// 	int	i;
// 	int	j;
// 	int	x;
// 	int	y;
//
// 	i = 0;
// 	y = 0;
// 	while (map[i])
// 	{
// 		j = 0;
// 		x = 0;
// 		while (map[i][j])
// 		{
// 			if (map[i][j] == '1')
// 				draw_square_on_img(img, x, y, 0x00FFFFFF);
// 			else if (map[i][j] == 'D')
// 				draw_square_on_img(img, x, y, 0xD0D7FE);
// 			else
// 				draw_square_on_img(img, x, y, 0x00000000);
// 			x += MINI_MAP_PIXEL;
// 			j++;
// 		}
// 		y += MINI_MAP_PIXEL;
// 		i++;
// 	}
// }

void	render_mini_map(t_game *game)
{
	const int	px = game->player->player_x / PIXEL;
	const int	py = game->player->player_y / PIXEL;

	int	i;
	int	j;
	int	x;
	int	y;

	i = py - MINI_MAP_RADIUS;

	y = 0;
	while (i <= py + MINI_MAP_RADIUS)
	{
		x = 0;
		j = px - MINI_MAP_RADIUS;
		while (j <= px + MINI_MAP_RADIUS)
		{
			if (i < 0 || i > game->map_len_h - 1 || j < 0 || j > ft_strlen(game->map[i]) - 1 || game->map[i][j] == ' ')
				draw_square_on_img(game->minimap_img, x, y, 0x00333333);
			else if (game->map[i][j] == '1')
				draw_square_on_img(game->minimap_img, x, y, 0x00FFFFFF);
			else if (game->map[i][j] == 'D')
				draw_square_on_img(game->minimap_img, x, y, 0x00D0D7FE);
			else
				draw_square_on_img(game->minimap_img, x, y, 0x00030303);
			x += MINI_MAP_PIXEL;
			j++;
		}
		y += MINI_MAP_PIXEL;
		i++;
	}
}
