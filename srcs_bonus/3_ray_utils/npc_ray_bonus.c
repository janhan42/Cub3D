/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_ray_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 08:40:47 by janhan            #+#    #+#             */
/*   Updated: 2024/06/19 12:53:06 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"

int	npc_ray(t_player *player, t_npc *npc, t_game *game)
{
	t_npc_ray	ray;

	ray.dx = player->player_x - npc->npc_x;
	ray.dy = player->player_y - npc->npc_y;
	ray.distance = sqrt(ray.dx * ray.dx + ray.dy * ray.dy);
	ray.angle = atan2(ray.dy, ray.dx);
	ray.x = npc->npc_x;
	ray.y = npc->npc_y;
	ray.i = 0;
	while (ray.i < (int)ray.distance)
	{
		ray.x += cos(ray.angle);
		ray.y += sin(ray.angle);
		ray.map_x = (int)ray.x >> 6;
		ray.map_y = (int)ray.y >> 6;
		if (game->map[ray.map_y][ray.map_x] == '1'
			|| game->map[ray.map_y][ray.map_x] == 'V'
			|| game->map[ray.map_y][ray.map_x] == 'H')
			return (FALSE);
		ray.i++;
	}
	return (TRUE);
}
