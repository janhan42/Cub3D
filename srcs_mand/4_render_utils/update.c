/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:42:08 by janhan            #+#    #+#             */
/*   Updated: 2024/06/17 11:57:02 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_mand/header_mand.h"

/**
 * @brief
 * game->mode = GAME
 * @param game
 */
int	update(t_game *game)
{
	game->s_time++;
	if (game->s_time >= 100)
	{
		if (game->mode == GAME)
		{
			player_movement(game);
			render_3d(game);
		}
		if (game->mode == INTRO)
			render_intro(game);
		game->s_time = 0;
	}
	return (0);
}
