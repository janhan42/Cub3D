/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 08:13:08 by janhan            #+#    #+#             */
/*   Updated: 2024/05/28 23:56:56 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_mand/header_mand.h"

void	init(t_game *game, int ac, char **av)
{
	if (ac != 2)
		error_exit("usage \"./cub mapfile.cub\"");
	ft_memset(game, 0, sizeof(t_game));
	if (parse_file(game, av[1]) == FAILURE)
		exit(1);
	if (check_parse(game) == FAILURE)
		exit(1);
	init_map(game);
	init_game(game);
	init_player(game);
}
