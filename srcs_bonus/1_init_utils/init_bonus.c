/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 08:13:08 by janhan            #+#    #+#             */
/*   Updated: 2024/06/19 12:50:32 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"

static void	init_intro(t_game *game)
{
	const float	scale_factor = 0.3;

	game->intro = make_image(game, game->main_menu->width * scale_factor,
			game->main_menu->height * scale_factor);
	scale_texture(game->main_menu, game->intro, 0.3);
	mlx_destroy_image(game->mlx, game->main_menu->img);
}

void	init(t_game *game, int ac, char **av)
{
	if (ac != 2)
		error_exit("usage \"./cub mapfile.cub\"");
	if (!(is_cub_file(av[1])))
		error_exit("NOT \".cub\" FILE");
	ft_memset(game, 0, sizeof(t_game));
	if (parse_file(game, av[1]) == FAILURE)
		error_exit("parse_file failed!");
	if (check_parse(game) == FAILURE)
		error_exit("check_parse not passed");
	init_map(game);
	init_game(game);
	init_player(game);
	init_object(game);
	init_npc(game);
	init_intro(game);
}
