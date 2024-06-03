/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mini_map_sub_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 23:54:41 by janhan            #+#    #+#             */
/*   Updated: 2024/06/04 08:42:42 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"

void	draw_map_squre(t_game *game, t_single_minimap *m)
{
	if (m->my < 0
		|| m->my > game->map_len_h - 1
		|| m->mx < 0
		|| m->mx > (int)ft_strlen(game->map[m->my]) - 1
		|| game->map[m->my][m->mx] == ' ')
		draw_square_on_img(game->minimap_img, m->x, m->y, 0x00333333);
	else if (game->map[m->my][m->mx] == '1')
		draw_square_on_img(game->minimap_img, m->x, m->y, 0x00FFFFFF);
	else if (game->map[m->my][m->mx] == 'H' || game->map[m->my][m->mx] == 'V')
		draw_square_on_img(game->minimap_img, m->x, m->y, 0x00D0D7FE);
	else if (game->map[m->my][m->mx] == 'L')
		draw_square_on_img(game->minimap_img, m->x, m->y, 0x00BD8413);
	else
		draw_square_on_img(game->minimap_img, m->x, m->y, 0x00030303);
}
