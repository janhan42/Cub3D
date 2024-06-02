/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 08:13:08 by janhan            #+#    #+#             */
/*   Updated: 2024/06/01 11:34:15 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"

void	init(t_game *game, int ac, char **av)
{
	if (ac != 2)
		error_exit("usage \"./cub mapfile.cub\"");
	ft_memset(game, 0, sizeof(t_game));
	if (parse_file(game, av[1]) == FAILURE)
		error_exit("parse_file failed!");
	if (check_parse(game) == FAILURE)
		error_exit("check_parse not passed");
	init_map(game);
	init_game(game);
	init_player(game);
	init_object(game);
	printf("------------init_object OK-----------------\n");
}
