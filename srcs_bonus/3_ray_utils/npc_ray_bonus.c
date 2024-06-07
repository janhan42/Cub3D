/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_ray_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 08:40:47 by janhan            #+#    #+#             */
/*   Updated: 2024/06/07 08:55:02 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"

int	npc_ray(t_player *player, t_npc *npc, t_game *game)
{
	double	dx;
	double	dy;
	double	distance;
	double	angle;
	int		i;
	double	x;
	double	y;
	int		map_x;
	int		map_y;

	// NPC에서 플레이어로 향하는 방향 계산
	dx = player->player_x - npc->npc_x;
	dy = player->player_y - npc->npc_y;
	distance = sqrt(dx * dx + dy * dy); // 거리 계산
	angle = atan2(dy, dx);

	// 초기 위치는 NPC의 위치
	x = npc->npc_x;
	y = npc->npc_y;
	i = 0;
	while(i < (int)distance)
	{
		x += cos(angle);
		y += sin(angle);
		map_x = (int)x >> 6; // 64로 나눔 (타일 크기 가정)
		map_y = (int)y >> 6;

		// 벽 충돌 검사
		if (game->map[map_y][map_x] == '1' || game->map[map_y][map_x] == 'V' || game->map[map_y][map_x] == 'H')
			return (FALSE);
		i++;
	}
	return (TRUE);
}
