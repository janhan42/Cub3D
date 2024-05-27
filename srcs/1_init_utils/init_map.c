/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 18:51:34 by sangshin          #+#    #+#             */
/*   Updated: 2024/05/27 23:32:37 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

/**
 * @brief
 * 	맵 파싱 함수 TODO: 구현중
 * @param game
 * @param ac
 * @param av
 */
void	init_map(t_game *game, int ac, char **av)
{
	if (ac != 2)
		error_exit("usage \"./cub mapfile.cub\"");
	if (parse_file(game, av[1]) == FAILURE)
		exit(1);
	if (check_parse(game) == FAILURE)
		exit(1);
	game->map = game->parse.map;
	print_map_info(game->map);
	game->map_len_w = game->parse.col;
	game->map_len_h = game->parse.row;
	game->map_width = game->parse.col * PIXEL;
	game->map_height = game->parse.row * PIXEL;
	game->ceiling_color = game->parse.ceiling_color;
	game->floor_color = game->parse.floor_color;
	print_game_info(game);
	printf("------------------------init_map OK---------------------------\n");
}
