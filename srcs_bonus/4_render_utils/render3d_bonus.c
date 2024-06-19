/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3d_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 22:34:45 by sangshin          #+#    #+#             */
/*   Updated: 2024/06/19 12:53:30 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"

/*
 * f_dest[0] = x position
 * f_dest[1] = y
 * f_dest[2] = distance
 * f_dest[3] = direction
*/
void	render_3d(t_game *game)
{
	t_dest	f_dest;
	double	ray_direction;
	double	ray_destination;
	double	ca;
	int		t;

	t = 0;
	ray_destination = game->player->player_rad
		+ (0.000545415391 * WINDOW_W / 2);
	ray_direction = game->player->player_rad
		- (0.000545415391 * WINDOW_W / 2);
	while (ray_direction <= ray_destination)
	{
		f_dest = get_dest(game->player->player_x, game->player->player_y,
				ray_direction, game);
		ca = game->player->player_rad - ray_direction;
		game->w_dist[t] = f_dest.distance;
		f_dest.distance = f_dest.distance * cos(ca);
		render_texture(game, &f_dest, t);
		ray_direction += 0.000545415391;
		t++;
	}
	render_object(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->render->img, 0, 0);
}
