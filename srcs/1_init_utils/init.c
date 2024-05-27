/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 08:13:08 by janhan            #+#    #+#             */
/*   Updated: 2024/05/27 19:39:00 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	init(t_game *game, int ac, char **av)
{
	init_map(game, ac, av);
	init_game(game);
	init_player(game);
	init_object(game);
}
