/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 08:13:08 by janhan            #+#    #+#             */
/*   Updated: 2024/05/28 15:33:46 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	init(t_game *game, int ac, char **av)
{
	if (ac != 2)
		error_exit("usage \"./cub mapfile.cub\"");
	ft_memset(game, 0, sizeof(t_game));
	if (parse_file(game, av[1]) == FAILURE)
		exit(1);
	if (check_parse(game) == FAILURE)
		exit(1);
	init_map(game, ac, av);
	init_game(game);
	init_player(game);
	init_object(game);
	printf("------------init_object OK-----------------\n");
}
