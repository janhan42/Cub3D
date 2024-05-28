/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 18:51:34 by sangshin          #+#    #+#             */
/*   Updated: 2024/05/28 17:41:50 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_mand/header_mand.h"

/**
 * @brief
 * 	맵 파싱 함수 TODO: 구현중
 * @param game
 * @param ac
 * @param av
 */
void	init_map(t_game *game, int ac, char **av)
{
	game->map = game->parse.map;
	game->map_len_w = game->parse.col;
	game->map_len_h = game->parse.row;
	game->map_width = game->parse.col * PIXEL;
	game->map_height = game->parse.row * PIXEL;
	game->ceiling_color = game->parse.ceiling_color;
	game->floor_color = game->parse.floor_color;
}
