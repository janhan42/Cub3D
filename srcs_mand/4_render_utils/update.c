/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:42:08 by janhan            #+#    #+#             */
/*   Updated: 2024/06/19 11:35:46 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_mand/header_mand.h"

int	update(t_game *game)
{
	game->s_time++;
	if (game->s_time >= 100)
	{
		player_movement(game);
		render_3d(game);
		game->s_time = 0;
	}
	return (0);
}
