/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:42:08 by janhan            #+#    #+#             */
/*   Updated: 2024/05/28 17:54:56 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_mand/header_mand.h"

/**
 * @brief
 * game->mode = GAME
 * @param game
 */
static void	render_game(t_game *game)
{
	render_3d(game);
}

int	update(t_game *game)
{
	game->s_time++;
	if (game->s_time >= 100)
	{
		mlx_destroy_image(game->mlx, game->render->img);
		free(game->render);
		game->render = make_image(game, WINDOW_W, WINDOW_H);
		if (game->mode == GAME)
		{
			player_movement(game);
			render_game(game);
		}
		if (game->mode == INTRO)
			render_intro(game);
		game->s_time = 0;
	}
	return (0);
}
