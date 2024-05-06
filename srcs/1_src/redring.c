/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redring.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:32:57 by janhan            #+#    #+#             */
/*   Updated: 2024/05/06 15:38:56 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	calculate_time(t_game *game)
{
	if (game->data->objects.t1 > 9)
		game->data->objects.t1 = 0,
		game->data->objects.t2++;

	if (game->data->objects.t2 > 5)
		game->data->objects.t2 = 0,
		game->data->objects.t3++;

	if (game->data->objects.t3 > 3 && game->data->objects.t4 == 2)
		game->data->objects.t3 = 0,
		game->data->objects.t4++;

	if (game->data->objects.t3 > 9 && game->data->objects.t4 < 2)
		game->data->objects.t3 = 0,
		game->data->objects.t4++;

	if (game->data->objects.t4 > 2)
		game->data->objects.t4 = 0;
}

void	*time_count(void *d, t_game *game)
{
	d = NULL;

	mlx_hook(game->data->mlx.win_ptr, 6, 1L<<6, mouse_move, game);
	mlx_hook(game->data->mlx.win_ptr, 4, 1L<<2, mouse_press, game);
	mlx_hook(game->data->mlx.win_ptr, 5, 1L<<3, mouse_release, game);
	while (1)
	{
		usleep(1000 * 300);
		if (game->data->mode == GAME)
		{
			game->data->objects.t1++;
			calculate_time(game),
			game->data->keys[999 - SCROLL_UP] = 1;
		}
	}
}
