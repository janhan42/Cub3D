/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_sub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:47:22 by janhan            #+#    #+#             */
/*   Updated: 2024/05/04 13:47:41 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_map_info_sup(t_game *game, int i, int j)
{
	game->data->enemy[game->data->enm_nb].x = j * 50 + 24;
	game->data->enemy[game->data->enm_nb].y = i * 50 + 24;
	game->data->map[i][j] = '0';
	game->data->door.map[i][j] = '0';
	game->data->enm_nb++;
}

void	parse_map_sub(t_game *game)
{
	game->data->h_map = ft_lst_size(game->map);
	game->data->map = (char **)malloc(sizeof(char *) * (game->data->h_map + 1));
	game->data->door.map = (char **)malloc(sizeof(char *)
			* (game->data->h_map + 1));
	game->data->w_map = (int *)malloc(sizeof(int )
			* (game->data->h_map));
}
